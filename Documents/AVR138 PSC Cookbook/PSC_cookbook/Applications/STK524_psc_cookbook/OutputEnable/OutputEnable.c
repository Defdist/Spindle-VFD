//******************************************************************************
//!
//! @file $Id: OutputEnable.c 804 2008-02-20 09:09:20Z raubree $
//!
//! Copyright (c) 2008 Atmel.
//!
//! @brief Main module : Provide a PWM led chaser on PSC outputs
//!
//! @todo
//! @bug
//******************************************************************************



//_____ D E F I N I T I O N S ______________________________________________
#include "gcc_compiler.h"
#include <avr/io.h>

#include "pll_drv.h"

#include "psc_drv.h"


//_____ D E F I N I T I O N S ______________________________________________

#define A_SA_VAL 25
#define A_RA_VAL 75
#define A_SB_VAL 40

#define B_SA_VAL 110
#define B_RA_VAL 80
#define B_SB_VAL 115

#define C_SA_VAL 60
#define C_RA_VAL 80
#define C_SB_VAL 90


#define RB_VAL 125


/* define here your PSC configuration */
#define PSC_PRESCALER PSC_NODIV_CLOCK
#define PSC_CLOCK_SOURCE PSC_CLOCK_SOURCE_EQ_PLL

#define PSC_MODE PSC_MODE_CENTERED

#define PSC_OUTPUT_B_POLARITY PSC_OUTPUT_HIGH
#define PSC_OUTPUT_A_POLARITY PSC_OUTPUT_HIGH


      unsigned char temp;
      unsigned char i;


/*F**************************************************************************
* NAME: PSC Init
*****************************************************************************/
void PSC_Init (void)
{
   Psc_enable_all_outputs();

   Psc_set_module_A(A_SA_VAL,A_RA_VAL,A_SB_VAL);
   Psc_set_module_B(B_SA_VAL,B_RA_VAL,B_SB_VAL);
   Psc_set_module_C(C_SA_VAL,C_RA_VAL,C_SB_VAL);
   Psc_set_register_RB(RB_VAL);

   Psc_config();

   Psc_run();

}



/*F**************************************************************************
* NAME: main
*****************************************************************************/
int main (void)
{

  Start_pll_64_mega();
  Wait_pll_ready();
  PSC_Init();

      while(1)
      {

         temp=1;
         for (i = 1; i < 7; i++)
         { 
            POC = temp;
            temp = (temp<<1);
            delay();
         }


         Psc_select_outputs(0,1,0,1,0,1);
         delay();

         Psc_select_outputs(1,0,1,0,1,0);
         delay();

         Psc_select_outputs(1,1,0,0,1,1);
         delay();

         Psc_select_outputs(0,0,1,1,0,0);
         delay();

      }



}




