#include "grBLDC.h"

//_____ D E C L A R A T I O N S ____________________________________________
uint16_t g_regulation_period = 0;  //sampling period
extern uint8_t overcurrent;

int main(void)
{
  mc_motor_init();
  
  mci_motor_run();
  
  hall_goalRPM_set(255); //debug
  
  while(1)
  {	  	  
    if (mc_drv_g_tick_get() == TRUE) // Timer 1 generates an interrupt (which sets g_tick) every 256us
    {		
      mc_drv_g_tick_set(FALSE);
      mc_ADC_Scheduler(); // Get Current or potentiometer value
      g_regulation_period += 1;
	    
      if(g_regulation_period >= 40) //n * 256us = Te
      {
        g_regulation_period = 0;

        pid_dutyCycle_calculate();
      }

	  
      //if( hall_goalRPM_get() < 64 ) { setPC3_low(); }
	  //else                           { setPC3_high(); }
		  
	  

      //psc_setDutyCycle( pid_dutyCycle_get() );
      psc_setDutyCycle(255); //debug
	  
      //mc_inrush_task();       // manage the inrush current
    }
	
  /*
    if (overcurrent==0)
    {
	    A4910_Enable();
    }
    else
    {
	    A4910_Disable();
    }
  */

  }
}
