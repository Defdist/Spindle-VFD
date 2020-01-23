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

U8 mc_control_speed(U8 speed_cmd);
U8 mc_control_current(U8 cur_cmd);

void mc_regulation_loop();

void mc_set_open_loop();
void mc_set_speed_loop();
void mc_set_current_loop();

U8 mc_get_duty_cycle();

#endif
