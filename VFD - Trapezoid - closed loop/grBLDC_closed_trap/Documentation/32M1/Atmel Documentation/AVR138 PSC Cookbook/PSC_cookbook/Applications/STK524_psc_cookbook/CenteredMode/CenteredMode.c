//******************************************************************************
//!
//! @file $Id: CenteredMode.c 804 2008-02-20 09:09:20Z raubree $
//!
//! Copyright (c) 2008 Atmel.
//!
//! @brief Main module : Generate 6 PWM waveforms with PSC in centered mode 
//!
//! @todo
//! @bug
//******************************************************************************



/*_____ I N C L U D E S ____________________________________________________*/

#include "gcc_compiler.h"
#include <avr/io.h>

#include "pll_drv.h"

#include "psc_drv.h"


//_____ D E F I N I T I O N S ______________________________________________

/* T_OVERLAP to choose a set of values which overlap*/
//#define T_OVERLAP


#ifdef T_OVERLAP

#define A_SA_VAL 40
#define A_RA_VAL 75
#define A_SB_VAL 25

#define B_SA_VAL 115
#define B_RA_VAL 80
#define B_SB_VAL 110

#define C_SA_VAL 90
#define C_RA_VAL 80
#define C_SB_VAL 60

#define RB_VAL 125

#else

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

#endif

/* define here your own application */
#define PSC_PRESCALER PSC_NODIV_CLOCK
#define PSC_CLOCK_SOURCE PSC_CLOCK_SOURCE_EQ_CLKIO


#define PSC_MODE PSC_MODE_CENTERED


#define PSC_OUTPUT_B_POLARITY PSC_OUTPUT_HIGH
//#define PSC_OUTPUT_B_POLARITY PSC_OUTPUT_LOW
#define PSC_OUTPUT_A_POLARITY PSC_OUTPUT_HIGH
//#define PSC_OUTPUT_A_POLARITY PSC_OUTPUT_LOW


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

  while(1) {;}
}




