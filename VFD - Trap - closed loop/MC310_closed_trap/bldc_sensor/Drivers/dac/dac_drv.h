//******************************************************************************
//! @file $Id: dac_drv.h 1139 2008-04-17 16:35:41Z raubree $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the prototypes and the macros of the
//!        library of functions of:
//!             - DAC (Digital to Analog Converter)
//!             - for AT90PWMxx4.
//! The following prototypes need some #define's of "at90pwmxx4_drv.h" file.
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//!
//!
//! @todo
//! @bug
//******************************************************************************

#ifndef _DAC_DRV_H_
#define _DAC_DRV_H_

//_____ I N C L U D E S ____________________________________________________


//! @defgroup DAC_module DAC Module
//! DAC Module
//! @{
//_____ M A C R O S ________________________________________________________

   //! @defgroup DAC_macros DAC Macros
   //! Low level macros that permit the use of the DAC of the product.
   //! @{

      //! @defgroup Turn_on_dac Turn on the DAC
      //! Turn on the DAC
      //! @{
#define Dac_enable()                         (DACON |= (1<<DAEN))
      //! @}

      //! @defgroup Turn_off_dac Turn Off the DAC
      //! Turn Off the DAC
      //! @{
#define Dac_disable()                        (DACON &= ~(1<<DAEN))
      //! @}

      //! @defgroup DAC_alignement_configuration DAC Alignement Configuration
      //! Configure the input data alignement
      //! @{
#define Dac_right_adjust_input()             (DACON  &= ~(1<<DALA))
#define Dac_left_adjust_input()              (DACON  |=  (1<<DALA))
      //! @}


      //! @defgroup DAC_output_configuration DAC Output Configuration
      //! Switch on or off the DAC output
      //! @{
#define Dac_enable_output()                  (DACON  |=  (1<<DAOE))
#define Dac_disable_output()                 (DACON  &= ~(1<<DAOE))
      //! @}

      //! @defgroup DAC_set_input_value DAC Set Input Value
      //! Setart the conversion input conversion value
      //! @{
#define Dac_set_8_bits(dac_in)               (DACH = (uint8_t)(dac_in))
#define Dac_set_10_bits(dac_in)              (DACL = lowByte((uint16_t)(dac_in)), DACH = highByte((uint16_t)(dac_in)))
      //! @}

      //! @defgroup DAC_start_left DAC Start Left Adjust
      //! Start the DAC in basic mode with left adjust
      //! @{
#define Dac_start_left() \
      DACON = (0<<DAATE)| /* DAC Auto Trigger Enable bit */ \
              (0<<DATS0)| /* DAC Trigger Selection bits */ \
              (0<<DALA) | /* Digital to Analog Left Adjust */ \
              (1<<DAOE) | /* Digital to Analog Output Enable bit */\
              (1<<DAEN);  /* DAC Enable */
      //! @}

      //! @defgroup DAC_start_right DAC Start Right Adjust
      //! Start the DAC in basic mode with right adjust
      //! @{
#define Dac_start_right() \
      DACON = (0<<DAATE)| /* DAC Auto Trigger Enable bit */ \
              (0<<DATS0)| /* DAC Trigger Selection bits */ \
              (1<<DALA) | /* Digital to Analog Left Adjust */ \
              (1<<DAOE) | /* Digital to Analog Output Enable bit */\
              (1<<DAEN);  /* DAC Enable */
      //! @}

      //! @defgroup DAC_start_right DAC Start Right Adjust
      //! Start the DAC in basic mode with right adjust
      //! @{
#define Dac_set_value(param) \
       DACL = lowByte(param); \
       DACH = highByte(param);
      //! @}

#define Dac_config() \
      DACON = (DAC_AUTOTRIG_ENABLE_VALUE<<DAATE)| \
              (DAC_TRIGGER_SELECTION<<DATS0)| \
              (DAC_LEFT_ADJUST_VALUE<<DALA) | \
              (DAC_ENABLE_VALUE<<DAEN);
       

//_____ D E F I N I T I O N S ______________________________________________
#define DAC_AUTOTRIG_DISABLE  0
#define DAC_AUTOTRIG_ENABLE   1

#define DAC_TRIG_WITH_COMP0   0
#define DAC_TRIG_WITH_COMP1   1
#define DAC_TRIG_WITH_INT0    2
#define DAC_TRIG_WITH_TCCM0   3
#define DAC_TRIG_WITH_TCOVF0  4
#define DAC_TRIG_WITH_TCCM1   5
#define DAC_TRIG_WITH_TCOVF1  6
#define DAC_TRIG_WITH_TCCAP1  7

#define DAC_RIGHT_ADJUST      0
#define DAC_LEFT_ADJUST       1

#define DAC_OUTPUT_DISABLE    0
#define DAC_OUTPUT_ENABLE     1

#define DAC_DISABLE           0
#define DAC_ENABLE            1

//_____ F U N C T I O N S __________________________________________________
   //! @defgroup DAC_low_level_functions DAC Low Level Fucntions
   //! DAC Low Level Functions
   //! @{

//! Configures the DAC accordingly to the DAC Define Configuration values.
void init_dac(void);

   //! @}

//! @}

#endif  // _DAC_DRV_H_

