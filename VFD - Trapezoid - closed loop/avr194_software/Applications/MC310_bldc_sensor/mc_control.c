//******************************************************************************
//!
//! @file $Id: mc_control.c 980 2008-03-27 09:59:50Z raubree $
//!
//! Copyright (c) 2008 Atmel.
//!
//! @brief Regulation Module (PID)
//!
//! @todo
//! @bug
//******************************************************************************

//_____  I N C L U D E S ___________________________________________________
#include "config.h"
#include "mc_control.h"
#include "mc_interface.h"

#include "dac\dac_drv.h"

U8 duty_cycle = 0;    //!<Parameter to set PWM Duty Cycle after regulation calculation
U8 regulation_type = OPEN_LOOP; //!< Define the type of regulation (OPEN_LOOP or CLOSE_LOOP)

/* Speed regulation variables */
S16 speed_error = 0;      //!<Error calculation
S16 last_speed_error = 0;  //!<Variable for the last error
S16 speed_integral = 0;
S16 speed_integ = 0;
S16 speed_proportional = 0;
S16 speed_derivative = 0;
S16 speed_der = 0;

/* Current regulation variables */
S16 cur_error = 0;      //!<Error calculation
S16 last_cur_error = 0;  //!<Variable for the last error
S16 cur_integral = 0;
S16 cur_integ = 0;
S16 cur_proportional = 0;
S16 cur_derivative = 0;
S16 cur_der = 0;


/************************************************************************************************************/
/*                                  Speed Regulation                                                        */
/************************************************************************************************************/
/**
* @brief use to control speed , speed  regulation loop
* need parameter : Kp_speed, Ki_speed ,Kd_speed and K_speed_scal in config_motor.h
* need to call in Te ms
* @return value of speed, duty cycle on 8 bits
*/
U8 mc_control_speed(U8 speed_cmd)
{
  U8 Duty = 0;
  S32 increment = 0;

  // Error calculation
  speed_error = speed_cmd - mci_get_measured_speed();// value -255 <=> 255

  // proportional term calculation
  speed_proportional = Kp_speed*speed_error;

  // integral term calculation
/*  speed_integral = speed_integral + speed_error;

  if(speed_integral >  255) speed_integral =  255;
  if(speed_integral < -255) speed_integral = -255;

  speed_integ = Ki_speed*speed_integral;
*/
  speed_integral = Ki_speed*(speed_integral + speed_error);

  if(speed_integral >  255) speed_integral =  255;
  if(speed_integral < -255) speed_integral = -255;

  // derivative term calculation
  /*speed_derivative = speed_error - last_speed_error;

  if(speed_derivative >  255) speed_derivative =  255;
  if(speed_derivative < -255) speed_derivative = -255;

  speed_der = Kd_speed*speed_derivative;

  last_speed_error = speed_error;*/

  // Duty Cycle calculation
  increment = speed_proportional + speed_integ;
  //increment += speed_der;
  increment = increment >> K_speed_scal;

  // Variable saturation
  if(increment >= (S16)(255)) Duty = 255;
  else
  {
    if(increment <= (S16)(0)) Duty =   0;
    else Duty = (U8)(increment);
  }

  // return Duty Cycle
  return Duty;
}

/************************************************************************************************************/
/*                                  Current Regulation                                                      */
/************************************************************************************************************/
/**
* @brief use to control current , current  regulation loop
* need parameter : Kp_cur, Ki_cur ,Kd_cur and K_cur_scal in config_motor.h
* need to call in Te ms
* @return value of current, duty cycle on 8 bits
*/
U8 mc_control_current(U8 cur_cmd)
{
  U8 Duty = 0;
  S32 increment = 0;

  // Error calculation
  cur_error = cur_cmd - (mci_get_measured_current());// value -255 <=> 255

  // proportional term calculation
  cur_proportional = Kp_cur*cur_error;

  // integral term calculation
  cur_integral = cur_integral + cur_error;

  if(cur_integral >  255) cur_integral =  255;
  if(cur_integral < -255) cur_integral = -255;

  cur_integ = Ki_cur*cur_integral;

  // derivative term calculation
  /*cur_derivative = cur_error - last_cur_error;

  if(cur_derivative >  255) cur_derivative =  255;
  if(cur_derivative < -255) cur_derivative = -255;

  cur_der = Kd_cur*cur_derivative;

  last_cur_error = cur_error;*/

  // Duty Cycle calculation
  increment = cur_proportional + cur_integ;
  //increment += cur_der;
  increment = increment >> K_cur_scal;

  // Variable saturation
  if(increment >= (S16)(255)) Duty = 255;
  else
  {
    if(increment <= (S16)(0)) Duty =   0;
    else Duty = (U8)(increment);
  }

  // return Duty Cycle
  return Duty;
}



/******************************************************************************/
/*                                Selection of Regulation Loop                */
/******************************************************************************/

//! @brief launch speed control or no regulation
//! @post new duty cycle on PWM
void mc_regulation_loop()
{
  switch(regulation_type)
  {
    case OPEN_LOOP     : duty_cycle = mci_get_ref_speed();break;
    case SPEED_LOOP    : duty_cycle = mc_control_speed(2*mci_get_ref_speed());break;
    case CURRENT_LOOP  : duty_cycle = mc_control_current(mc_get_potentiometer_value());break;
    default : break;
  }
}


//! @brief set type of regulation
//! @post Open loop regulation Set
void mc_set_open_loop(){regulation_type = OPEN_LOOP;}


//! @brief set type of regulation
void mc_set_speed_loop(){regulation_type = SPEED_LOOP;}


//! @brief set type of regulation
void mc_set_current_loop(){regulation_type = CURRENT_LOOP;}


//! @brief set type of regulation
U8 mc_get_duty_cycle()
{
  return duty_cycle;
}

