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

void interface_checkForDirectionChange(void)
{
	static uint8_t grblDirection_previous = 0;
	uint8_t grblDirection_now = ((PINB & (1<<PINB3)) >> (PINB3)); //0: CW //1: CCW

	if(grblDirection_now != grblDirection_previous)
	{
		while(timing_measuredRPM_get() > 2000) { A4910_disable(); } //coast motor until it slows down enough to change direction

		A4910_enable(); //turn FETs back on

		if(grblDirection_now == 0) { motor_direction_set(MOTOR_CW); }
		else                       { motor_direction_set(MOTOR_CCW); }

		grblDirection_previous = grblDirection_now;
	}
} 

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void interface_handler(void)
{
	if (goalRPM_status == GOALRPM_LPF_CHANGING)
	{
		unoPinA2_high(); //debug

		adc_scheduler(ADC_MEASURING_GOAL_RPM);
		
		if(motor_state_get() == STOPPED) { motor_run(); } //JTS2doNow: Where should this go?

		#define GOALRPM_LPF_SETTLING_TIME_us 40000 //lowpass filter settles in 30 ms... wait longer
		#define NUM_ITERATIONS_FOR_LPF_TO_SETTLE (GOALRPM_LPF_SETTLING_TIME_us / CONTROL_LOOP_PERIOD_us) //division handled to pre-processor

		static uint16_t iterationCount = 0;

		if(++iterationCount > NUM_ITERATIONS_FOR_LPF_TO_SETTLE)
		{
			goalRPM_status = GOALRPM_LPF_SETTLED;
			iterationCount = 0;
		}

		//JTS2doNow: Store direction pin
	}
	else
	{
		unoPinA2_low(); //debug

		interface_checkForDirectionChange();
	}
}