//!
//! @file $RCSfile: config.h,v $
//!
//! Copyright (c) 2006 Atmel.
//!
//! @brief This module provide services to define config for AT90PWM2/3
//! Describes the system dependant software configuration.
//! This file is included by all source files in order to access to system wide
//! configuration.
//!
//! @version $Revision: 1.6 $
//!

/*_____ I N C L U D E S ____________________________________________________*/
#include "lib_mcu/compiler.h"

#include <ioavr.h>
#include "inavr.h"

#ifndef _CONFIG_H_
#define _CONFIG_H_
#endif

#define BOARD_ID 1 /* 0:unknown, 1 : MC100, 2 : MC200 */
#define SOFT_ID 2 /* 0:unknown, 1:bldc sensor, 2:bldc sinus, 3:bldc sensorless */
#define REV_ID 1

/*-------------- UART LIB CONFIGURATION ---------------*/

#define BAUDRATE      38400
#define FOSC          16000

#define uart_putchar putchar

/*----------- SOME USEFUL MACROINSTRUCTIONS -----------*/
#define Set_PC7()     PORTC |=  (1<<PORTC7)
#define Clear_PC7()   PORTC &= ~(1<<PORTC7)
#define Toggle_PC7()  PINC  |=  (1<<PINC7)

#define Set_PC1()     PORTC |=  (1<<PORTC1)
#define Clear_PC1()   PORTC &= ~(1<<PORTC1)
#define Toggle_PC1()  PINC  |=  (1<<PINC1)

#define Set_PE1()     PORTE |=  (1<<PE1)
#define Clear_PE1()   PORTE &= ~(1<<PE1)
#define Toggle_PE1()  PINE  |=  (1<<PINE1)

#define Set_PE2()     PORTE |=  (1<<PE2)
#define Clear_PE2()   PORTE &= ~(1<<PE2)
#define Toggle_PE2()  PINE  |=  (1<<PINE2)

#define USE_COMP0
#define COMPARATOR0_IT                          1 //!< 0: Disable Comparator Interrupt    1: Enable Comparator Interrupt
#define COMPARATOR0_IT_EVENT                    0 //!< Comparator Interrupt on outut => 0: toggle     2: falling edge     3: rising edge
#define COMPARATOR0_NEGATIVE_INPUT              2 //!< Comparator negative input selection => 0: vref/6.40  1: vref/3.20  2: vref/2.13  3: vref/1.60  4: ACMPM  5: DAC result

/* MC100 */
#define USE_COMP1
#define COMPARATOR1_IT                          1 //!< 0: Disable Comparator Interrupt    1: Enable Comparator Interrupt
#define COMPARATOR1_IT_EVENT                    0 //!< Comparator Interrupt on outut => 0: toggle     2: falling edge     3: rising edge
#define COMPARATOR1_NEGATIVE_INPUT              2 //!< Comparator negative input selection => 0: vref/6.40  1: vref/3.20  2: vref/2.13  3: vref/1.60  4: ACMPM  5: DAC result

/* MC100 */
#define USE_COMP2
#define COMPARATOR2_IT                          1 //!< 0: Disable Comparator Interrupt    1: Enable Comparator Interrupt
#define COMPARATOR2_IT_EVENT                    0 //!< Comparator Interrupt on outut => 0: toggle     2: falling edge     3: rising edge
#define COMPARATOR2_NEGATIVE_INPUT              2 //!< Comparator negative input selection => 0: vref/6.40  1: vref/3.20  2: vref/2.13  3: vref/1.60  4: ACMPM  5: DAC result

// 64MHz (PLL frequency) / 1333 / 2 = 24 kHz (PWM frequency)
#define	MAX_PWM		1333

#define DEAD_TIME       32     //!< 32 => Dead Time = 0.5 µs at 64MHz
#define MAX_AMPLITUDE  ((MAX_PWM / 2) - DEAD_TIME)


#define AMPLITUDE_IN_OPEN_LOOP 600
#define REGULATION_MODE 1 /* 1 for open loop | 2 for PI */

#define ADVANCE         0 /* hardware dependant - so it's constant */

#define MAX_THETA	80 // equals one sixth of the circle

#define K_SPEED 39500
//!< K_SPEED = (255 * 60 * 4)/(p * t_timer0 * speed_max(rpm))
//!< \n with t_timer0 : 48us at 16MHz
//!< \n with p : the number of pairs of poles
//!< \n 8000 rpm/ 4 pairs/ 16MHz => K_SPEED = 39500
//!< \n speed(rpm) = measured_speed * (60 * 4) / (K_SPEED * t_timer0 * p)
//!< \n (The result must be multiplied by 31.65 to get a value in rpm)


/**
 * @brief  Define the two states of the motor
 */
  enum {RUN = TRUE, STOP = FALSE};

/**
 * @brief  Define Direction of rotor : CCW and CW
 */
  enum {CCW = TRUE, CW = FALSE};


