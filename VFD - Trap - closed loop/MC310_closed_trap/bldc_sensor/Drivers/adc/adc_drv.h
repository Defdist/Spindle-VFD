//******************************************************************************
//! @file $Id: adc_drv.h 1140 2008-04-17 16:35:50Z raubree $
//!
//! Copyright (c) 2008 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the prototypes and the macros of the
//!        library of functions of:
//!             - ADC (Analog to Digital Converter)
//!             - for ATmega32M1
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//!
//!
//! @todo
//! @bug
//******************************************************************************

#ifndef _ADC_DRV_H_
	#define _ADC_DRV_H_

	//_____ I N C L U D E S ____________________________________________________
	//! @defgroup ADC_module ADC Module
	//! ADC Module
	//! @{
	//_____ M A C R O S ________________________________________________________

	   //! @defgroup ADC_macros ADC Macros
	   //! Low level macros that permit the use of the ADC of the product.
	   //! @{

		  //! @defgroup Turn_on_adc Turn on the ADC
		  //! Turn on the ADC
		  //! @{
	#define Adc_enable()                     (ADCSRA |= (1<<ADEN))
		  //! @}
		  //! @defgroup ADC_alignement_configuration ADC Alignement Configuration
		  //! Configure the Result alignement
		  //! @{
	#define Adc_right_adjust_result()        (ADMUX  &= ~(1<<ADLAR))
	#define Adc_left_adjust_result()         (ADMUX  |=  (1<<ADLAR))
		  //! @}

		  //! @defgroup ADC_high_speed_mode_configuration ADC High Speed Mode Configuration
		  //! Set the high spped mode in case ADC frequency is higher than 200KHz
		  //! @{
	#define Adc_enable_high_speed_mode()     (ADCSRB |=  (1<<ADHSM))
	#define Adc_disable_high_speed_mode()    (ADCSRB &= ~(1<<ADHSM))
		  //! @}


		  //! @defgroup ADC_vref_configuration ADC Vref Configuration
		  //! Configure the Vref
		  //! @{
	#define Adc_enable_internal_vref()       (ADMUX  |=  ((1<<REFS1)|(1<<REFS0)) )
	#define Adc_enable_external_vref()       (ADMUX  &= ~((1<<REFS1)|(1<<REFS0)) )
	#define Adc_enable_vcc_vref()            ( ADMUX  &= ~(1<<REFS1),          \
											   ADMUX  |=  (1<<REFS0) )
		  //! @}

		  //! @defgroup ADC_it_configuration ADC IT Configuration
		  //! Configure the ADC IT
		  //! @{
	#define adc_generateInterruptAfterConversion() (ADCSRA |=  (1<<ADIE) )
	#define adc_disableInterruptAfterConversion()  (ADCSRA &= ~(1<<ADIE) )
	#define Adc_clear_flag()                       (ADCSRA &=  (1<<ADIF) )
		  //! @}

		  //! @defgroup ADC_prescaler_configuration ADC Prescaler Configuration
		  //! Configure the ADC prescaler
		  //! @{
	#define Adc_set_prescaler(prescaler)     (ADCSRA &= ~((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)),\
											 ADCSRA |=  (prescaler) )
		  //! @}

		  //! @defgroup ADC_channel_selection ADC Channel Selection
		  //! Select the ADC channel to be converted
		  //! @{
	#define Adc_clear_mux()                  (ADMUX  &= ~((1<<MUX4)|(1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0)) )
	#define Adc_select_channel(channel) \
			(ADMUX = ( ADMUX & (~((1<<MUX4)|(1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0)))) \
							 | (channel) )
		  //! @}

		  //! @defgroup ADC_start_conversion ADC Start Conversion
		  //! Start the Analog to Digital Conversion
		  //! @{

			 //! @defgroup ADC_start_normal_conversion ADC Start Normal Conversion
			 //! Start the conversion in normal mode
			 //! @{
	#define Adc_start_conv()                 (ADCSRA |= (1<<ADSC) )
	#define Adc_start_conv_channel(channel)  (Adc_select_channel(channel),\
											  Adc_start_conv() )
			 //! @}

			 //! @defgroup ADC_start_idle_conversion ADC Start Idle Conversion
			 //! Start the Analog to Digital Conversion in noise reduction mode
			 //! @{
	#define Adc_start_conv_idle()            SMCR   |=  (1<<SM0)|(1<<SE) )
	#define Adc_start_conv_idle_channel(chl) (Adc_select_channel(chl),\
											  Adc_start_conv_idle() )
	#define Adc_clear_sleep_mode()           (SMCR   &= ~(1<<SM0)|(1<<SE) )
			 //! @}

		  //! @}

		  //! @defgroup ADC_get_x_bits_result ADC Get x Bits Result
		  //! ADC Get x Bits Result
		  //! @{
	#define Adc_get_8_bits_result()          ((uint8_t)(ADCH))
	#define Adc_get_10_bits_result()         ((uint16_t)(ADCL+((uint16_t)(ADCH<<8))))
		  //! @}


		  //! @defgroup Turn_off_adc Turn Off the ADC
		  //! Turn Off the ADC
		  //! @{
	#define Adc_disable()                    (ADCSRA &= ~(1<<ADEN))
		  //! @}

		  //! @defgroup Check conversion is finished or not
		  //! Check conversion status 
		  //! @{
	#define Adc_is_conv_finished()           ((ADCSRA &  (1<<ADIF)) ? TRUE : FALSE)
	#define Adc_is_conv_not_finished()       ((ADCSRA | ~(1<<ADIF)) ? TRUE : FALSE)
	#define Adc_wait_end_of_conversion()     while (ADCSRA & (1<<ADSC))
		  //! @}

		  //! @defgroup Configuration of the ADC
		  //! Configure the ADC
		  //! @{
	
	//JTS: These are the various registers that need to be set to use the ADC //adc_init() does the same thing with functions 
	// #define Adc_config() \
	//   ADMUX  = (ADC_REF_SOURCE<<REFS0)| \
	// 		   (ADC_ADLAR_VALUE<<ADLAR)| \
	// 		   (ADC_CHANNEL<<MUX0); \
	//   ADCSRA = (ADC_ENABLE_BIT_VALUE<<ADEN)| \
	// 		   (0<<ADSC)| \
	// 		   (ADC_AUTO_TRIG_ENABLE_VALUE<<ADATE)| \
	// 		   (0<<ADIF)| \
	// 		   (ADC_INTERRUPT_ENABLE_VALUE<<ADIE)| \
	// 		   (ADC_PRESCALER_SELECT_VALUE<<ADPS0); \
	//   ADCSRB = (ADC_HIGH_SPEED_MODE_VALUE<<ADHSM)| \
	// 		   (ADC_AREF_PIN_ENABLE_VALUE<<AREFEN)| \
	// 		   (ADC_AUTO_TRIG_SOURCE<<ADTS0);
		  //! @}

		  //! @defgroup Configuration of the Amplifier 0
		  //! Configure the Amplifier 0
		  //! @{
	#define Amp0_config() \
	   AMP0CSR = (AMP0_ENABLE_VALUE<<AMP0EN)| \
				 (AMP0_INPUT_SHUNT_VALUE<<AMP0IS)| \
				 (AMP0_GAIN<<AMP0G0)| \
				 (AMP0_CMP0_CONNECTION_VALUE<<AMPCMP0)| \
				 (AMP0_CLOCK_SOURCE<<AMP0TS0);
		  //! @}

		  //! @defgroup Configuration of the Amplifier 1
		  //! Configure the Amplifier 1
		  //! @{

	#define Amp1_config() \
	   AMP1CSR = (AMP1_ENABLE_VALUE<<AMP1EN)| \
				 (AMP1_INPUT_SHUNT_VALUE<<AMP1IS)| \
				 (AMP1_GAIN<<AMP1G0)| \
				 (AMP1_CMP1_CONNECTION_VALUE<<AMPCMP1)| \
				 (AMP1_CLOCK_SOURCE<<AMP1TS0);
		  //! @}

		  //! @defgroup Configuration of the Amplifier 0
		  //! Configure the Amplifier 0
		  //! @{

	#define Amp2_config() \
	   AMP2CSR = (AMP2_ENABLE_VALUE<<AMP2EN)| \
				 (AMP2_INPUT_SHUNT_VALUE<<AMP2IS)| \
				 (AMP2_GAIN<<AMP2G0)| \
				 (AMP2_CMP2_CONNECTION_VALUE<<AMPCMP2)| \
				 (AMP2_CLOCK_SOURCE<<AMP2TS0);
		  //! @}

	   //! @}

	//_____ D E F I N I T I O N S ______________________________________________
	// definitions for ADMUX
	#define ADC_REF_EQ_AREF_PIN   0
	#define ADC_REF_EQ_AVCC_PIN   1
	#define ADC_REF_EQ_INT_VREF   3

	#define ADC_RIGHT_ADJUST_RESULT  0
	#define ADC_LEFT_ADJUST_RESULT   1

	#define ADC_INPUT_ADC0        0
	#define ADC_INPUT_ADC1        1
	#define ADC_INPUT_ADC2        2
	#define ADC_INPUT_ADC3        3
	#define ADC_INPUT_ADC4        4
	#define ADC_INPUT_ADC5        5
	#define ADC_INPUT_ADC6        6
	#define ADC_INPUT_ADC7        7
	#define ADC_INPUT_ADC8        8
	#define ADC_INPUT_ADC9        9
	#define ADC_INPUT_ADC10       10
	#define ADC_INPUT_TEMP_SENSOR 11
	#define ADC_INPUT_VCCDIV4     12
	#define ADC_INPUT_ISRC        13
	#define ADC_INPUT_AMP0        14
	#define ADC_INPUT_AMP1        15
	#define ADC_INPUT_AMP2        16
	#define ADC_INPUT_BANDGAP     17
	#define ADC_INPUT_GND         18
 
	// definitions for ADCSRA
	#define ADC_DISABLE           0
	#define ADC_ENABLE            1
           
	#define ADC_AUTO_TRIG_DISABLE 0
	#define ADC_AUTO_TRIG_ENABLE  1
          
	#define ADC_INTERRUPT_DISABLE 0
	#define ADC_INTERRUPT_ENABLE  1

	#define ADC_DIV_CLOCK_BY_2    0
	#define ADC_DIV_CLOCK_BY_4    2
	#define ADC_DIV_CLOCK_BY_8    3
	#define ADC_DIV_CLOCK_BY_16   4
	#define ADC_DIV_CLOCK_BY_32   5
	#define ADC_DIV_CLOCK_BY_64   6
	#define ADC_DIV_CLOCK_BY_128  7

	// definitions for ADCSRB
	#define ADC_LOW_SPEED_MODE    0
	#define ADC_HIGH_SPEED_MODE   1

	#define ADC_CURRENT_SRC_DISABLE 0           
	#define ADC_CURRENT_SRC_ENABLE  1

	#define ADC_AREF_PIN_DISABLE  0
	#define ADC_AREF_PIN_ENABLE   1

	#define ADC_FREE_RUNNING      0
	#define ADC_TRIG_WITH_INT0    1
	#define ADC_TRIG_WITH_TCM0    2
	#define ADC_TRIG_WITH_TCOVF0  3
	#define ADC_TRIG_WITH_TCM1    4
	#define ADC_TRIG_WITH_TCOVF1  5
	#define ADC_TRIG_WITH_TCCAPT1 6
	#define ADC_TRIG_WITH_PSC0    7
	#define ADC_TRIG_WITH_PSC1    8
	#define ADC_TRIG_WITH_PSC2    9
	#define ADC_TRIG_WITH_CMP0   10
	#define ADC_TRIG_WITH_CMP1   11
	#define ADC_TRIG_WITH_CMP2   12
	#define ADC_TRIG_WITH_CMP3   13

	#define AMP_DISABLE            0
	#define AMP_ENABLE             1

	#define AMP_SHUNT_DISABLE      0
	#define AMP_SHUNT_ENABLE       1

	#define AMP_GAIN_5             0
	#define AMP_GAIN_10            1
	#define AMP_GAIN_20            2
	#define AMP_GAIN_40            3

	#define AMP_CMP_DISCONNECTED   0
	#define AMP_CMP_CONNECTED      1

	#define AMP_CLOCK_EQ_ADC_DIV_8 0
	#define AMP_CLOCK_EQ_TCCM0     1
	#define AMP_CLOCK_EQ_TCOVF0    2
	#define AMP_CLOCK_EQ_TCCMB1    3
	#define AMP_CLOCK_EQ_TCOVF1    4
	#define AMP_CLOCK_EQ_PSC0      5
	#define AMP_CLOCK_EQ_PSC1      6
	#define AMP_CLOCK_EQ_PSC2      7


	//_____ F U N C T I O N S __________________________________________________
	   //! @defgroup ADC_low_level_functions ADC Low Level Fucntions
	   //! ADC Low Level Functions
	   //! @{

	//! Configures the ADC accordingly to the ADC Define Configuration values.
	//! Take care that you have to select the ports which will be converted as
	//! analog inputs thanks to the DIDR0 and DIDR1 registers.
	//!
	

#endif  // ADC_DRV_H
