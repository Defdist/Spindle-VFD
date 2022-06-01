#include "grBLDC.h"

int main(void)
{
  psc_init();
  adc_init();
  motor_init();
  hall_init();
  a4910_init(); //configure pin to digital output
  timing_timer0_init();
  timing_timer1_init();

  Start_pll_64_mega(); // Start the 64 MHz PLL
  Wait_pll_ready();
  
  a4910_enable(); //enable MOSFET driver
  motor_run();

  sei(); //enable interrupts

  while(1)
  {	  	  
    if (timing_runControlLoop_get() == TRUE) //controlled by Timer0 interrupt
    {	
      timing_runControlLoop_set(FALSE); //prevent control loop from running again until next Timer0 interrupt occurs
      
      adc_scheduler(); //JTS2doLater: This only needs to run when 328p is updating goalRPM
      
      pid_scheduler();

      //psc_commutateOutputWaveforms( pid_dutyCycle_get() ); //debug
	  
      //mc_inrush_task();       // manage the inrush current
    }
  }
}
