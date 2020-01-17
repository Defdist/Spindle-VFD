/*
 * adc.h
 *
 * Created: 1/16/2020 2:02:07 PM
 *  Author: Windermac
 */ 
#include <atmel_start.h>

#define ADC_goalRPM_PORT PORTB
#define ADC_goalRPM_DDR DDRB
#define ADC_goalRPM_PIN PINB
#define ADC_goalRPM_BIT 2  //PB2

//voltage reference enums
#define VREF_EXT_AVCC 0
#define VREF_INT_2V56 1

//ai channel enums
#define ADC_CHANNEL_goalRPM    0 // ADC5 PB2 (ADMUX bxxx00101)
#define ADC_CHANNEL_temp       1 // ADCt --- (ADMUX bxxx01011) internal temperature sensor
#define ADC_CHANNEL_cur_phaseA 2 // ADC6 PB5 (ADMUX bxxx00110)
#define ADC_CHANNEL_cur_phaseB 3 // ADC9 PC5 (ADMUX bxxx01001)
#define ADC_CHANNEL_cur_phaseC 4 // ADC8 PC4 (ADMUX bxxx01000)
#define ADC_CHANNEL_VCCDIV4    5 // VCC/4 (~1.25 volts)

//initialize ADC
void adc_init();

//change voltage reference
void adc_select_vref(uint8_t reference);

//select which ai channel to digitizes
void adc_select_channel(uint8_t channel);

//returns 8b ADC measurement
uint8_t adc_read();