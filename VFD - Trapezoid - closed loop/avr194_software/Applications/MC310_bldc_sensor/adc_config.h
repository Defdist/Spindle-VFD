//******************************************************************************
//!
//! @file $Id: adc_config.h 892 2008-03-10 17:52:38Z raubree $
//!
//! Copyright (c) 2007 Atmel.
//!
//! @brief ADC Firmware Configuration
//!
//!
//! @todo
//! @bug
//******************************************************************************

//_____  I N C L U D E S ___________________________________________________

#include "config.h"

#ifndef _ADC_CONFIG_H_
#define _ADC_CONFIG_H_

//! @defgroup ADC_defines_configuration_values ADC Defines Configuration Values
//! Defines allowing to init the ADC with the wanted configuration
//! @{
#define _USE_ADC_LIB_

#define ADC_RIGHT_ADJUST_RESULT                 0 //!< 0: Result left adjusted  1: Result right adjusted
#define ADC_HIGH_SPEED_MODE                     1 //
#define VREF_SOURCE                             1 //!< 0: External Vref         1: Internal Vref  2: Vref is connected to Vcc
#define ADC_IT                                  1 //!< 0: No ADC End of Conv IT 1: ADC End of conversion generates an IT
#define ADC_PRESCALER                           4 //!< 2, 4, 8, 16, 32, 64, 128  : The input ADC frequency is the system clock frequency divided by the const value

#endif
