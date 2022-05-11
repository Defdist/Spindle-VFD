//******************************************************************************
//******************************************************************************
//!
//! @file $Id: test_with_comparator.c 826 2008-02-28 14:23:24Z raubree $
//!
//! Copyright (c) 2008 Atmel.
//!
//! @brief Main module : Demonstrate the use of comparator 0 as PSC input
//! 
//! @todo
//! @bug
//******************************************************************************




//_____ I N C L U D E S ____________________________________________________


#include "gcc_compiler.h"
#include <avr/io.h>

#include "pll_drv.h"

#include "psc_drv.h"

#include "comparator_drv.h"



/* PSC configuration */
#define A_SA_VAL 100
#define A_RA_VAL 500
#define A_SB_VAL 600

#define B_SA_VAL 110
#define B_RA_VAL 80
#define B_SB_VAL 115

#define C_SA_VAL 60
#define C_RA_VAL 80
#define C_SB_VAL 90


#define RB_VAL 1250



#define PSC_PRESCALER PSC_DIV_CLOCK_BY_256
#define PSC_CLOCK_SOURCE PSC_CLOCK_SOURCE_EQ_PLL
#define PSC_MODE PSC_MODE_ONE_RAMP

#define PSC_OUTPUT_B_POLARITY PSC_OUTPUT_HIGH
#define PSC_OUTPUT_A_POLARITY PSC_OUTPUT_HIGH


/* Comparator 0 configuration */
#define COMP0_ENABLE_BIT_VALUE COMP_ENABLE
#define COMP0_INTERRUPT_ENABLE COMP_DISABLE_INTERRUPT
#define COMP0_INTERRUPT_SELECT COMP_INTERRUPT_ON_OUTPUT_TOGGLE
#define COMP_CLOCK_SOURCE COMP_CLOCK_IO
#define COMP0_NEG_INPUT_SELECT COMP_USE_NEGATIVE_PIN



/*F**************************************************************************
* NAME: psc_init
*****************************************************************************/
void psc_init (void)
{
   Psc_enable_all_outputs();

   Psc_set_module_A(A_SA_VAL,A_RA_VAL,A_SB_VAL);
   Psc_set_module_B(B_SA_VAL,B_RA_VAL,B_SB_VAL);
   Psc_set_module_C(C_SA_VAL,C_RA_VAL,C_SB_VAL);
   Psc_set_register_RB(RB_VAL);

   Psc_config();

   Psc_config_input_0(PSC_OVERLAP_DISABLE,\
                      PSC_USE_COMPARATOR,\
                      PSC_USE_LOW_LEVEL,\
                      PSC_INPUT_FILTER_ENABLE,\
                      PSC_SYNCHRONOUS_OUTPUT_CONTROL,\
                      PSC_DISACTIVATE_ALL_OUTPUTS);


   Psc_config_input_1(PSC_OVERLAP_DISABLE,\
                      PSC_USE_PIN,\
                      PSC_USE_LOW_LEVEL,\
                      PSC_INPUT_FILTER_ENABLE,\
                      PSC_SYNCHRONOUS_OUTPUT_CONTROL,\
                      PSC_INPUT_NO_ACTION);

   Psc_config_input_2(PSC_OVERLAP_DISABLE,\
                      PSC_USE_PIN,\
                      PSC_USE_LOW_LEVEL,\
                      PSC_INPUT_FILTER_ENABLE,\
                      PSC_SYNCHRONOUS_OUTPUT_CONTROL,\
                      PSC_INPUT_NO_ACTION);


   Psc_run();

}



/*F**************************************************************************
* NAME: main
*****************************************************************************/

int main (void){

   U16 temp;

   Start_pll_64_mega();
   Wait_pll_ready();


   DIDR0 = (1<<ADC5D); /* ACMPN0D */
   DIDR1 = (1<<ACMP0D)|(1<<AMP0PD)|(1<<AMP0ND);

   Comp_0_config();

   psc_init();


   while(1)
   {

       ;
   }
} 




