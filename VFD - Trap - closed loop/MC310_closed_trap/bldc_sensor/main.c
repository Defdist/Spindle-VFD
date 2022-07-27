#include "grBLDC.h"

FUSES = { //set 32M1's fuses.  //Requires avr/io.h
	.low      = 0xFF,
	.high     = 0xD7,
	.extended = 0xFF
};

int main(void)
{
  psc_init();
  adc_init();
  motor_init();
  hall_init();
  a4910_init(); //configure pin to digital output
  timing_timer0_init();
  timing_timer1_init();
  interface_init();

  Start_pll_64_mega(); // Start the 64 MHz PLL
  Wait_pll_ready();
  
  a4910_enable(); //enable MOSFET driver
  //motor_run();

  sei(); //enable interrupts

  while(1)
  {	  	  
    if (timing_runControlLoop_get() == TRUE) //controlled by Timer0 interrupt
    {	
      timing_runControlLoop_set(FALSE); //prevent control loop from running again until next Timer0 interrupt occurs

      interface_handler();
    }
	
	if((TCNT1 > 65534) && (motor_state_get() == RUNNING) ) //hall event hasn't occurred recently
	{
		pid_dutyCycle_set(150); //kickstart motor
		psc_commutateOutputWaveforms(150);
	}
  }
}
