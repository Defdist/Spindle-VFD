//Allegro A4910 MOSFET driver functions

#include "grBLDC.h"

////////////////////////////////////////////////////////////////////////////////////////

void hall_init(void)
{
  // Use PCINT17 to detect change on H1 (A) sensor
  // Use PCINT18 to detect change on H3 (C) sensor
  PCMSK2 = ( (1<<PCINT17) | (1<<PCINT18) );

  // Use PCINT9 to detect change on H2 (B) sensor
  PCMSK1 = (1<<PCINT9);
  
  // Enable pin change interrupts on PCMSK1 & 2
  PCICR |= ( (1<<PCIE1) | (1<<PCIE2) );
}

////////////////////////////////////////////////////////////////////////////////////////

uint8_t hall_getPosition(void)
{
  static uint8_t state_previous = 0;
  static uint8_t numConsecutiveInvalidStates = 0;	
  
  //Build Hall state 0b0000 0BGY (B=BLU, G=GRN, Y=YEL)
  uint8_t state = ( (( (PIND & (1<<PIND1)) >> PIND1) << 2) |  //Hall BLU //MSB
                    (( (PINC & (1<<PINC1)) >> PINC1) << 0) |  //Hall YEL //LSB
                    (( (PIND & (1<<PIND2)) >> PIND2) << 1) ); //Hall GRN

  if( ((state == 0b00000000) || (state == 0b00000111)) && //invalid Hall state (due to H->L or L->H transition)
      (numConsecutiveInvalidStates < 10)                ) 
  {
	  //hall states in transition
	  state = state_previous;
	  numConsecutiveInvalidStates++;
  } 
  else //valid Hall state (or motor is stalled)
  {
	  state_previous = state; //store for next iteration
	  numConsecutiveInvalidStates = 0;
  } 
	  
  return state;
}

////////////////////////////////////////////////////////////////////////////////////////

//Configure interrupt vectors (each time a hall sensor state changes)
ISR( HALL_AC_vect )  //Hall_A & Hall_C share the same interrupt vector byte
{
  psc_commutateOutputWaveforms( pid_dutyCycle_get() );
}

////////////////////////////////////////////////////////////////////////////////////////

ISR( HALL_B_vect )
{
  psc_commutateOutputWaveforms( pid_dutyCycle_get() );

  uint8_t hallB_state = 0;
  static uint8_t hallB_state_previous = 0;

  //determine hallB state (high or low)
  if (PINC & (1<<PINC1) ) { hallB_state = HALL_B_HIGH; }
  else                    { hallB_state = HALL_B_LOW;  }

  if(hallB_state == HALL_B_HIGH)
  {
    if(hallB_state_previous == HALL_B_LOW) 
    {
      //rising edge just occurred on Hall B
      timing_calculateRPM();
	  pid_dutyCycle_calculate();
    }
  }

  hallB_state_previous = hallB_state;
}

