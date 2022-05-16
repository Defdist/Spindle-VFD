//******************************************************************************
//!
//! @file $Id: amp_config.h 826 2008-02-28 14:23:24Z raubree $
//!
//! Copyright (c) 2007 Atmel.
//!
//! @brief Firmware Configuration
//!
//!
//! @todo
//! @bug
//******************************************************************************

//_____  I N C L U D E S ___________________________________________________



#ifndef _AMP_CONFIG_H_
#define _AMP_CONFIG_H_


// Amplifier 0 Configuration

#define AMP0_ENABLE_BIT           AMP0_ENABLE

#define AMP0_SHUNT_ENABLE_BIT     AMP0_SHUNT_DISABLE

#define AMP0_GAIN_VAL             AMP0_GAIN_5

#define AMP0_CMP0_CONNECT_BIT     AMP0_CMP0_DISABLE

#define AMP0_CLOCK_SOURCE_VAL     AMP0_ADC_CLK_8


// Amplifier 1 Configuration

#define AMP1_ENABLE_BIT           AMP1_DISABLE

#define AMP1_SHUNT_ENABLE_BIT     AMP1_SHUNT_DISABLE

#define AMP1_GAIN_VAL             AMP1_GAIN_5

#define AMP1_CMP1_CONNECT_BIT     AMP1_CMP1_DISABLE

#define AMP1_CLOCK_SOURCE_VAL     AMP1_ADC_CLK_8


// Amplifier 2 Configuration

#define AMP2_ENABLE_BIT           AMP2_DISABLE

#define AMP2_SHUNT_ENABLE_BIT     AMP2_SHUNT_DISABLE

#define AMP2_GAIN_VAL             AMP2_GAIN_5

#define AMP2_CMP2_CONNECT_BIT     AMP2_CMP2_DISABLE

#define AMP2_CLOCK_SOURCE_VAL     AMP2_ADC_CLK_8




#endif

