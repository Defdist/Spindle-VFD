//******************************************************************************
//!
//! @file $Id: mc_interface.c 1137 2008-04-17 16:35:06Z raubree $
//!
//! Copyright (c) 2007 Atmel.
//!
//! @brief Provide Interface Functions with Motor Control
//!
//! @todo
//! @bug
//******************************************************************************

//_____  I N C L U D E S ___________________________________________________
#include "config.h"

#include "mc_interface.h"
#include "mc_control.h"
#include "mc_drv.h"

Bool mci_direction = CW; //!<User Input parameter to set motor direction
Bool mci_run_stop = FALSE;    //!<User Input parameter to launch or stop the motor
U8 mci_ref_speed = 0;        //!<User Input parameter to set motor speed

U8 mci_measured_speed = 0;   //!<Motor Input parameter to get the motor speed
U32 mci_measured_current = 0; //!<Motor Input parameter to get the motor current
U8 mc_potentiometer_value = 0;//!<Motor Input to set the motor speed

extern Bool overcurrent;


/**
* @brief mci_run run the motor with parameter
* @pre initialization  HW and SW
* @post New value in Hall variable
*/
void mci_run(void)
{
  if (!(PCTL & (1<<PRUN))) /* if there is an overcurrent */
  {
    PSC_Init();
  }
  overcurrent = FALSE;
  mci_run_stop = TRUE;
  mc_regulation_loop();
  mc_duty_cycle(mc_get_duty_cycle());
  mc_switch_commutation(mc_get_hall());
  mc_disable_during_inrush(); /* disable overcurrent during inrush */
}

/**
* @brief mci_retry_run retry to run if speed is null
* @pre initialization  HW and SW
* @post New value in Hall variable
*/
void mci_retry_run(void)
{
  mci_run_stop = TRUE;
  mc_regulation_loop();
  mc_duty_cycle(mc_get_duty_cycle());
  mc_switch_commutation(mc_get_hall());
  mc_disable_during_inrush(); /* disable overcurrent during inrush */
}

/**
* @brief get the motor state
* @pre initialization  HW and SW
* @post We know if the motor is running or not
*/
Bool mci_motor_is_running(void)
{
  return mci_run_stop;
}

/**
* @brief mci_stop stop the motor
* And reset the speed measured value.
* @pre motor run (mci_run executed)
* @post motor stop
*/
void mci_stop(void)
{
  mci_run_stop=FALSE;
}

/**
* @brief use to init programm
* @param
* @post configuration of hardware and sotware
* @pre none
*/
void mc_init()
{
  mc_init_HW();
  Enable_interrupt();

  mci_stop();
  mci_forward();
  mci_set_ref_speed(0);
  mc_set_measured_speed(0);
}

/*
* @brief speed modification
* @pre initialization of motor
* @post new value of speed
*/
void mci_set_ref_speed(U8 speed)
{
  mci_ref_speed = speed;
}

/*
* @brief speed visualization
* @pre initialization of motor
* @post get speed value
*/
U8 mci_get_ref_speed(void)
{
  return mci_ref_speed;
}

/*
* @brief direction modification
* @pre initialization of motor
* @post new value of direction
*/
void mci_forward(void)
{
  mci_direction = CW;
}

/*
* @brief direction modification
* @pre initialization of motor
* @post new value of direction
*/
void mci_backward(void)
{
  mci_direction = CCW;
}

/*
* @brief direction visualization
* @pre initialization of motor
* @post get direction value
*/
U8 mci_get_motor_direction(void)
{
  return mci_direction;
}

/**
 * @brief set Measured of speed (for initialization)
 * @pre none
 * @post mci_measured_speed initialized
*/
void mc_set_measured_speed(U8 measured_speed)
{
  mci_measured_speed = measured_speed;
}

/**
 * @brief Measured of speed
 * @return return value of speed (8 bits)
 * @pre none
 * @post none
*/
U8 mci_get_measured_speed(void)
{
  return mci_measured_speed;
}

/**
* @brief Get the current measured in the motor
* @pre Launch ADC scheduler
* @post Get ADC Channel 12 result (Current value on 8bits).
*/
U16 mci_get_measured_current(void)
{
  return mci_measured_current/64;
}

/**
* @brief Set the variable 'mc_measured_current' for initialization.
* @pre none
* @post 'mc_measured_current' set with the current value
*/
void mci_store_measured_current(U16 current)
{
  mci_measured_current = ((63*mci_measured_current)+(64*current))>>6;
}

/**
* @brief Get the potentiometer value
* @pre Launch ADC scheduler
* @post Get ADC Channel 6 result (Potentiometer value on 8bits).
*/
U8 mc_get_potentiometer_value(void)
{
  return mc_potentiometer_value;
}

/**
* @brief Set the 'mc_potentiometer_value' variable with the potentiometer value
* @pre Launch ADC scheduler
* @post 'mc_potentiometer_value' set with the potentiometer value
*/
void mc_set_potentiometer_value(U8 potentiometer)
{
  mc_potentiometer_value = potentiometer;
}

