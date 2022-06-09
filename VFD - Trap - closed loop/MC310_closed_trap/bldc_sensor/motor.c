#include "grBLDC.h"

//Motor interface

uint8_t motorStatus = STOPPED;
uint8_t motorDirection = CW;

////////////////////////////////////////////////////////////////////////////////////////

uint8_t motor_state_get(void) { return motorStatus; }

////////////////////////////////////////////////////////////////////////////////////////

void motor_init()
{
  motor_stop();
  motor_direction_set(CW);
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

//JTS2doNow: Direction never set in code.  Fine for now.
//JTS2doNow: If direction_now != direction_previous, need to stop motor first, then spin other way. //PID loop might take care of this automatically
void    motor_direction_set(uint8_t direction) { (direction == CCW) ? (motorDirection = CCW) : (motorDirection = CW); }
uint8_t motor_direction_get(void) { return motorDirection; }