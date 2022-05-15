//!
//! @file $RCSfile: adc.h,v $
//!
//! Copyright (c) 2006 Atmel.
//!
//! @brief This module provide services to define adc use for AT90PWM2/3
//!
//! @version $Revision: 1.2 $
//!


#ifndef _ADC_H_
#define _ADC_H_


/* Amplifier Configuration */
#define AMP_GAIN_5  0
#define AMP_GAIN_10 1
#define AMP_GAIN_20 2
#define AMP_GAIN_40 3

#define AMP_AUTO_SYNC    0
#define AMP_TRIG_ON_PSC0 1
#define AMP_TRIG_ON_PSC1 2
#define AMP_TRIG_ON_PSC2 3

/* ADC configuration */
#define ADC_INPUT_ADC0    0
#define ADC_INPUT_ADC1    1
#define ADC_INPUT_ADC2    2
#define ADC_INPUT_ADC3    3
#define ADC_INPUT_ADC4    4
#define ADC_INPUT_ADC5    5
#define ADC_INPUT_ADC6    6
#define ADC_INPUT_ADC7    7
#define ADC_INPUT_ADC8    8
#define ADC_INPUT_ADC9    9
#define ADC_INPUT_ADC10   10
#define ADC_INPUT_AMP0    11
#define ADC_INPUT_AMP1    12
#define ADC_INPUT_ISRC    13
#define ADC_INPUT_BANDGAP 14

#define ADC_VREF_AREF     0
#define ADC_VREF_AVCC     1
#define ADC_VREF_INTERNAL 3

#define ADC_TRIG_SRC_FREE_RUNNING    0
#define ADC_TRIG_SRC_ANA_COMP0       1
#define ADC_TRIG_SRC_EXT_IT_0        2
#define ADC_TRIG_SRC_TIM0_COMP_MATCH 3
#define ADC_TRIG_SRC_TIM0_COMP_OVF   4
#define ADC_TRIG_SRC_TIM1_COMP_MATCH 5
#define ADC_TRIG_SRC_TIM1_COMP_OVF   6
#define ADC_TRIG_SRC_TIM1_CAPTURE    7
#define ADC_TRIG_SRC_PSC0            8
#define ADC_TRIG_SRC_PSC1            9
#define ADC_TRIG_SRC_PSC2            10
#define ADC_TRIG_SRC_ANA_COMP1       11
#define ADC_TRIG_SRC_ANA_COMP2       12

#define ADC_PRESCALER_2   0
#define ADC_PRESCALER_2b  1
#define ADC_PRESCALER_4   2
#define ADC_PRESCALER_8   3
#define ADC_PRESCALER_16  4
#define ADC_PRESCALER_32  5
#define ADC_PRESCALER_64  6
#define ADC_PRESCALER_128 7

#endif
