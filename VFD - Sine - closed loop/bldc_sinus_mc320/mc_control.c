//!
//! @file $RCSfile: mc_control.c,v $
//!
//! Copyright (c) 2006 Atmel.
//!
//! @brief This module provides the regulation loop
//! Type of control : PI means proportionnal, integral.
//!
//! @version $Revision: 1.4 $
//!

#include "config.h"
#include "inavr.h"

/* Speed control variables */
S16 speed_error=0;           //!< Regulation loop error calculation
S16 speed_integral = 0;      //!< Local integral value
S16 speed_integ = 0;         //!< Intermediate integral value
S16 speed_proportional = 0;  //!< Local proportional value

/**************************************************************************************/
/*                          Speed Control                                             */
/**************************************************************************************/
/**
* @brief  speed controller
* @return value of speed (duty cycle on 16 bits)
*         speed_measure has 10 bits resolution
*/
U16 mc_control_speed_16b(U16 speed_ref , U16 speed_measure)     //TT not used in the applicaiton, seems to be a PID controller 
{
   U16 result = 0;
   S16 increment = 0;

   // Error calculation
   //speed_error = speed_ref - speed_measure/2 ;
   speed_error = speed_ref - speed_measure;

   // proportional term calculation : Kp= 7/64=0.1
   speed_proportional = speed_error * 4;

   // integral term calculation
   speed_integral = speed_integral + speed_error;

   // speed integral saturation
   if(speed_integral >  32000) speed_integral =  32000;
   if(speed_integral < -32000) speed_integral = -32000;

   speed_integ = (speed_integral - speed_integral/8 + speed_integral/32) / 16 ;

   // amplitude calculation
   increment = speed_proportional + speed_integ;

   // saturation of the PI output
   if (increment > 0)
   {
      if  (increment <= (S16)(MAX_AMPLITUDE)) result = (S16)increment ;
      else result = MAX_AMPLITUDE ;
   }
   else result = 0;

   // return Duty Cycle
   return result;
}




