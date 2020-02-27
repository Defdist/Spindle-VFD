//******************************************************************************
//!
//! @file $Id: main.c 2100 2008-09-25 13:01:59Z raubree $
//!
//! Copyright (c) 2008 Atmel.
//!
//! @brief Main module : It is based on an infinite loop
//!
//! @todo
//! @bugs
//******************************************************************************

/* Copyright (c) 2008, Atmel Corporation All rights reserved.
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

#include "config.h"

#include "mc_interface.h"
#include "mc_control.h"
#include "mc_drv.h"

#include "adc\adc_drv.h"

#include "ushell_task.h"

//_____ M A C R O S ________________________________________________________


//_____ D E F I N I T I O N S ______________________________________________

//_____ D E C L A R A T I O N S ____________________________________________
U16 g_regulation_period = 0;  //!< Define the sampling period
U16 motor_speed = 0;          //!< User Speed Order
extern Bool g_tick;           //generated by mc_drv.c Used for sampling time
extern Bool overcurrent;


//! Main Entry
//!
//! The main entry point for the control motor application.\n
//! The mc_regulation_loop() function is launched every 80ms.\n
//!
int main(void)
{

  // init motor
  mc_init();  // launch initialization of the motor application
  
  // Initialyze the communication system for External Command through Uart
  ushell_task_init();

  // Start the motor
  mci_set_ref_speed(0);
  mci_run();
//  mc_set_speed_loop(); // uncomment to activate the speed regulation loop
  
  while(1)
  {
    // Launch regulation loop
    // Timer 1 generate an IT (g_tick) all 250us
    // Sampling period = n * 250us
    if (g_tick == TRUE)
    {
      g_tick = FALSE;

      // Get Current and potentiometer value
      mc_ADC_Scheduler();

      g_regulation_period += 1;
      if ( g_regulation_period >= 40 ) //n * 250us = Te
      {
        g_regulation_period = 0;

        if (ushell_active == FALSE)
        {
          // Set User Speed Command with potentiometer
          mci_set_ref_speed(mc_get_potentiometer_value());
        }
        mc_regulation_loop(); // launch regulation loop
      }
      mc_duty_cycle(mc_get_duty_cycle());
      ushell_task();
      mc_inrush_task();       // manage the inrush current

    }
    if (overcurrent==0)
    {
      Set_PC7();
    }
    else
    {
      Clear_PC7();
    }

  }
}
