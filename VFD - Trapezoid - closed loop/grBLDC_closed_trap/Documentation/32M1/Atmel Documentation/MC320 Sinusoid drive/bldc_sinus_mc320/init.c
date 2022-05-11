//!
//! @file $RCSfile: init.c,v $
//!
//! Copyright (c) 2006 Atmel.
//!
//! @brief Initialization of peripherals
//!
//! @version $Revision: 1.5 $
//!

//_____  I N C L U D E S ___________________________________________________

#include <ioavr.h>

#include "config.h"
#include "inavr.h"

#include "lib_mcu/comparator/comparator_drv.h"


void init(void)
{
   /*************************************************************************************/
   /*           ports direction configuration                                           */
   /*************************************************************************************/

   DDRB = 0xC3;
   DDRC = 0x8A; 
   DDRD = 0x01;
   DDRE = 0x04; 

   PORTC = 0x06;     /* enable pull up */
   
   
   /*************************************************************************************/
   /*           comparator configuration and activation                                 */
   /*************************************************************************************/

   init_comparator0();    // all three comparators are sensitive to the falling and rising edges
   init_comparator1();    // of the three hall sensors.x
   init_comparator2();
   
   
   
   /*************************************************************************************/
   /*     Timer 0 Configuration : generates the sampling frequency                      */
   /*************************************************************************************/
   
   TCCR0A = (1<<WGM01);   // mode CTC : Clear Timer on Compare
   OCR0A = 0x03;          // one interruption every 64µS @16 Mhz
   TIMSK0 = (1<<OCIE0A);  // allow timer 0 compare interruption when timer=compare 
   Enable_interrupt();    // allow interruptions
   TCCR0B = (1<<CS02);    // RUN TIMER f_quartz = 8 MHz / 256 = 32 kHz
}
