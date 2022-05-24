//******************************************************************************
//! @file $RCSfile: comparator_drv.h,v $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the prototypes and the macros of the
//!        library of functions of:
//!             - COMPARATOR
//!             - for AT90PWMxx4.
//! The following prototypes need some #define's of "at90pwmxx4_drv.h" file.
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//! This file has been validated with AVRStudio-413549/WinAVR-20070525.
//!
//! @version $Revision: 1.00 $ $Name:  r.aubree $
//!
//! @todo
//! @bug
//******************************************************************************


#ifndef _COMPARATOR_DRV_H_
#define _COMPARATOR_DRV_H_

//_____ I N C L U D E S ____________________________________________________


//! @defgroup COMP_module Comparator Module
//! COMP Module
//! @{
//_____ M A C R O S ________________________________________________________

   //! @defgroup COMP_macros Comparator Macros
   //! Low level macros that permit the use of the COMP of the product.
   //! @{



      //! @defgroup Comp_0_config() Configure Comparator 0
      //! All parameters must be set in definitions
      //! @{
#define Comp_0_config() \
   AC0CON = (COMP0_ENABLE_BIT_VALUE<<AC0EN)| \
            (COMP0_INTERRUPT_ENABLE<<AC0IE)| \
            (COMP0_INTERRUPT_SELECT<<AC0IS0)| \
            (COMP_CLOCK_SOURCE<<ACCKSEL)| \
            (COMP0_NEG_INPUT_SELECT<<AC0M0);
      //! @}



      //! @defgroup Comp_1_config() Configure Comparator 1
      //! All parameters must be set in definitions
      //! @{
#define Comp_1_config() \
   AC1CON = (COMP1_ENABLE_BIT_VALUE<<AC1EN)| \
            (COMP1_INTERRUPT_ENABLE<<AC1IE)| \
            (COMP1_INTERRUPT_SELECT<<AC1IS0)| \
            (COMP1_CAPTURE_ENABLE<<AC1ICE)| \
            (COMP1_NEG_INPUT_SELECT<<AC1M0);
      //! @}


      //! @defgroup Comp_2_config() Configure Comparator 2
      //! All parameters must be set in definitions
      //! @{
#define Comp_2_config() \
   AC2CON = (COMP2_ENABLE_BIT_VALUE<<AC1EN)| \
            (COMP2_INTERRUPT_ENABLE<<AC1IE)| \
            (COMP2_INTERRUPT_SELECT<<AC1IS0)| \
            (COMP2_NEG_INPUT_SELECT<<AC1M0);
      //! @}



      //! @defgroup Comp_3_config() Configure Comparator 3
      //! All parameters must be set in definitions
      //! @{
#define Comp_3_config() \
   AC3CON = (COMP3_ENABLE_BIT_VALUE<<AC1EN)| \
            (COMP3_INTERRUPT_ENABLE<<AC1IE)| \
            (COMP3_INTERRUPT_SELECT<<AC1IS0)| \
            (COMP3_NEG_INPUT_SELECT<<AC1M0);
      //! @}




//_____ D E F I N I T I O N S ______________________________________________
#define COMP_DISABLE 0
#define COMP_ENABLE 1

#define COMP_DISABLE_INTERRUPT 0
#define COMP_ENABLE_INTERRUPT 1

#define COMP_INTERRUPT_ON_OUTPUT_TOGGLE 0
#define COMP_INTERRUPT_ON_OUTPUT_FALLING_EDGE 2
#define COMP_INTERRUPT_ON_OUTPUT_RISING_EDGE 3

#define COMP_USE_VREF_DIV640 0
#define COMP_USE_VREF_DIV320 1
#define COMP_USE_VREF_DIV213 2
#define COMP_USE_VREF_DIV160 3
#define COMP_USE_BANDGAP 4
#define COMP_USE_DAC_OUTPUT 5
#define COMP_USE_NEGATIVE_PIN 6

#define COMP_CLOCK_IO 0
#define COMP_CLOCK_PLL 1

#define COMP_CAPTURE_DISABLE 0
#define COMP_CAPTURE_ENABLE 1

//! @}

#endif  // _COMPARATOR_DRV_H_

