/*
 * adc.c
 *
 * Created: 1/16/2020 2:01:49 PM
 *  Author: Windermac
 */ 
#include <adc.h>
#include <atmel_start.h>


void adc_select_vref(uint8_t reference)
{
	//"The user is advised not to write new reference selection values during Free Running mode"
	ADCSRA &= ~(1<<ADSC); //disable free running mode
	//while ( !(ADCSRA & (1<<ADIF)) ) {;} //wait for ADC to stop
	if(reference == VREF_EXT_AVCC) {ADMUX = ( (ADMUX & 0b00111111) | (1<<REFS0) ); } //sets ADMUX to b01xxxxxx
	if(reference == VREF_INT_2V56) {ADMUX |= ( (1<<REFS0) | (1<<REFS1) ); } //sets ADMUX to b11xxxxxx
	ADCSRA |= (1<<ADSC); //enable free running mode
}


void adc_select_channel(uint8_t channel)
{
	//"The user is advised not to write new channel selection values during Free Running mode"
	ADCSRA &= ~(1<<ADSC); //disable free running mode
	while ( !(ADCSRA & (1<<ADIF)) ) {;} //wait for ADC to stop
	if(channel == ADC_CHANNEL_goalRPM) {ADMUX = ( (ADMUX & 0b1100000) | 0b00000101 ); } //ADC5 (single ended)
	//JTS2do: add other channels here
	ADCSRA |= (1<<ADSC); //enable free running mode
}


void adc_init()
{	
	DIDR0 = (1<<ADC5D);//JTS2do: disable digital logic on adc pins (to reduce power)(see DIDR0/DIDR1)
	PRR &= ~(1<<PRADC); //enable system clock to ADC.  This is default value, but just making sure ADC is on
	ADC_goalRPM_PORT &= ~(1<<ADC_goalRPM_BIT); //disable goalRPM pullup resistor

	ADCSRA = 0; //reset to default valuess
	ADCSRA |= 0b00000110; //ADPS: sets ADC clock to 16E6/64 = 250 kHz (max anecdotal supported is clock = 2 MHz).  Conversion takes 13 clock cycles, so ~19 kS/s.
	ADCSRA |= (1<<ADATE); //auto-trigger enable... ADC is just always digitizing.  When we want a value, we just grab the last one acquired
		
	ADCSRB = 0; //reset to default values
	//ADCSRB |= (1<<ADHSM) //uncomment to enable high speed mode.  max ADC rate with this line commented out is 200 kHz 
	ADCSRB |= (1<<AREFEN); //connect analog reference to external AREF pin (with capacitor)
	//ADCSRB 3:0 sets auto-trigger source selection bits 0b0000 is "free running mode", which we're using for now

	
	ADMUX = 0; //reset 
	adc_select_vref(VREF_EXT_AVCC);  //modifies ADMUX, so needs to happen after "ADMUX=0;"
	ADMUX |= (1<<ADLAR); //left adjust ADC result, so that upper 8 bits are in ADCH

	ADCSRA |= (1<<ADEN); //enable ADC (but doesn't actually start)
	ADCSRA |= (1<<ADSC); //start ADC conversion (since we're free running, we only need to set bit once)
}

//returns the latest measurement (8 bits for now)
uint8_t adc_read()
{
	uint8_t adc_result = ADCH; //high byte ADC result
	return adc_result; //only 8 MSBs returned (2 LSBs in ADCL not read).  Search ADLAR to enable 10b (and note this requires two register reads, etc)
}