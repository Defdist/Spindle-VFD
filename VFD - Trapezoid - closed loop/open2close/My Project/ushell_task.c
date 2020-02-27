//******************************************************************************
//!
//! @file $Id: ushell_task.c 1137 2008-04-17 16:35:06Z raubree $
//!
//! Copyright (c) 2007 Atmel.
//!
//! @brief This file manages the µshell task for communication.
//!
//! @todo
//! @bug
//******************************************************************************

//_____  I N C L U D E S ___________________________________________________

#include "config.h"
#include "ushell_task.h"
#include "ascii.h"
#include "uart/uart_lib.h"
#include "mc_interface.h"
#include "mc_drv.h"

U16 debug_get_value1(void);
U16 debug_get_value2(void);

//_____ M A C R O S ________________________________________________________

//_____ D E F I N I T I O N S ______________________________________________
void convert_param1(void);
void print_hex16(U16 value);

//_____ D E C L A R A T I O N S ____________________________________________

static U8 cmd;
static U8 cmd_type;
static U16 par_str1[8];
static U16 par_str2[8];
static U16 param1;
static U16 param2;
static U8 cmd_str[26];
static U8 i_str=0;

volatile Bool ushell_active = FALSE;

U8 code str_run[]=STR_RUN;
U8 code str_stop[]=STR_STOP;
U8 code str_help[]=STR_HELP;
U8 code str_forward[]=STR_FORWARD;
U8 code str_backward[]=STR_BACKWARD;
U8 code str_set_speed[]=STR_SET_SPEED;
U8 code str_get_id[]=STR_GET_ID;
U8 code str_get_status0[]=STR_GET_STATUS0;
U8 code str_get_status1[]=STR_GET_STATUS1;

U8 code msg_prompt[]=MSG_PROMPT;
U8 code msg_welcome[]=MSG_WELCOME;
U8 code msg_help[]=MSG_HELP;
U8 code msg_er_cmd_not_found[]=MSG_ER_CMD_NOT_FOUND;

extern S16 speed_error;

//! @brief This function initializes the hardware/software ressources required for ushell task.
//!
//!
//! @param none
//!
//! @return none
//!
//!/
void ushell_task_init(void)
{
   uart_init();
   print_msg(msg_welcome);
   print_msg(msg_prompt);
   cmd=FALSE;
   cmd_type=CMD_NONE;
}





//! @brief Entry point of the explorer task management
//!
//! This function links perform ushell task decoding to access file system functions.
//!
//!
//! @param none
//!
//! @return none
void ushell_task(void)
{
   U8 status = 0;

   if(cmd==FALSE)
   {
      build_cmd();
   }
   else
   {
      switch (cmd_type)
      {
         case CMD_HELP:
            print_msg(msg_help);
            break;
         case CMD_RUN:
            mci_run();
            break;
         case CMD_STOP:
            mci_stop();
            break;
         case CMD_FORWARD:
            mci_forward();
            break;
         case CMD_BACKWARD:
            mci_backward();
            break;
         case CMD_SET_SPEED:
            convert_param1();
            mc_disable_during_inrush();
            mci_set_ref_speed((U8)param1);
            break;
         case CMD_GET_ID:
            print_hex16(BOARD_ID);
            uart_putchar(' ');
            print_hex16(SOFT_ID);
            uart_putchar(' ');
            print_hex16(REV_ID);
            break;
         case CMD_GET_STATUS0:
            status = 0;
            if (mci_direction == CCW) {status |= (1<<3);}
            if (mci_run_stop == TRUE) {status |= (1<<2);}
            print_hex16(status);
            uart_putchar(' ');
            print_hex16(mci_get_measured_speed());
            uart_putchar(' ');
            print_hex16(mci_get_measured_current());
            ushell_active = TRUE;
            break;
         case CMD_GET_STATUS1:
            print_hex16(0xDEA);
            uart_putchar(' ');
            print_hex16(0x123);
            break;
         default:    //Unknown command
            print_msg(msg_er_cmd_not_found);
      }
      cmd_type=CMD_NONE;
      cmd=FALSE;
      print_msg(msg_prompt);
   }
}

//! @brief get the full command line to be interpreted.
//!
//! @param none
//!
//! @return none
void build_cmd(void)
{
U8 c;

   if (uart_test_hit())    //Something new of  the UART ?
   {
      c=uart_getchar();
      switch (c)
      {
         case CR:
            cmd_str[i_str]=0;  //Add NULL char
            parse_cmd();    //Decode the command
            i_str=0;
            break;
         case ABORT_CHAR:    //^c abort cmd
            i_str=0;
            printf("\r#");
            break;
         case BKSPACE_CHAR:   //backspace
            if(i_str>0)
            {
               uart_putchar(c);
               uart_putchar(' ');
               uart_putchar(c);
            }
            if(i_str>=1)
            {
               i_str--;
            }
            break;

         default:
            cmd_str[i_str++]=c;  //append to cmd line
            break;
      }
   }
}



//! @brief decodes full command line into command type and arguments
//!
//! This function allows to set the cmd_type to the command type decoded
//! with its respective arguments par_str1 and par_str2
//!
//! @param none
//!
//! @return none
void parse_cmd(void)
{
   U8 i=0;
   U8 j;

   //Get command type
   for(i=0;cmd_str[i]!=' ' && i<=i_str;i++);
   cmd=TRUE;

   //Decode command type

   if ( mystrncmp(cmd_str,str_run,i-1))
   {  cmd_type=CMD_RUN; }
   else if ( mystrncmp(cmd_str,str_stop,i-1))
   {  cmd_type=CMD_STOP; }
   else if ( mystrncmp(cmd_str,str_help,i-1))
   {  cmd_type=CMD_HELP; }
   else if ( mystrncmp(cmd_str,str_forward,i-1))
   {  cmd_type=CMD_FORWARD; }
   else if ( mystrncmp(cmd_str,str_backward,i-1))
   {  cmd_type=CMD_BACKWARD; }
   else if ( mystrncmp(cmd_str,str_set_speed,i-1))
   {  cmd_type=CMD_SET_SPEED; }
   else if ( mystrncmp(cmd_str,str_get_id,i-1))
   {  cmd_type=CMD_GET_ID; }
   else if ( mystrncmp(cmd_str,str_get_status0,i-1))
   {  cmd_type=CMD_GET_STATUS0; }
   else if ( mystrncmp(cmd_str,str_get_status1,i-1))
   {  cmd_type=CMD_GET_STATUS1; }
   else
   {
      if(i_str)
      {
        print_msg(msg_er_cmd_not_found);
      }
      print_msg(msg_prompt);
      cmd=FALSE;
      return;
   }

  //Get first arg (if any)
   if(++i<i_str)
   {
      j=0;
      for(;(cmd_str[i]!=' ')&&(i<i_str);i++)
      {
         LSB(par_str1[j])=cmd_str[i];
         MSB(par_str1[j])=0;
         j++;
      }
      LSB(par_str1[j])=0;MSB(par_str1[j])=0;
   }
   else   {  return; }

   //Get second arg (if any)
   if(++i<i_str)
   {
      j=0;
      for(;(cmd_str[i]!=' ')&&(i<i_str);i++)
      {
         LSB(par_str2[j])=cmd_str[i];
         MSB(par_str2[j])=0;
         j++;
      }
      LSB(par_str2[j])=0;MSB(par_str2[j])=0;
   }
   else   { return; }

}

//! @brief compares two strings located in flash code area.
//!
//! @param *str1
//! @param *str2
//!
//! @return status: TRUE for ok, FALSE if strings are not equal
#ifdef __GNUC__
U8 mystrncmp(U8 *str1,U8 const *str2,U8 i)
#else
U8 mystrncmp(U8 *str1,U8 code *str2,U8 i)
#endif
{
   U8 j;
   for(j=0;j<=i;j++)
   {
#ifndef __GNUC__
      if(*str1!=*str2)
#else
      if( *str1 != pgm_read_byte_near((unsigned int)str2))
#endif
      {
         return FALSE;
      }
      str1++;str2++;
   }
   return TRUE;
}

//! @brief Display an ASCII code string.
//!
//! @param *str: pointer to string located in flash area
//!
//! @return none
#ifdef __GNUC__
void print_msg(U8 const *str)
#else
void print_msg(U8 code *str)
#endif
{
U8 c;
#ifndef __GNUC__
   c=*str++;
   while(c!=0)
   {
      uart_putchar(c);
      c=*str++;
   }
#else    // AVRGCC does not support point to PGM space
   c=pgm_read_byte_near((unsigned int)str++);
   while(c!=0)
   {
      uart_putchar(c);
      c=pgm_read_byte_near((unsigned int)str++);
   }
#endif

}

//! @brief convert param1 to binaire.
//!
//! @param none
//!
//! @return none
void convert_param1(void)
{
   U8 i = 0;
   param1 = 0;
   while ( par_str1[i] != 0 )
   {
      param1 = param1 << 4;
      param1 = param1 + ascii_to_bin(par_str1[i]);
      i++;
   }
}

//! @brief convert param2 to binaire.
//!
//! @param none
//!
//! @return none
void convert_param2(void)
{
   U8 i = 0;
   param2 = 0;
   while ( par_str2[i] != 0 )
   {
      param2 = param2 << 4;
      param2 = param2 + ascii_to_bin(par_str2[i]);
      i++;
   }
}

//! @brief Display an U16 with hexa form.
//!
//! @param
//!
//! @return none
void print_hex16(U16 value)
{
   U8 c;
   U8 d4;
   U8 d3;
   U8 d2;
   U8 d1;

   d4 = (U16)(value >> 12) & 0x0F;
   d3 = (U16)(value >> 8) & 0x0F;
   d2 = (U16)(value >> 4) & 0x0F;
   d1 = (U16)(value) & 0x0F;

   if (d4 != 0)
   {
      c = bin_to_ascii(d4);
      uart_putchar(c);

      c = bin_to_ascii(d3);
      uart_putchar(c);

      c = bin_to_ascii(d2);
      uart_putchar(c);
   }
   else
   {
      if (d3 != 0)
      {
         c = bin_to_ascii(d3);
         uart_putchar(c);

         c = bin_to_ascii(d2);
         uart_putchar(c);
      }
      else
      {
         if (d2 != 0)
         {
            c = bin_to_ascii(d2);
            uart_putchar(c);
         }
      }
   }

   c = bin_to_ascii(d1);
   uart_putchar(c);
}



