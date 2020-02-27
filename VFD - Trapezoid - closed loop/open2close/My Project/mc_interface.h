//******************************************************************************
//!
//! @file $Id: mc_interface.h 943 2008-03-21 12:28:21Z raubree $
//!
//! Copyright (c) 2007 Atmel.
//!
//! @brief Motor Control Interface Functions
//!
//!
//! @todo
//! @bug
//******************************************************************************

//_____  I N C L U D E S ___________________________________________________

#ifndef _MC_LIB_H_
#define _MC_LIB_H_

extern Bool mci_direction;
extern Bool mci_run_stop;

void mci_run(void);
void mci_retry_run(void);
Bool mci_motor_is_running(void);
void mci_stop(void);
void mc_init(void);

void mci_set_ref_speed(U8 speed);
uint8_t mci_get_ref_speed(void);

void mci_forward(void);
void mci_backward(void);
uint8_t mci_get_motor_direction(void);

void mc_set_measured_speed(uint8_t measured_speed);
uint8_t mci_get_measured_speed(void);

uint16_t mci_get_measured_current(void);
void mci_store_measured_current(uint16_t current);

uint8_t mc_get_potentiometer_value(void);
void mc_set_potentiometer_value(uint8_t potentiometer);

#endif
