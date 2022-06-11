#include "grBLDC.h"

//analog to digital converter

// uint32_t mci_measured_current = 0;

uint16_t goalSpeed_RPM = 0;

uint8_t ADC_stateMachine = ADC_MEASURING_GOAL_RPM; //initial channel to digitize
uint8_t ADC_hardwareStatus = ADCFREE;  //ADC is available to perform conversions

//////////////////////////////////////////////////////////////////////////////////////////////////

//average out noise to prevent rapid RPM hunting
uint16_t filteredValue_counts(uint16_t latest10bSample)
{
#if 1    
	#define NUM_ADC_SAMPLES_TO_AVERAGE 16
    #define POWER_OF__NUM_ADC_SAMPLES_TO_AVERAGE 4

    static uint16_t lastN_samples[NUM_ADC_SAMPLES_TO_AVERAGE] = {0};

    static uint8_t index_latestSample = 0;

    lastN_samples[index_latestSample] = latest10bSample; //store latest sample
    if(++index_latestSample == NUM_ADC_SAMPLES_TO_AVERAGE) { index_latestSample = 0; } //circular buffer rollover

    uint16_t sumOfArrayElements = 0;

    for(uint8_t ii=0; ii<NUM_ADC_SAMPLES_TO_AVERAGE; ii++) { sumOfArrayElements += lastN_samples[ii]; }

    return (sumOfArrayElements>>POWER_OF__NUM_ADC_SAMPLES_TO_AVERAGE);
#else
	return latest10bSample;
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////

//Interrupt generated each time ADC conversion finishes
//using an interrupt so we can add other ADC channels later
//with just one channel, we could set the ADC to free running mode (and remove this ISR)
ISR(ADC_vect)
{
  if(ADC_stateMachine == ADC_MEASURING_GOAL_RPM)
  {
	uint16_t adcResult_counts = Adc_get_10_bits_result(); //~520 counts max (grBLDC goalRPM has DIV2 voltage divider LPF)

	adcResult_counts = filteredValue_counts(adcResult_counts);

    #define ADC_COUNTS_TO_RPM__GAIN     14
    #define ADC_COUNTS_TO_RPM__OFFSET 1360
    //y=mx+b //see ../Documentation/RPM LUT.ods
	
    uint16_t adcResultScaled_goalRPM = (uint16_t)(ADC_COUNTS_TO_RPM__GAIN * adcResult_counts) + ADC_COUNTS_TO_RPM__OFFSET;

	if(adcResultScaled_goalRPM < MIN_ALLOWED_RPM) { a4910_disable(); }
	else                                          { a4910_enable(); }

    adc_goalRPM_set(adcResultScaled_goalRPM);
  }

  // else if(ADC_stateMachine == ADC_MEASURING_CURRENT)
  
  ADC_hardwareStatus = ADCFREE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void adc_init(void)
{
  //disable digital input circuitry on all pins used as analog inputs.
  //reduces power consumption, particularly when an analog signal is near Vcc/2.
  DIDR1 |= (1<<ADC9D)|(1<<ADC8D); //CUR_C & CUR_B ADC inputs
  DIDR0 |= (1<<ADC6D)|(1<<ADC5D); //CUR_A & goalRPM ADC inputs
  //CUR_A   is Pin PB5/ADC6
  //CUR_B   is Pin PC5/ADC9
  //CUR_C   is Pin PC4/ADC8
  //goalRPM is PIN PB2/ADC5

  Adc_enable();
  Adc_set_prescaler(ADC_DIV_CLOCK_BY_4);

  Adc_enable_vcc_vref();
  ADCSRB |= (1<<AREFEN); //connect AREF pin to the internal analog reference.
  ADCSRB &= ~(1<<ISRCEN); //disable 100 uA current source on AREF pin.

  Adc_select_channel(ADC_INPUT_ADC5);  //goalRPM

  Adc_right_adjust_result(); //0b------xx xxxxxxxx
  Adc_enable_high_speed_mode();
  adc_generateInterruptAfterConversion(); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void adc_scheduler(uint8_t channel)
{ 
  if(ADC_hardwareStatus == ADCFREE)
  {
    ADC_hardwareStatus = ADCBUSY;

    switch(channel)
    {
      case ADC_MEASURING_GOAL_RPM:
        Adc_start_conv_channel(ADC_INPUT_ADC5); //configure ADC to measure desired RPM (from grbl)
        ADC_stateMachine = ADC_MEASURING_GOAL_RPM;
        break;

      //case ADC_MEASURING_CURRENT:
      //  break;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////

uint16_t adc_goalRPM_get(void) { return goalSpeed_RPM; }

////////////////////////////////////////////////////////////////////////////////////////

void adc_goalRPM_set(uint16_t newRPM) { goalSpeed_RPM = newRPM; }
