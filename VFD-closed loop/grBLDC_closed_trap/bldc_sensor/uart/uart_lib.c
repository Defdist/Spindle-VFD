//******************************************************************************
//!
//! @file $Id: uart_lib.c 1344 2008-05-07 14:50:31Z raubree $
//!
//! Copyright (c) 2007 Atmel.
//!
//! @brief This file provides a minimal VT100 terminal access through UART \n
//!        and compatibility with Custom I/O support
//!
//! @todo
//! @bug
//******************************************************************************

/*_____ I N C L U D E S ____________________________________________________*/
#include "config.h"
#include "uart/uart_lib.h"


/*_____ G L O B A L    D E F I N I T I O N _________________________________*/


/*_____ D E F I N I T I O N ________________________________________________*/



#define     LBT_MASK ((1<<LBT5)|(1<<LBT4)|(1<<LBT3)|(1<<LBT2)|(1<<LBT1)|(1<<LBT0)) 

#define Byte_transfer_enable()  { LINCR = (0<<LIN13)|(1<<LENA)|(1<<LCMD2)|(1<<LCMD1)|(1<<LCMD0); }

#define Lin_set_btr_brr(bt,br)  { U8 __jacq__;                                                            \
                                  __jacq__ = LINCR;                                                       \
                                  LINCR  &= ~(1<<LENA);                                                   \
                                  LINBTR  = ((1<<LDISR) | (LBT_MASK & bt));                               \
                                  LINBRRH = (U8)((((((((U32)FOSC*1000)<<1)/(((U32)br)*bt))+1)>>1)-1)>>8); \
                                  LINBRRL = (U8)(( (((((U32)FOSC*1000)<<1)/(((U32)br)*bt))+1)>>1)-1)    ; \
                                  LINCR = __jacq__;                                                       }

#define Lin_rx_response_ready() ( LINSIR & (1<<LRXOK) )
#define Lin_tx_response_ready() ( LINSIR & (1<<LTXOK) )
#define Lin_get_data()          ( LINDAT )      
#define Lin_set_data(data)      ( LINDAT = data )

#define BITSAMPLING 8    /* 8 samples per bit */

/*_____ M A C R O S ________________________________________________________*/


bit uart_test_hit(void)
{
  return (Lin_rx_response_ready());
}


bit uart_init(void)
{
   Lin_set_btr_brr(BITSAMPLING,BAUDRATE);
   Byte_transfer_enable();
   Lin_set_data(0xFF);
   return TRUE;
}


r_uart_ptchar uart_putchar(p_uart_ptchar ch)
{
   while (!Lin_tx_response_ready());
   Lin_set_data(ch);
   return (ch);
}




r_uart_gtchar uart_getchar(void)
{
    while(!Lin_rx_response_ready());
    return Lin_get_data();
}


