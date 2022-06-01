#include "grBLDC.h"

//Spindle RPM PID controller

uint8_t dutyCycle = 0;    //Closed loop speed regulation PWM Duty Cycle

////////////////////////////////////////////////////////////////////////////////////////

uint8_t pid_dutyCycle_get() { return dutyCycle; }

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
  #if (SPINDLE_MODE == SPINDLE_CLOSED_LOOP) 
    int16_t summedPID = 0;
    int16_t speedError = adc_goalRPM_get() - timing_measuredRPM_get();

    int16_t TermPID_proportional = pid_calculate_proportional(speedError);
    int16_t TermPID_integral     = pid_calculate_integral    (speedError);
    int16_t TermPID_derivative   = pid_calculate_derivative  (speedError);

    // Duty Cycle calculation
    summedPID = TermPID_proportional + TermPID_integral + TermPID_derivative;
    summedPID = summedPID >> K_SPEED_SCALAR;

    // Bound max/min PWM value
    if     ( summedPID >= (int16_t)(255) ) { dutyCycle = 255;                  }
    else if( summedPID <= (int16_t)(  0) ) { dutyCycle =   0;                  }
    else                                   { dutyCycle = (uint8_t)(summedPID); }
  
  #else //(SPINDLE_MODE == SPINDLE_OPEN_LOOP)
    dutyCycle = OPEN_LOOP_STATIC_PSC_DUTY_CYCLE;
  #endif

  return dutyCycle;
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