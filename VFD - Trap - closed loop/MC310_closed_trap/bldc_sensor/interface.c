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
		
		motor_stop();  //prevent motion while requested speed is changing
		
		#define GOALRPM_LPF_SETTLING_TIME_us 40000 //lowpass filter settles in 30 ms... wait at least this long
		#define NUM_ITERATIONS_FOR_LPF_TO_SETTLE (GOALRPM_LPF_SETTLING_TIME_us / CONTROL_LOOP_PERIOD_us) //division handled by pre-processor

		static uint16_t iterationCount = 0;

		if(++iterationCount > NUM_ITERATIONS_FOR_LPF_TO_SETTLE)
		{
			goalRPM_status = GOALRPM_LPF_SETTLED;
			iterationCount = 0;
		}
	}
	else //goalRPM_status == GOALRPM_LPF_SETTLED
	{
		interface_checkForDirectionChange(); //We don't want to do this when grbl is toggling direction pin (to generate interrupt)
	
		if( (motor_state_get() == STOPPED) && (adc_goalRPM_get() > MIN_ALLOWED_RPM) ) { motor_run(); }
			
		interface_sendStatus_RPM();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void interface_sendStatus_RPM(void)
{
	int16_t RPM_actualMinusGoal = (int16_t)timing_measuredRPM_get() - (int16_t)adc_goalRPM_get();

	if(motor_state_get() == RUNNING)
	{	
		if     (RPM_actualMinusGoal > -1000) { unoPinA2_low() ; unoPinA4_low() ; } //actualRPM between    0 & 1000 RPM slower than setpoint (or is faster than setpoint) 
		else if(RPM_actualMinusGoal > -2000) { unoPinA2_low() ; unoPinA4_high(); } //actualRPM between 1000 & 2000 RPM slower than setpoint
		else if(RPM_actualMinusGoal > -3000) { unoPinA2_high(); unoPinA4_low() ; } //actualRPM between 2000 & 3000 RPM slower than setpoint
		else                                 { unoPinA2_high(); unoPinA4_high(); } //actualRPM beyond  3000        RPM slower than setpoint	
	}
	else //motor STOPPED
	{
		unoPinA2_input(); //shared with X1 limit switch (X1 only used during X table level)
		unoPinA4_low();
	}
}