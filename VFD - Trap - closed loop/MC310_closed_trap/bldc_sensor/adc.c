#include "grBLDC.h"

//analog to digital converter

uint32_t mci_measured_current = 0; //!<Motor Input parameter to get the motor current

uint8_t goalRPM_ADC_value = 0;

uint8_t ADC_stateMachine = ADC_UNITIALIZED;
uint8_t ADC_hardwareStatus = ADCFREE;  // ADC State

//////////////////////////////////////////////////////////////////////////////////////////////////

//Interrupt generated each time ADC conversion finishes
ISR(ADC_vect)
{
  Adc_select_channel(ADC_INPUT_GND); /* release the amplified channel */
  if(ADC_stateMachine == ADC_MEASURE_REQUESTED_RPM) { adc_goalRPM_set(Adc_get_8_bits_result()); }
  if(ADC_stateMachine == ADC_MEASURE_CURRENT) { adc_measuredCurrent_integrate(Adc_get_10_bits_result()); }
  ADC_hardwareStatus = ADCFREE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void adc_init(void)
{
  //disable digital input circuitry on all pins used as analog inputs.
  //reduces power consumption, particularly when an analog signal is near Vcc/2.
  DIDR1 = (1<<ADC9D)|(1<<ADC8D); //CUR_C & CUR_B ADC inputs
  DIDR0 = (1<<ADC6D); //CUR_A ADC input
  //JTS: CUR_A is Pin PB5/ADC6
  //JTS: CUR_B is Pin PC5/ADC9
  //JTS: CUR_C is Pin PC4/ADC8

  Adc_enable();
  Adc_left_adjust_result();
  Adc_enable_high_speed_mode();
  adc_generateInterruptAfterConversion();

  //vref_source(); // Select the Vref Source
  //JTS2doLater: need to use 2.56 internal reference when measuring phase currents (absolute accuracy)
  //JTS2doLater: need to use VCC when measuring PWM from 328p (ratiometric)
  //The first ADC measurement after each switch should be discarded
  ADCSRB &= ~(1<<ISRCEN); //disable 100 uA current source on AREF pin.
  ADCSRB |= (1<<AREFEN); //connect AREF pin to the internal analog reference.
  
  //Select the Vref Source
  Adc_enable_external_vref();

  Adc_config();

  #if   (ADC_PRESCALER == 128)
    Adc_set_prescaler(7);
  #elif (ADC_PRESCALER ==  64)
    Adc_set_prescaler(6);
  #elif (ADC_PRESCALER ==  32)
    Adc_set_prescaler(5);
  #elif (ADC_PRESCALER ==  16)
    Adc_set_prescaler(4);
  #elif (ADC_PRESCALER ==   8)
    Adc_set_prescaler( 3);
  #elif (ADC_PRESCALER ==   4)
    Adc_set_prescaler( 2);
  #elif (ADC_PRESCALER ==   2)
    Adc_set_prescaler( 1);
  #else
    #error (ADC_PRESCALER should be 2, 4, 8, 16, 32, 64 or 128... See config.h file)
  #endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void adc_Scheduler(void)
{  
  switch(ADC_stateMachine)
  {
  case ADC_UNITIALIZED:
    ADC_hardwareStatus = ADCFREE;
    ADC_stateMachine = ADC_MEASURE_CURRENT;
    break;

  //JTS2doNow: Confusing... case doesn't match ADC action
  case ADC_MEASURE_CURRENT:
    //ADC just finished measuring current... now we need to configure the ADC to measure desired RPM
    if(ADC_hardwareStatus == ADCFREE)
    {
      ADC_hardwareStatus = ADCBUSY;
      Adc_left_adjust_result();
      Adc_start_conv_channel(ADC_INPUT_ADC5); //configure ADC to measure desired RPM (from grbl)
      ADC_stateMachine = ADC_MEASURE_REQUESTED_RPM;
    }
    break;

  case ADC_MEASURE_REQUESTED_RPM:
    //ADC just finished measuring goal RPM... now we need to configure the ADC to measure current
    if(ADC_hardwareStatus == ADCFREE)
    {
      ADC_hardwareStatus = ADCBUSY;
      Adc_right_adjust_result();
      Adc_start_conv_channel(ADC_INPUT_AMP1); /* get current on amplifier 1 */
      ADC_stateMachine = ADC_MEASURE_CURRENT; //this case gets current sensor
    }
    break;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////

//JTS2doNow: We shouldn't be integrating inside these functions... do it wherever they're called
uint16_t adc_measuredCurrent_get(void) { return (mci_measured_current >> 6); } //mci_measured_current/64

void adc_measuredCurrent_integrate(uint16_t current) { mci_measured_current = ( (63 * mci_measured_current) + (64 * current) )>>6; }

////////////////////////////////////////////////////////////////////////////////////////

uint8_t adc_goalRPM_get(void) { return goalRPM_ADC_value; }
void    adc_goalRPM_set(uint8_t ADC_value) { goalRPM_ADC_value = ADC_value; }
