#include <atmel_start.h>
//#include "avr\iom64m1.h"
#include <adc.h>

FUSES = { //set 32M1's fuses.  //Requires avr/io.h
	.low      = 0xFF,
	.high     = 0xD7,
	.extended = 0xFF
};

#define SLOWDOWN_PORT PORTC
#define SLOWDOWN_DDR DDRC
#define SLOWDOWN_PIN PINC
#define SLOWDOWN_BIT 3
#define SLOWDOWN_MASK (1<<SLOWDOWN_BIT)

#define BLDC_ENABLE_PORT PORTB
#define BLDC_ENABLE_DDR DDRB
#define BLDC_ENABLE_PIN PINB
#define BLDC_ENABLE_BIT 4 //PB4
#define BLDC_ENABLE_MASK (1<<BLDC_ENABLE_BIT)

#define BLDC_DIR_PORT PORTB
#define BLDC_DIR_DDR DDRB
#define BLDC_DIR_PIN PINB
#define BLDC_DIR_BIT 3 //PB3
#define BLDC_DIR_MASK (1<<BLDC_DIR_BIT)

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

//setup TC0 to continuously count from 0:127 with auto-reload
//This is used to (poorly) control spindle speed
void timer0_init()
{
	PRR &= ~(1<<PRTIM0);//enable timer
	TCCR0A = 0b10000010; //set to clear on compare
	//TCCR0B = 0b00000101; //divide 16E6/1024 = 15.6 kHz clock, counter resets @   117  Hz
	//TCCR0B = 0b00000100; //divide 16E6/0256 = 62.5 kHz clock, counter resets @   488  Hz
	//TCCR0B = 0b00000011; //divide 16E6/0064 = 250. kHz clock, counter resets @  1.95 kHz
	TCCR0B = 0b00000010; //divide 16E6/0008 = 02.0 MHz clock, counter resets @ 15.63 kHz
	//TCCR0B = 0b00000001; //divide 16E6/0001 = 16.0 MHz clock, counter resets @   125 kHz
	
	OCR0A = 127; //maximum timer value to count up to (before reset); counter continuously counts up from zero to this value 
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
	//DDRD |= (1<<3); //debug set to output  This MUST BE DISABLED OR X LIMIT SWITCH WON'T WORK
	//PORTD |= (1<<3); //debug set X1LIMIT (PD3) low (so we can toggle when errors)
}

uint8_t get_hall_logic()
{
	
	uint8_t temp = 0; //reset state to zero
	if ( (Hall_A_PIN & Hall_A_MASK) ) { temp |= (1<<HALL_A_LOGIC_BIT); }
	if ( (Hall_B_PIN & Hall_B_MASK) ) { temp |= (1<<HALL_B_LOGIC_BIT); }
	if ( (Hall_C_PIN & Hall_C_MASK) ) { temp |= (1<<HALL_C_LOGIC_BIT); }
	return temp;
}

uint8_t is_direction_clockwise()
{
	if ( BLDC_DIR_PIN & BLDC_DIR_MASK ) { return 1;}  //spin CW 
	else { return 0; } //spin CCW
}

void set_phase(char phase, char set_output_to)
{
	switch (phase) {
		case 'A':			
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

/*
uint8_t scale_adc_pwm(uint8_t raw_adc_value)
{
	static const uint8_t lookup_PWM[256] = {  //hacky LUT for open loop speed similar to GG2.  STFP!							  
		0,0,0,0,0,0,0,0,                      //We scale across only first 128 elements because we only use ADC's 7 LSBs
		0,0,0,0,0,0,0,0,                      //due to voltage dividing lowpass filter
		77,77,78,78,79,79,80,80,
		81,81,81,82,82,83,83,84,
		84,85,85,86,86,87,87,88,
		88,89,89,89,90,90,91,91,
		92,92,93,93,94,94,95,95,
		96,96,97,97,97,98,98,99,
		99,100,100,101,101,102,102,103,
		103,104,104,105,105,105,106,106,
		107,107,108,108,109,109,110,110,
		111,111,112,112,112,113,113,114,
		114,115,115,116,116,117,117,118,
		118,119,119,120,120,120,121,121,
		122,122,123,123,124,124,125,125,
		126,126,127,127,128,129,129,129,
		129,129,129,129,129,129,129,129,
		129,129,129,129,129,129,129,129,
		129,129,129,129,129,129,129,129,
		129,129,129,129,129,129,129,129,
		129,129,129,129,129,129,129,129,
		129,129,129,129,129,129,129,129,
		129,129,129,129,129,129,129,129,
		129,129,129,129,129,129,129,129,
		129,129,129,129,129,129,129,129,
		129,129,129,129,129,129,129,129,
		129,129,129,129,129,129,129,129,
		129,129,129,129,129,129,129,129,
		129,129,129,129,129,129,129,129,
		129,129,129,129,129,129,129,129,
		129,129,129,129,129,129,129,129,
		129,129,129,129,129,129,129,129
	};
	return lookup_PWM[raw_adc_value];
}
*/

uint8_t ai_result_delayed = 0;
uint8_t helper_p_control = 0; //controls how quickly rpm changes occur

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	hall_init();
	phase_init();
	adc_init();
	timer0_init();
	

	
	//adc_select_channel(ADC_CHANNEL_goalRPM); // will need to specify if more than one ADC channel monitored

	while (1) {
		uint8_t ai_result = adc_read_latest();
		uint8_t counter_latest = TCNT0 + 1; //count from 1 to 128
		
		if( ai_result != ai_result_delayed ) { //user changed rpm
			helper_p_control++; //increment helper               
			if( helper_p_control >= 100 ) { //only update rpm every n loop cycles
				helper_p_control = 0; //reset helper
				if ( (ai_result > ai_result_delayed) && (ai_result_delayed < 128) ) { ai_result_delayed++; } //new rpm greater than old
				if ( (ai_result < ai_result_delayed) && (ai_result_delayed > 0  ) ) { ai_result_delayed--; } //new rpm less    than old
			}	
		} 
		
		//ai_result_delayed = scale_adc_pwm(ai_result_delayed); //LUT hack to spoof GG2 spindle RPM behavior 
		
		if( counter_latest > ai_result_delayed ) { //if free-running counter value is greater than arduino PWM output, turn off all FETs
			set_all_phases('Z','Z','Z'); //replicate GG2 behavior
		} else { //always true when 'S8000' sent, true half the time when 'S4000', never true when 'S0'
			if( is_direction_clockwise() == 0 ) //spin CCW
			{
				//PIND |= (1<<3); //debug... toggle PD3 (X1LIM)
				switch ( get_hall_logic() ) {
					case 6: set_all_phases('H','L','Z'); break;
					case 5: set_all_phases('L','Z','H'); break;
					case 4: set_all_phases('Z','L','H'); break;
					case 3: set_all_phases('Z','H','L'); break;
					case 2: set_all_phases('H','Z','L'); break;
					case 1: set_all_phases('L','H','Z'); break;
					case 0: //fall through
					case 7: // fall through 0b000 & 0b111 are invalid hall states
					default:
						set_all_phases('Z','Z','Z'); //mainly to catch M5 pulling HallC low (when spindle disabled)
						break;
				}		
			} else { //spin CW
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
						set_all_phases('Z','Z','Z'); //mainly to catch M5 pulling HallC low (when spindle disabled)
						break;
				}
			}
		}
	}
	
}
