//******************************************************************************
//!
//! @file $Id: Interrupt.c 828 2008-02-28 18:07:35Z raubree $
//!
//! Copyright (c) 2008 Atmel.
//!
//! @brief Main module : Generate 6 PWM waveforms with PSC in centered mode 
//!                      And an interruption when PSC cycle is completed
//! @todo
//! @bug
//******************************************************************************



/*_____ I N C L U D E S ____________________________________________________*/

#include "gcc_compiler.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#include "pll_drv.h"

#include "psc_drv.h"


//_____ D E F I N I T I O N S ______________________________________________



#define A_SA_VAL 250
#define A_RA_VAL 750
#define A_SB_VAL 400

#define B_SA_VAL 1100
#define B_RA_VAL 800
#define B_SB_VAL 1150

#define C_SA_VAL 600
#define C_RA_VAL 800
#define C_SB_VAL 900


#define RB_VAL 1250


/* define here your own application */
#define PSC_PRESCALER PSC_NODIV_CLOCK
#define PSC_CLOCK_SOURCE PSC_CLOCK_SOURCE_EQ_CLKIO


#define PSC_MODE PSC_MODE_CENTERED


#define PSC_OUTPUT_B_POLARITY PSC_OUTPUT_HIGH
//#define PSC_OUTPUT_B_POLARITY PSC_OUTPUT_LOW
#define PSC_OUTPUT_A_POLARITY PSC_OUTPUT_HIGH
//#define PSC_OUTPUT_A_POLARITY PSC_OUTPUT_LOW



ISR(SIG_PSC_END_CYCLE)
{
   PIND = (1<<PIND2); /* toggle Port D2 on each interrupt */
}


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

   PIM = (1<<PEOPE); /* set the PSC End of Cycle Interrupt Enable */

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

  DDRD |= (1<<DDD2); /* set port D2 as output */

  __enable_interrupt;

  while(1) {;}
}




