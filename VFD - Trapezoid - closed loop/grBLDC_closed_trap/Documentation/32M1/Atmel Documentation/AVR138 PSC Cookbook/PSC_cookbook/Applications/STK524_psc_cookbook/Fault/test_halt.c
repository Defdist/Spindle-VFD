//******************************************************************************
//!
//! @file $Id: test_halt.c 804 2008-02-20 09:09:20Z raubree $
//!
//! Copyright (c) 2008 Atmel.
//!
//! @brief Main module : Provide a way to test the fault feature on input 
//!
//! @todo
//! @bug
//******************************************************************************



//_____ I N C L U D E S ________________________________________________________

#include "gcc_compiler.h"
#include <avr/io.h>

#include "pll_drv.h"

#include "psc_drv.h"

#define TEST_FILTER
#ifdef TEST_FILTER
  #define A_SA_VAL 5
  #define A_RA_VAL 25
  #define A_SB_VAL 30

  #define B_SA_VAL 5
  #define B_RA_VAL 25
  #define B_SB_VAL 30

  #define C_SA_VAL 5
  #define C_RA_VAL 25
  #define C_SB_VAL 30

  #define RB_VAL 40
#else
  #define A_SA_VAL 5
  #define A_RA_VAL 75
  #define A_SB_VAL 65

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
#define PSC_CLOCK_SOURCE PSC_CLOCK_SOURCE_EQ_PLL


#define PSC_MODE PSC_MODE_ONE_RAMP

#define PSC_OUTPUT_B_POLARITY PSC_OUTPUT_HIGH
#define PSC_OUTPUT_A_POLARITY PSC_OUTPUT_HIGH

 /* comment the following line to test the disactivate mode
    rather than the halt mode */
//#define PSC_TEST_HALT


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

#ifdef PSC_TEST_HALT
   Psc_config_input_0(PSC_OVERLAP_DISABLE,\
                      PSC_USE_PIN,\
					  PSC_USE_LOW_LEVEL,\
					  PSC_INPUT_FILTER_ENABLE,\
					  PSC_SYNCHRONOUS_OUTPUT_CONTROL,\
					  PSC_INPUT_HALT);
#else  /* test the disable output mode */
   Psc_config_input_0(PSC_OVERLAP_DISABLE,\
                      PSC_USE_PIN,\
					  PSC_USE_HIGH_LEVEL,\
					  PSC_INPUT_FILTER_DISABLE,\
					  PSC_SYNCHRONOUS_OUTPUT_CONTROL,\
					  PSC_DISACTIVATE_OUTPUT_A);
#endif

   Psc_run();

}



/*F**************************************************************************
* NAME: main
*****************************************************************************/
int main (void)
{
  Start_pll_64_mega();
  Wait_pll_ready();
  psc_init();


  PORTC = 0xFF;
  DDRC = 0xFF;

  while(1)
  {

   if (bit_is_clear(PINE,PINE2))
	{
	  while (bit_is_clear(PINE,PINE2));
     Psc_run();
	}

  }
} 




