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

#ifndef _CONFIG_H_
#define _CONFIG_H_

//_____  I N C L U D E S ___________________________________________________

#include "compiler.h"
#include "config_motor.h"



#define BOARD_ID 3 /* 0:unknown, 1 : MC100, 2 : MC200, 3 : MC310 */
#define SOFT_ID 1 /* 0:unknown, 1:bldc sensor, 2:bldc sinus, 3:bldc sensorless */
#define REV_ID 1

/*-------------- UART LIB CONFIGURATION ---------------*/

#define BAUDRATE      38400
#define FOSC          16000

/* DAC configuration */
#define DAC_AUTOTRIG_ENABLE_VALUE        DAC_AUTOTRIG_DISABLE
#define DAC_TRIGGER_SELECTION            DAC_TRIG_WITH_COMP0
#define DAC_LEFT_ADJUST_VALUE            DAC_LEFT_ADJUST
#define DAC_OUTPUT_ENABLE_VALUE          DAC_OUTPUT_DISABLE
#define DAC_ENABLE_VALUE                 DAC_ENABLE


/* Amplifier 1 configuration */
#define AMP1_ENABLE_VALUE                AMP_ENABLE
#define AMP1_INPUT_SHUNT_VALUE           AMP_SHUNT_DISABLE
#define AMP1_GAIN                        AMP_GAIN_5
#define AMP1_CMP1_CONNECTION_VALUE       AMP_CMP_CONNECTED
#define AMP1_CLOCK_SOURCE                AMP_CLOCK_EQ_PSC0


/* ADC configuration */
#define ADC_REF_SOURCE                   ADC_REF_EQ_INT_VREF
#define ADC_ADLAR_VALUE                  ADC_RIGHT_ADJUST_RESULT
#define ADC_CHANNEL                      ADC_INPUT_ADC0
#define ADC_ENABLE_BIT_VALUE             ADC_ENABLE
#define ADC_AUTO_TRIG_ENABLE_VALUE       ADC_AUTO_TRIG_DISABLE
#define ADC_INTERRUPT_ENABLE_VALUE       ADC_INTERRUPT_ENABLE
#define ADC_PRESCALER_SELECT_VALUE       ADC_DIV_CLOCK_BY_4
#define ADC_HIGH_SPEED_MODE_VALUE        ADC_HIGH_SPEED_MODE
#define ADC_CURRENT_SOURCE_ENABLE_VALUE  ADC_CURRENT_SRC_ENABLE
#define ADC_AREF_PIN_ENABLE_VALUE        ADC_AREF_PIN_DISABLE
#define ADC_AUTO_TRIG_SOURCE             ADC_FREE_RUNNING


/* Comparator 0 configuration */
#define COMP0_ENABLE_BIT_VALUE COMP_ENABLE
#define COMP0_INTERRUPT_ENABLE COMP_ENABLE_INTERRUPT
#define COMP0_INTERRUPT_SELECT COMP_INTERRUPT_ON_OUTPUT_TOGGLE
#define COMP_CLOCK_SOURCE COMP_CLOCK_IO
#define COMP0_NEG_INPUT_SELECT COMP_USE_BANDGAP

/* Comparator 1 configuration */
#define COMP1_ENABLE_BIT_VALUE COMP_ENABLE
#define COMP1_INTERRUPT_ENABLE COMP_DISABLE_INTERRUPT
#define COMP1_INTERRUPT_SELECT COMP_INTERRUPT_ON_OUTPUT_TOGGLE
#define COMP1_CAPTURE_ENABLE COMP_CAPTURE_DISABLE
#define COMP1_NEG_INPUT_SELECT COMP_USE_DAC_OUTPUT

/* Comparator 2 configuration */
#define COMP2_ENABLE_BIT_VALUE COMP_ENABLE
#define COMP2_INTERRUPT_ENABLE COMP_ENABLE_INTERRUPT
#define COMP2_INTERRUPT_SELECT COMP_INTERRUPT_ON_OUTPUT_TOGGLE
#define COMP2_NEG_INPUT_SELECT COMP_USE_BANDGAP


// PSC configuration
#define PSC_PRESCALER PSC_NODIV_CLOCK
#define PSC_CLOCK_SOURCE PSC_CLOCK_SOURCE_EQ_PLL

#define PSC_MODE PSC_MODE_CENTERED

#define PSC_OUTPUT_A_POLARITY PSC_OUTPUT_HIGH

//! @brief  Define all current decay types
#define SLOW_DECAY 0
#define FAST_DECAY 1
#define SLOW_DECAY_SYNCHRONOUS 2
#define FAST_DECAY_SYNCHRONOUS 3 // ATmega64M1 only

//! @brief  Select here the current decay type for the application
//#define CURRENT_DECAY SLOW_DECAY
#define CURRENT_DECAY FAST_DECAY
//#define CURRENT_DECAY SLOW_DECAY_SYNCHRONOUS
//#define CURRENT_DECAY FAST_DECAY_SYNCHRONOUS // ATmega64M1 only

#if (CURRENT_DECAY == FAST_DECAY)
#define PSC_OUTPUT_B_POLARITY PSC_OUTPUT_LOW
#else /* SLOW_DECAY or SLOW_DECAY_SYNCHRONOUS or FAST_DECAY_SYNCHRONOUS */
#define PSC_OUTPUT_B_POLARITY PSC_OUTPUT_HIGH
#endif

#define A_SA_VAL 0 //!< POCR0SA = 0 for no pulse at init
#define A_RA_VAL 1 //!< POCR0RA = 1 to synchronize the ADC at the center of the waveform
#define A_SB_VAL 0 //!< POCR0SB = 0 for no pulse at init

#define B_SA_VAL 0 //!< POCR1SA = 0 for no pulse at init
#define B_RA_VAL 1
#define B_SB_VAL 0 //!< POCR1SB = 0 for no pulse at init

#define C_SA_VAL 0 //!< POCR2SA = 0 for no pulse at init
#define C_RA_VAL 1
#define C_SB_VAL 0 //!< POCR2SB = 0 for no pulse at init

#define RB_VAL 255 //!< POCR_RB = 255 => PWM freq = PLL freq / 255

#define DEADTIME 2 //!< Dead Time for the inverter

#define Low(data_w)                ((U8)data_w)
#define High(data_w)               ((U8)(data_w>>8))

/* useful defines when PC3 is required to display events */
#define Init_PC3()   (DDRC |= (1<<DDC3))
#define Toggle_PC3() (PINC |= (1<<PINC3))
#define Set_PC3()    (PORTC |= (1<<PORTC3))
#define Clear_PC3()  (PORTC &= ~(1<<PORTC3))

#define Init_PC7()   (DDRC |= (1<<DDC7))
#define Toggle_PC7() (PINC |= (1<<PINC7))
#define Set_PC7()    (PORTC |= (1<<PORTC7))
#define Clear_PC7()  (PORTC &= ~(1<<PORTC7))

#endif // _CONFIG_H_
