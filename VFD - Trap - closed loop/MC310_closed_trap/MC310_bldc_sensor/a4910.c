//Allegro A4910 MOSFET driver functions

#include "grBLDC.h"

A4910pinPB4_reset_Init()   { (DDRB |= (1<<DDB4));     }
A4910pinPB4_reset_Toggle() { (PINB |= (1<<PINB4));    }
A4910pinPB4_reset_Set()    { (PORTB |= (1<<PORTB4));  }
A4910pinPB4_reset_Clear()  { (PORTB &= ~(1<<PORTB4)); }

A4910_Disable() { A4910pinPB4_reset_Clear(); }
A4910_Enable()  { A4910pinPB4_reset_Set();   }