#include "grBLDC.h"

int main(void)
{
  psc_init();
  adc_init();
  motor_init();
  hall_init();
  mosfet_init();
  a4910_init(); //configure pin to digital output
  timing_timer0_init();
  timing_timer1_init();

  Start_pll_64_mega(); // Start the 64 MHz PLL
  Wait_pll_ready();
  
  a4910_enable(); //enable MOSFET driver
  motor_run();

  sei(); //enable interrupts
  
  //adc_goalRPM_set(255); //debug

  while(1)
  {	  	  
    if (timing_gTick_get() == TRUE) // Timer 1 interrupt sets gTick=TRUE every 256us
    {	
      timing_gTick_set(FALSE); //acknowledge interrupt
      
      // adc_Scheduler(); // Get Current or potentiometer value
      
      // static uint16_t g_regulation_period = 0; //sampling period
	    // 
      // if(++g_regulation_period >= 40) //n * 256us = Te //40: update PID every 10.24 ms
      // {
      //   pid_dutyCycle_calculate();
      //   g_regulation_period = 0;
      // }

      //psc_setDutyCycle( pid_dutyCycle_get() );
      psc_setDutyCycle(255); //debug
	  
      //mc_inrush_task();       // manage the inrush current
    }
  }
}
