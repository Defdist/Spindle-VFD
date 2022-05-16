//Allegro A4910 MOSFET driver functions

#include "grBLDC.h"

inline uint8_t hall_getPosition(void)
{
	//Example: if Hall GRN & YEL are high, the result is 0b00000110
	uint8_t state = ( (PIND & (1<<PIND1)) >> (PIND1-0) ) | //Hall BLU //LSB
                    ( (PINC & (1<<PINC1)) >> (PINC1-1) ) | //Hall YEL
                    ( (PIND & (1<<PIND2)) >> (PIND2-2) )   //Hall GRN //MSB

    return state;
}