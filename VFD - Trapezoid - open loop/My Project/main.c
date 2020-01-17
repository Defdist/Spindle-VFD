#include <atmel_start.h>
//#include "avr\iom64m1.h"
#include <adc.h>

#define BLDC_ENABLE_PORT PORTB
#define BLDC_ENABLE_DDR DDRB
#define BLDC_ENABLE_PIN PINB
#define BLDC_ENABLE_BIT 4 //PB4
#define BLDC_ENABLE_MASK (1<<BLDC_ENABLE_BIT)

#define Hall_A_PORT PORTD
#define Hall_A_DDR DDRD
#define Hall_A_PIN PIND
#define Hall_A_BIT 1
#define Hall_A_MASK (1<<Hall_A_BIT)

#define Hall_B_PORT PORTC 
#define Hall_B_DDR DDRC
#define Hall_B_PIN PINC
#define Hall_B_BIT 1
#define Hall_B_MASK (1<<Hall_B_BIT)

#define Hall_C_PORT PORTD
#define Hall_C_DDR DDRD
#define Hall_C_PIN PIND
#define Hall_C_BIT 2
#define Hall_C_MASK (1<<Hall_C_BIT)

#define HALL_A_LOGIC_BIT 2 //for internal storage location. This has NOTHING to do with actual pinout.
#define HALL_B_LOGIC_BIT 1
#define HALL_C_LOGIC_BIT 0

#define FET_A_HIGH_PORT PORTD
#define FET_B_HIGH_PORT PORTC
#define FET_C_HIGH_PORT PORTB
#define FET_A_LOW_PORT PORTB
#define FET_B_LOW_PORT PORTB
#define FET_C_LOW_PORT PORTB

#define FET_A_HIGH_DDR DDRD
#define FET_B_HIGH_DDR DDRC
#define FET_C_HIGH_DDR DDRB
#define FET_A_LOW_DDR DDRB
#define FET_B_LOW_DDR DDRB
#define FET_C_LOW_DDR DDRB

#define FET_A_HIGH_PIN PIND
#define FET_B_HIGH_PIN PINC
#define FET_C_HIGH_PIN PINB
#define FET_A_LOW_PIN PINB
#define FET_B_LOW_PIN PINB
#define FET_C_LOW_PIN PINB

#define FET_A_HIGH_BIT 0 
#define FET_B_HIGH_BIT 0
#define FET_C_HIGH_BIT 0
#define FET_A_LOW_BIT 7
#define FET_B_LOW_BIT 6
#define FET_C_LOW_BIT 1

#define FET_PORTB_MASK ( (1<<FET_C_HIGH_BIT) | (1<<FET_A_LOW_BIT) | (1<<FET_B_LOW_BIT) | (1<<FET_C_LOW_BIT) )
#define FET_PORTC_MASK (1<<FET_B_HIGH_BIT)
#define FET_PORTD_MASK (1<<FET_A_HIGH_BIT)


void hall_init()
{
	//need to set pins to input, no pullup (this is default behavior, so ignoring for now)
}

void phase_init()
{
	//Pull enable pin high
	BLDC_ENABLE_DDR |= BLDC_ENABLE_MASK; //configure as output
	BLDC_ENABLE_PORT |= BLDC_ENABLE_MASK; //set pin high
	
	//configure phases as output
	DDRB |= FET_PORTB_MASK;
	DDRC |= FET_PORTC_MASK;
	DDRD |= FET_PORTD_MASK;
	
	//set pins low
	PORTB &= ~(FET_PORTB_MASK);
	PORTC &= ~(FET_PORTB_MASK);
	PORTD &= ~(FET_PORTB_MASK);
	
	//debug (X1LIMIT)
	DDRD |= (1<<3); //debug set to output
	PORTD |= (1<<3); //debug set X1LIMIT (PD3) low (so we can toggle when errors)
}

uint8_t get_hall_logic()
{
	
	uint8_t temp = 0; //reset state to zero
	if ( (Hall_A_PIN & Hall_A_MASK) ) { temp |= (1<<HALL_A_LOGIC_BIT); }
	if ( (Hall_B_PIN & Hall_B_MASK) ) { temp |= (1<<HALL_B_LOGIC_BIT); }
	if ( (Hall_C_PIN & Hall_C_MASK) ) { temp |= (1<<HALL_C_LOGIC_BIT); }
	return temp;
}


void set_phase(char phase, char set_output_to)
{
	switch (phase) {
		case 'A':
			//PIND |= (1<<3);			
			switch (set_output_to) {
				case 'H':
					FET_A_LOW_PORT &= ~(1<<FET_A_LOW_BIT);//turn low FET off
					FET_A_HIGH_PORT |= (1<<FET_A_HIGH_BIT);//turn high FET on
					break;
				case 'L':
					FET_A_HIGH_PORT &= ~(1<<FET_A_HIGH_BIT);//turn high FET off
					FET_A_LOW_PORT |= (1<<FET_A_LOW_BIT);//turn low FET on
					break;
				case 'Z':
					FET_A_HIGH_PORT &= ~(1<<FET_A_HIGH_BIT);//turn both FETs off
					FET_A_LOW_PORT &= ~(1<<FET_A_LOW_BIT);
					break;
				default: 
					break;
			}
			break;
			
		case 'B':
			switch (set_output_to) {
				case 'H':
					FET_B_LOW_PORT &= ~(1<<FET_B_LOW_BIT);//turn low FET off
					FET_B_HIGH_PORT |= (1<<FET_B_HIGH_BIT);//turn high FET on
					break;
				case 'L':
					FET_B_HIGH_PORT &= ~(1<<FET_B_HIGH_BIT);//turn high FET off
					FET_B_LOW_PORT |= (1<<FET_B_LOW_BIT);//turn low FET on
					break;
				case 'Z':
					FET_B_HIGH_PORT &= ~(1<<FET_B_HIGH_BIT);//turn both FETs off
					FET_B_LOW_PORT &= ~(1<<FET_B_LOW_BIT);
					break;
				default: 
					break;
			}			
			break;
			
		case 'C':			
			switch (set_output_to) {
				case 'H':
					FET_C_LOW_PORT &= ~(1<<FET_C_LOW_BIT);//turn low FET off
					FET_C_HIGH_PORT |= (1<<FET_C_HIGH_BIT);//turn high FET on
					break;
				case 'L':
					FET_C_HIGH_PORT &= ~(1<<FET_C_HIGH_BIT);//turn high FET off
					FET_C_LOW_PORT |= (1<<FET_C_LOW_BIT);//turn low FET on
					break;
				case 'Z':
					FET_C_HIGH_PORT &= ~(1<<FET_C_HIGH_BIT);//turn both FETs off
					FET_C_LOW_PORT &= ~(1<<FET_C_LOW_BIT);
					break;
				default: 
					break;
			}				
			break;
		
		default:
			break;
	}


}


void set_all_phases(char stateA, char stateB, char stateC)
{
	set_phase('A',stateA);
	set_phase('B',stateB);
	set_phase('C',stateC);
}


int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	hall_init();
	phase_init();
	adc_init();
	
	adc_select_channel(ADC_CHANNEL_goalRPM);

	/* Replace with your application code */
	while (1) {
		//if( (adc_read() != 0) ) { //~1.25 volts (Vresult / Vref *256)
			switch ( get_hall_logic() ) {
				case 1: set_all_phases('H','L','Z'); break;
				case 2: set_all_phases('L','Z','H'); break;
				case 3: set_all_phases('Z','L','H'); break;
				case 4: set_all_phases('Z','H','L'); break;
				case 5: set_all_phases('H','Z','L'); break;
				case 6: set_all_phases('L','H','Z'); break;
				case 0: //fall through
				case 7: // fall through 0b000 & 0b111 are invalid hall states
				default:
					set_all_phases('Z','Z','Z');
					break;
			PIND |= (1<<3); //debug... toggle PD3 (X1LIM)
			}
		//} else { PIND |= (1<<3); }
			
	}
}
