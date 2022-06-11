#include "grBLDC.h"

//Spindle RPM PID controller

#ifdef SPINDLE_MODE_OPEN_LOOP
	uint8_t dutyPID = OPEN_LOOP_STATIC_PSC_DUTY_CYCLE;
#elif defined SPINDLE_MODE_CLOSED_LOOP
	uint8_t dutyPID = 0; //Closed loop PSC PWM Duty Cycle //0:255
#else 
#endif

////////////////////////////////////////////////////////////////////////////////////////

uint8_t pid_dutyCycle_get() { return dutyPID; }
void pid_dutyCycle_set(uint8_t newDuty) { dutyPID = newDuty; } 

////////////////////////////////////////////////////////////////////////////////////////

int16_t pid_calculate_proportional(int16_t speedError)
{
  return (SPEED_PID_PROPERTIONAL_COEF * speedError);
}

////////////////////////////////////////////////////////////////////////////////////////

int16_t pid_calculate_integral(int16_t speedError)
{
  static int16_t speed_integrator = 0;

  speed_integrator += speedError;

  if(speed_integrator >  255) { speed_integrator =  255; }
  if(speed_integrator < -255) { speed_integrator = -255; }

  return (SPEED_PID_INTEGRAL_COEF * speed_integrator);
}

////////////////////////////////////////////////////////////////////////////////////////

int16_t pid_calculate_derivative(int16_t speedError)
{
  static int16_t speedError_previous = 0;

  int16_t speed_derivative = (speedError - speedError_previous);
  speedError_previous = speedError;

  if(speed_derivative >  255) speed_derivative =  255;
  if(speed_derivative < -255) speed_derivative = -255;

  return (SPEED_PID_DIFFERENTIAL_COEF * speed_derivative);
}

////////////////////////////////////////////////////////////////////////////////////////

uint8_t pid_dutyCycle_calculate(void)
{
  #ifdef SPINDLE_MODE_CLOSED_LOOP 
    static int16_t summedPID = 0;

    if(adc_goalRPM_get() > MIN_ALLOWED_RPM)
    { 
      int16_t error_actualMinusGoal_RPM = (int16_t)timing_measuredRPM_get() - (int16_t)adc_goalRPM_get();

      if(error_actualMinusGoal_RPM > 0) { summedPID--; }
      else                              { summedPID++; }

      //int16_t TermPID_proportional = pid_calculate_proportional(speedError);
      //int16_t TermPID_integral     = pid_calculate_integral    (speedError);
      //int16_t TermPID_derivative   = pid_calculate_derivative  (speedError);

      // Duty Cycle calculation
      //summedPID = TermPID_proportional + TermPID_integral + TermPID_derivative;
      //summedPID = error_actualRPM_minus_goalRPM;

      // Bound max/min PWM value
      if     ( summedPID > (int16_t)(255) ) { summedPID = 255; }
      else if( summedPID < (int16_t)(125) ) { summedPID = 125; }
      
      dutyPID = summedPID;
    }
    else //(adc_goalRPM_get() < MIN_ALLOWED_RPM)
    {
      summedPID = 0;
	  dutyPID = summedPID;
	  
      motor_stop(); //turn off output stage
    }

  #elif defined SPINDLE_MODE_OPEN_LOOP
    dutyPID = OPEN_LOOP_STATIC_PSC_DUTY_CYCLE;
  #endif
	
  return dutyPID;
}

////////////////////////////////////////////////////////////////////////////////////////

void pid_scheduler(void)
{
  static uint16_t timeSinceLastUpdate_PID = 0;
  
  timeSinceLastUpdate_PID += TIMER0_INTERRUPT_PERIOD_us;

  if(timeSinceLastUpdate_PID >= PID_UPDATE_PERIOD_MICROSECONDS)
  {
    pid_dutyCycle_calculate();
    timeSinceLastUpdate_PID = 0;
  }
}