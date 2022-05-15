//!
//! @file $RCSfile: mc_control.h,v $
//!
//! Copyright (c) 2006 Atmel.
//!
//! @brief This module provides services to define config for AT90PWM3 Only
//! This file needs to be include in all files using speed regulation.
//!
//! @version $Revision: 1.2 $
//!

#ifndef _MC_CONTROL_H_
#define _MC_CONTROL_H_

U8 mc_control_speed(U8 speed_cmd);
U8 mc_control_current(U8 cur_cmd);
U8 mc_control_position(S32 Number_of_turns);

void mc_regulation_loop();

void mc_set_Open_Loop();
void mc_set_Speed_Loop();
void mc_set_Current_Loop();
void mc_set_Position_Loop();

U8 mc_get_Duty_Cycle();

#endif
