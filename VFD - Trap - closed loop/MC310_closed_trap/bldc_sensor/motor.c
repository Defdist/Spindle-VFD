#include "grBLDC.h"

//Motor interface

uint8_t motorStatus = STOPPED;
uint8_t motorDirection = MOTOR_CW;

////////////////////////////////////////////////////////////////////////////////////////

uint8_t motor_state_get(void) { return motorStatus; }

////////////////////////////////////////////////////////////////////////////////////////

void motor_init()
{
  motor_stop();
  adc_goalRPM_set(0);
  timing_measuredRPM_set(0);
}

////////////////////////////////////////////////////////////////////////////////////////

void motor_stop(void)
{
  motorStatus = STOPPED;
  a4910_disable();
}

////////////////////////////////////////////////////////////////////////////////////////

void motor_run(void)
{
  motorStatus = RUNNING;

  a4910_enable();
  
  pid_dutyCycle_set(175); //kickstart motor
  psc_commutateOutputWaveforms( 175 );
}

////////////////////////////////////////////////////////////////////////////////////////

void    motor_direction_set(uint8_t direction) { (direction == MOTOR_CCW) ? (motorDirection = MOTOR_CCW) : (motorDirection = MOTOR_CW); }
uint8_t motor_direction_get(void) { return motorDirection; } //This ONLY retrieves the modal state (not the actual pin logic level)