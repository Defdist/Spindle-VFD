#include "grBLDC.h"

//hardware interface to grbl (328p)

uint8_t goalRPM_status = GOALRPM_LPF_CHANGING;

/////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t interface_goalRPM_status(void) { return goalRPM_status; }

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void interface_init(void)
{
  // Use PCINT3 to detect change on PB3 (direction pin)
  PCMSK0 = (1<<PCINT3);
  
  // Enable pin change interrupts on PCMSK0
  PCICR |= (1<<PCIE0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

ISR( DIRECTION_PIN_CHANGE_vect )
{
  goalRPM_status = GOALRPM_LPF_CHANGING;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

//see if the direction pin has changed
void interface_checkForDirectionChange(void)
{
	static uint8_t grblDirection_previous = 2;
	uint8_t grblDirection_now = ((PINB & (1<<PINB3)) >> (PINB3)); //0: CW (M3) //1: CCW (M4)

	if(grblDirection_now != grblDirection_previous)
	{
		while(timing_measuredRPM_get() > 500) { a4910_disable(); } //coast motor until it slows down enough to change direction

		a4910_enable(); //turn FETs back on

		if(grblDirection_now == 0) { motor_direction_set(MOTOR_CW); }
		else                       { motor_direction_set(MOTOR_CCW); }
			
		pid_dutyCycle_set(0);
		//adc_goalRPM_set(0); //don't set this here... ADC isn't sampling goalRPM at this point, so goalRPM will remain 0 until next interrupt occurs (e.g. 'S3000')

		grblDirection_previous = grblDirection_now;
	}
} 

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void interface_handler(void)
{
	if (goalRPM_status == GOALRPM_LPF_CHANGING) //set inside interrupt when grbl direction pin toggles
	{
		adc_scheduler(ADC_MEASURING_GOAL_RPM);
		
		if(motor_state_get() == STOPPED) { motor_run(); }

		#define GOALRPM_LPF_SETTLING_TIME_us 40000 //lowpass filter settles in 30 ms... wait at least this long
		#define NUM_ITERATIONS_FOR_LPF_TO_SETTLE (GOALRPM_LPF_SETTLING_TIME_us / CONTROL_LOOP_PERIOD_us) //division handled by pre-processor

		static uint16_t iterationCount = 0;

		if(++iterationCount > NUM_ITERATIONS_FOR_LPF_TO_SETTLE)
		{
			goalRPM_status = GOALRPM_LPF_SETTLED;
			iterationCount = 0;
		}
	}
	else { interface_checkForDirectionChange(); } //We don't want to do this when grbl is toggling direction pin (to generate interrupt)
}