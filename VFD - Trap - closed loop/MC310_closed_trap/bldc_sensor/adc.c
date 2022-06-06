#include "grBLDC.h"

//analog to digital converter

// uint32_t mci_measured_current = 0;

uint16_t goalSpeed_RPM = 0;

uint8_t ADC_stateMachine = ADC_MEASURING_GOAL_RPM; //initial channel to digitize
uint8_t ADC_hardwareStatus = ADCFREE;  //ADC is available to perform conversions

//////////////////////////////////////////////////////////////////////////////////////////////////

//prevent noise from affecting requested RPM
//to do this, send highest RPM value received since last 'reset'
//'reset' occurs when s0 sent via grbl //this is a debug tool for now
uint16_t filteredValue_counts(uint16_t latest10bSample)
{
		static uint16_t max10bSample;
		
		if(latest10bSample < 10) { max10bSample = 0; }
		else if(latest10bSample > max10bSample) { max10bSample = latest10bSample; }
		
		return max10bSample;
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

    adc_goalRPM_set(adcResultScaled_goalRPM);
	
	if(adcResultScaled_goalRPM > 7500) { unoPinA4_high(); } //goalRPM is greater than 7500 rpm
	else                              { unoPinA4_low(); }
	
	if(adcResultScaled_goalRPM < 2000) { unoPinA2_high(); } //goalRPM is less than 2000 rpm
	else                               { unoPinA2_low(); }
  }

  // else if(ADC_stateMachine == ADC_MEASURING_CURRENT)
  // {
  //   adc_measuredCurrent_integrate(Adc_get_10_bits_result());
  // }
  
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

void adc_scheduler(void)
{  
  switch(ADC_stateMachine)
  {
    case ADC_MEASURING_GOAL_RPM:
    if(ADC_hardwareStatus == ADCFREE)
    {
      ADC_hardwareStatus = ADCBUSY;
      Adc_start_conv_channel(ADC_INPUT_ADC5); //configure ADC to measure desired RPM (from grbl)
      ADC_stateMachine = ADC_MEASURING_GOAL_RPM; //right now this is the only case
    }
    break;

    // case ADC_MEASURING_CURRENT:
    // if(ADC_hardwareStatus == ADCFREE)
    // {
    //   ADC_hardwareStatus = ADCBUSY;
    //   Adc_start_conv_channel(ADC_INPUT_ADC6); 
    //   ADC_stateMachine = ADC_MEASURING_GOAL_RPM;
    // }
    // break;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////

//JTS2doNow: We shouldn't be integrating inside these functions... do it wherever they're called
// uint16_t adc_measuredCurrent_get(void) { return (mci_measured_current >> 6); } //mci_measured_current/64

// void adc_measuredCurrent_integrate(uint16_t current) { mci_measured_current = ( (63 * mci_measured_current) + (64 * current) )>>6; }

////////////////////////////////////////////////////////////////////////////////////////

uint16_t adc_goalRPM_get(void) { return goalSpeed_RPM; }

////////////////////////////////////////////////////////////////////////////////////////

void adc_goalRPM_set(uint16_t newRPM) { goalSpeed_RPM = newRPM; }
