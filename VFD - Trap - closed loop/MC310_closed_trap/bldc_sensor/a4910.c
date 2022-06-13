//Allegro A4910 MOSFET driver functions

//32M1 has the following connections to the A4910:
	//RESETn (pin PB4): pull high to enable A4910
	//DIAG   (pin PC7): A4910 outputs fault conditions on this line

#include "grBLDC.h"

void a4910_init(void)   { (DDRB |= (1<<DDB4)); } //set A4910 reset pin to output

//////////////////////////////////////////////////////////////////////////////////////////////////

void a4910_disable(void) { (PORTB &= ~(1<<PORTB4)); } //set RESETn pin low
void a4910_enable(void)  { (PORTB |= (1<<PORTB4));  } //set RESETn pin high