#ifndef _ADC_H_
	#define _ADC_H_

    #define ADC_REF_SOURCE                   ADC_REF_EQ_INT_VREF
    #define ADC_ADLAR_VALUE                  ADC_RIGHT_ADJUST_RESULT
    #define ADC_CHANNEL                      ADC_INPUT_ADC0
    #define ADC_ENABLE_BIT_VALUE             ADC_ENABLE
    #define ADC_AUTO_TRIG_ENABLE_VALUE       ADC_AUTO_TRIG_DISABLE
    #define ADC_INTERRUPT_ENABLE_VALUE       ADC_INTERRUPT_ENABLE
    #define ADC_PRESCALER_SELECT_VALUE       ADC_DIV_CLOCK_BY_4
    #define ADC_HIGH_SPEED_MODE_VALUE        ADC_HIGH_SPEED_MODE
    #define ADC_CURRENT_SOURCE_ENABLE_VALUE  ADC_CURRENT_SRC_ENABLE
    #define ADC_AREF_PIN_ENABLE_VALUE        ADC_AREF_PIN_DISABLE
    #define ADC_AUTO_TRIG_SOURCE             ADC_FREE_RUNNING

    void adc_init(void);

    void adc_Scheduler(void);
    
    uint16_t adc_measuredCurrent_get(void);
    void     adc_measuredCurrent_integrate(uint16_t current);

    #define ADCFREE  0
    #define ADCBUSY  1

    // ADC scheduler definitions
    #define ADC_UNITIALIZED           0
    #define ADC_MEASURE_REQUESTED_RPM 1
    #define ADC_MEASURE_CURRENT       2

#endif
