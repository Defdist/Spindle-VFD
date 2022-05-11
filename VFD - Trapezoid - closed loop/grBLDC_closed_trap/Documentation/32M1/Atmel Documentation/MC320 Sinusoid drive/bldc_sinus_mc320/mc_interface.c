//!
//! @file $RCSfile: mc_interface.c,v $
//!
//! Copyright (c) 2006 Atmel.
//!
//! @brief This module provides High level function for the motor control
//!
//! @version $Revision: 1.5 $
//!

//_____  I N C L U D E S ___________________________________________________

#include "config.h"
#include "mc_interface.h"
#include "mc_control.h"
#include "mc_drv.h"




//_____ M A C R O S ________________________________________________________

//_____ D E F I N I T I O N S ______________________________________________
void   svpwm_init(void);
void   Do_Sensor_Interrupt(void);
void   PSC_Start(void);

//_____ D E C L A R A T I O N S ____________________________________________
Bool mci_direction = CW;             //!<User Input parameter to set motor direction

volatile Bool mci_run_stop  = STOP;  //!<User Input parameter to launch or stop the motor

U8 mci_potentiometer_value = 0; //!<Motor Input to set the motor speed


/*************************************************************************************/
/*           motor starts and stops                                                  */
/*************************************************************************************/


void mci_run(void)
{
   mci_run_stop = RUN;
   Disable_interrupt();
   svpwm_init();
   Do_Sensor_Interrupt();
   Enable_interrupt();
   PSC_Start();
}


void mci_stop(void)
{
   PSC_Stop();
   mci_run_stop = STOP;
}


Bool mci_motor_is_running(void)
{
  return mci_run_stop;
}


/*************************************************************************************/
/*           motor running direction functions                                       */
/*************************************************************************************/

void mci_set_direction(U8 direction)
{
   mci_direction = direction;
}


void mci_forward(void)
{
  mci_direction = CW;
}


void mci_backward(void)
{
  mci_direction = CCW;
}


U8 mci_get_direction(void)
{
  return mci_direction;
}






