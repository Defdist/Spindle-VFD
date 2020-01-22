//******************************************************************************
//!
//! @file $Id: adc_drv.c 586 2007-12-11 17:28:25Z raubree $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the low level functions for the ADC
//!
//!
//! @todo
//! @bug
//******************************************************************************

//_____  I N C L U D E S ___________________________________________________

#include "adc_config.h"

#ifdef _USE_ADC_LIB_ //!< this define is set in adc_config.h file
#include "adc_drv.h"

//_____ M A C R O S ________________________________________________________


//_____ P R I V A T E    D E C L A R A T I O N _____________________________


//_____ D E F I N I T I O N ________________________________________________


//_____ D E C L A R A T I O N ______________________________________________
//! Configures the ADC accordingly to the ADC Define Configuration values.
//! Take care that you have to select the ports which will be converted as
//! analog inputs thanks to the DIDR0 and DIDR1 registers.
//!
void init_adc(void)
{
    Adc_enable();
#   if (ADC_RIGHT_ADJUST_RESULT == 1)
       Adc_right_adjust_result();
#   elif (ADC_RIGHT_ADJUST_RESULT == 0)
       Adc_left_adjust_result();
#   else
#      error (ADC_RIGHT_ADJUST_RESULT should be 0 or 1... See config.h file)
#   endif

#   if (ADC_HIGH_SPEED_MODE == 1)
       Adc_enable_high_speed_mode();
#   elif (ADC_HIGH_SPEED_MODE == 0)
       Adc_disable_high_speed_mode();
#   else
#      error (ADC_HIGH_SPEED_MODE should be 0 or 1... See config.h file)
#   endif

#   if (ADC_IT == 1)
       Adc_enable_it();
#   elif (ADC_IT == 0)
       Adc_disable_it();
#   else
#      error (ADC_IT should be 0 or 1... See config.h file)
#   endif

#   if (ADC_PRESCALER == 128)
       Adc_set_prescaler(7);
#   elif (ADC_PRESCALER == 64)
       Adc_set_prescaler(6);
#   elif (ADC_PRESCALER == 32)
       Adc_set_prescaler(5);
#   elif (ADC_PRESCALER == 16)
       Adc_set_prescaler(4);
#   elif (ADC_PRESCALER ==  8)
       Adc_set_prescaler( 3);
#   elif (ADC_PRESCALER ==  4)
       Adc_set_prescaler( 2);
#   elif (ADC_PRESCALER ==  2)
       Adc_set_prescaler( 1);
#   else
#      error (ADC_PRESCALER should be 2, 4, 8, 16, 32, 64 or 128... See config.h file)
#   endif
}
#endif // USE_ADC

void init_vref_source (void)
{
#   if (VREF_SOURCE == 2)
       Adc_enable_vcc_vref();
#   elif (VREF_SOURCE == 1)
       Adc_enable_internal_vref();
#   elif (VREF_SOURCE == 0)
       Adc_enable_external_vref();
#   else
#      error (VREF_SOURCE should be 0, 1 or 2... See config.h file)
#   endif
}
