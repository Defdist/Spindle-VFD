//******************************************************************************
//! 
//! @file $Id: dac_drv.c 587 2007-12-11 17:28:34Z raubree $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the library of functions of:
//!             - DAC (Digital to Analog Converter)
//!             - for AT90PWMxx4.
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//!
//!
//! @todo
//! @bug
//******************************************************************************

//_____  I N C L U D E S ___________________________________________________

#include "dac_config.h"

#ifdef _USE_DAC_LIB_ //!< this define is set on config.h file
#include "dac_drv.h"


//_____ M A C R O S ________________________________________________________


//_____ P R I V A T E    D E C L A R A T I O N _____________________________


//_____ D E F I N I T I O N ________________________________________________


//_____ D E C L A R A T I O N ______________________________________________
//! Configures the DAC accordingly to the DAC Define Configuration values.
void init_dac(void){

    Dac_enable();

#   if (DAC_INPUT_RIGHT_ADJUST == 1)
       Dac_right_adjust_input();
#   elif (DAC_INPUT_RIGHT_ADJUST == 0)
       Dac_left_adjust_input();
#   else
#      error (ADC_RIGHT_ADJUST_RESULT should be 0 or 1... See config.h file)
#   endif

#   if (DAC_OUTPUT_DRIVER == 1)
       Dac_enable_output();
#   elif (DAC_OUTPUT_DRIVER == 0)
       Dac_disable_output();
#   else
#      error (DAC_OUTPUT_DRIVER should be 0 or 1... See config.h file)
#   endif
}

#endif // USE_DAC
