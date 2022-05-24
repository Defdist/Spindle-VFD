//Allegro A4910 MOSFET driver functions

#include "grBLDC.h"

inline uint8_t hall_getPosition(void)
{
	//Example: if Hall GRN & YEL are high, the result is 0b00000110
	uint8_t state = ( (PIND & (1<<PIND1)) >> (PIND1-0) ) | //Hall BLU //LSB
                    ( (PINC & (1<<PINC1)) >> (PINC1-1) ) | //Hall YEL
                    ( (PIND & (1<<PIND2)) >> (PIND2-2) );  //Hall GRN //MSB

    return state;
}

////////////////////////////////////////////////////////////////////////////////////////

//Configure interrupt vectors (each time a hall sensor state changes)
ISR( HALL_AC() )  //Hall_A & Hall_C share the same interrupt vector byte
{
  mc_commutateFETs( hall_getPosition() );
}

////////////////////////////////////////////////////////////////////////////////////////

ISR( HALL_B() )
{
  mc_commutateFETs( hall_getPosition() ); 
  if (PINC&(1<<PINC1)) //"is Hall_B logic high?"
  {
    mc_calculateSpeed(); //estimate speed on Hall_B rising edge
    g_mc_read_enable=FALSE; // Wait 1 period
    } else {
    g_mc_read_enable=TRUE;
  } 
}