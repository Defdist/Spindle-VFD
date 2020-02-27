//******************************************************************************
//!
//! @file $Id: mc_control.h 943 2008-03-21 12:28:21Z raubree $
//!
//! Copyright (c) 2007 Atmel.
//!
//! @brief Regulation Loop Functions
//!
//!
//! @todo
//! @bug
//******************************************************************************

#ifndef _MC_CONTROL_H_
#define _MC_CONTROL_H_

uint8_t mc_control_speed(uint8_t speed_cmd);
uint8_t mc_control_current(uint8_t cur_cmd);

void mc_regulation_loop();

void mc_set_open_loop();
void mc_set_speed_loop();
void mc_set_current_loop();

uint8_t mc_get_duty_cycle();

#endif
