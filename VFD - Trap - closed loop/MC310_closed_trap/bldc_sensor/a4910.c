//Allegro A4910 MOSFET driver functions

#include "grBLDC.h"

void A4910pinPB4_reset_Init(void)   { (DDRB |= (1<<DDB4));     }
void A4910pinPB4_reset_Toggle(void) { (PINB |= (1<<PINB4));    }
void A4910pinPB4_reset_Set(void)    { (PORTB |= (1<<PORTB4));  }
void A4910pinPB4_reset_Clear(void)  { (PORTB &= ~(1<<PORTB4)); }

void A4910_Disable(void) { A4910pinPB4_reset_Clear(); }
void A4910_Enable(void)  { A4910pinPB4_reset_Set();   }