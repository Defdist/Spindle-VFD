#ifndef _ADC_H_
	#define _ADC_H_

    #define ADCFREE  0
    #define ADCBUSY  1

    // ADC scheduler definitions
    #define ADC_MEASURING_NEXT     0
    #define ADC_MEASURING_GOAL_RPM 1
    #define ADC_MEASURING_CURRENT  2

    void adc_init(void);

    void adc_scheduler(uint8_t channel);

    uint16_t adc_goalRPM_get(void);
    void     adc_goalRPM_set(uint16_t adcResult_RPM);

#endif
