//!
//! @file $RCSfile: mc_interface.h,v $
//!
//! Copyright (c) 2006 Atmel.
//!
//! @brief This header module provides High level function for the motor control
//!
//! @version $Revision: 1.3 $
//!

#ifndef _MC_LIB_H_
#define _MC_LIB_H_

#define mci_get_motor_direction() mci_direction

void mci_set_direction(U8 direction);
void mci_run(void);
void mci_stop(void);
void mci_forward(void);
void mci_backward(void);

extern Bool mci_direction;
extern volatile Bool mci_run_stop;

Bool mci_motor_is_running(void);
U8 mci_get_direction(void);

#endif
