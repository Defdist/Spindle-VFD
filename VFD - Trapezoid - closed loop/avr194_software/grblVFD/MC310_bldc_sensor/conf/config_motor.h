/*This file has been prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief This file contains the function declarations
//!
//! - Compiler:           IAR EWAVR and GNU GCC for AVR
//! - Supported devices:  ATMega32M1
//!
//! \author               Atmel Corporation: http://www.atmel.com \n
//!                       Support and FAQ: http://support.atmel.no/
//!
//! ***************************************************************************

/* Copyright (c) 2007, Atmel Corporation All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of ATMEL may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//_____  I N C L U D E S ___________________________________________________


#ifndef _CONFIG_MOTOR_H_
#define _CONFIG_MOTOR_H_


//! @brief  This enumeration contains the 6 differents values for the Hall Sensors
//! See design document. \n In this application, just 3 hall sensor are used
//! Hall Sensor : position 1 to 6
typedef  enum {HS_001=1,HS_010=2,HS_011=3,HS_100=4,HS_101=5,HS_110=6} Hall_Position;


//! @brief  Define the two states of the motor
  enum {RUN = TRUE, STOP = FALSE};


//! @brief  Define Direction of rotor : CCW (counter clock wise) and CW (clock wise)
  enum {CCW = TRUE, CW = FALSE};


// Define type of speed measure and number of samples
//#define AVERAGE_SPEED_MEASUREMENT
#define N_SAMPLE  8

//! @brief  Regulation loop modes
  enum {OPEN_LOOP  = 0, SPEED_LOOP = 1, CURRENT_LOOP = 2};

// Here you have to define your control coefficients

//! @brief  Speed regulation Proportional coefficient
#define Kp_speed 30
//! @brief  Speed regulation Integral coefficient
#define Ki_speed 30
//! @brief  Speed regulation Derivative coefficient
#define Kd_speed 0

//! @brief  Current regulation Proportional coefficient
#define Kp_cur 1
//! @brief  Current regulation Integral coefficient
#define Ki_cur 3
//! @brief  Current regulation Derivative coefficient
#define Kd_cur 0


// All PID coef are multiplied by 2^Kmul
// For exemple : kp = 1 => Kp = 1 * 2^K_scal = 1 * 2^4 = 16
// To get the right result you have to divide the number by 2^K_scal
// So execute a K_scal right shift
//! @brief  Speed regulation scale factor
#define K_speed_scal 4
//! @brief  Current regulation scale factor
#define K_cur_scal 4

// Speed measurement
// K_SPEED = (60 * 255)/(n * t_timer0 * speed_max(rpm))
// with n : number of pairs of poles.
// and t_timer0 : 16us
#define K_SPEED 34152 // max speed : 7000 (MC100 motor)
//#define K_SPEED 11250 // max speed : 17000 (MMT 35-1LS motor)
// if you want to calculate the absolute speed
//   absolute_speed = alpha * measured_speed
//   with alpha = 60 / (n * K_SPEED * t_timer0)

#endif

/* IMAX for DAC is calculated on that way :
   Rshunt = 0.05 Ohm
   Vref = 2.56V
   DAC is left adjust so it is like a 8 bit DAC
   IMAX = imax(amp) * 0.05 * 5 * 256 / 2.56 + 128
   IMAX = imax * 25 + 128
   The result must be less than 254              */

//#define IMAX (4 * 25 + 128) /* 4 amps */
#define IMAX 228
  