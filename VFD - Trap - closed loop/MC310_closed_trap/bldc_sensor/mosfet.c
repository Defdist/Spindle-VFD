#include "grBLDC.h"

//MOSFET control

void mosfet_init(void)
{
	// Output Pin configuration (used by PSC outputs)
	// PD0 => UH     PB7 => UL
	// PC0 => VH     PB6 => VL
	// PB0 => WH     PB1 => WL

	// Set MOSFET Drive pins low (soo all FETs are off when set to output in next step)
	PORTB &= ~(1<<PORTB7 | 1<<PORTB6 | 1<<PORTB1 | 1<<PORTB0);
	PORTC &= ~(1<<PORTC0);
	PORTD &= ~(1<<PORTD0);

	// Configure FET pins to output
	DDRB = (1<<DDB7)|(1<<DDB6)|(1<<DDB1)|(1<<DDB0);
	DDRC = (1<<DDC0);
	DDRD = (1<<DDD0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////

//Set commutation outputs based on sensor position
void mosfet_commutate(uint8_t hallState)
{
    if ( motor_state_get() == STOPPED ) { mosfet_turnOffAll(); }
    else //motor == RUNNING
    {
      psc_setDutyCycle( pid_dutyCycle_get() );

      if(motor_direction_get() == CCW) //JTS2doNow: Sample direction pin (PB3) to determine spindle direction
      {
          switch(hallState)
          {
              case 1: Set_Q5Q2(); break;
              case 2: Set_Q1Q4(); break;
              case 3: Set_Q5Q4(); break;
              case 4: Set_Q3Q6(); break;
              case 5: Set_Q3Q2(); break;
              case 6: Set_Q1Q6(); break;
              default: mosfet_turnOffAll(); break;
          }
      }
      else //direction == CW
      {
          switch(hallState)
          {
              case 1: Set_Q1Q6(); break;
              case 2: Set_Q3Q2(); break;
              case 3: Set_Q3Q6(); break;
              case 4: Set_Q5Q4(); break;
              case 5: Set_Q1Q4(); break;
              case 6: Set_Q5Q2(); break;
              default: mosfet_turnOffAll(); break;
          }
      }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void mosfet_turnOffAll(void)
{
  //POC: PSC output configuration
  POC = ( (0<<POEN0A)|(0<<POEN0B) |  //0:disconnect PSC outputs 0A & 0B from I/O pins //1:connect PSC output
          (0<<POEN1A)|(0<<POEN1B) |  //0:disconnect PSC outputs 1A & 1B from I/O pins //1:connect PSC output
          (0<<POEN2A)|(0<<POEN2B) ); //0:disconnect PSC outputs 2A & 2B from I/O pins //1:connect PSC output

  PORTB &= ( ~((1<<PORTB7)|(1<<PORTB6)|(1<<PORTB0)|(1<<PORTB1)) ); //Turn off Q2/Q4/Q5/Q6, respectively
  PORTC &= ( ~(1<<PORTC0) ); //turn off Q3
  PORTD &= ( ~(1<<PORTD0) ); //turn off Q1
}