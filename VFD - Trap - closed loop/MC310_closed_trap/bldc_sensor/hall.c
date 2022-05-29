//Allegro A4910 MOSFET driver functions

#include "grBLDC.h"

//JTS2doNow: T0 is 8 bits, while T1 is 16 bits.  Swap T0<->T1.
static uint8_t ovf_timer = 0; // variable "ovf_timer" is use to simulate a 16 bits timer with 8 bits timer

uint8_t goalRPM_ADC_value = 0;//!<Motor Input to set the motor speed

uint8_t motorSpeed_measured = 0;

////////////////////////////////////////////////////////////////////////////////////////

uint8_t hall_goalRPM_get(void) { return goalRPM_ADC_value; }
void hall_goalRPM_set(uint8_t ADC_value) { goalRPM_ADC_value = ADC_value; }

////////////////////////////////////////////////////////////////////////////////////////

void hall_measuredRPM_set(uint8_t measured_speed) { motorSpeed_measured = measured_speed; }
uint8_t hall_measuredRPM_get(void) { return motorSpeed_measured; }

////////////////////////////////////////////////////////////////////////////////////////

inline uint8_t hall_getPosition(void)
{
  //Example: if Hall GRN & YEL are high, the result is 0b00000110
  uint8_t state = ((PIND & (1<<PIND1)) >> (PIND1-0)) | //Hall BLU //LSB
                  ((PINC & (1<<PINC1)) >> (PINC1-1)) | //Hall YEL
                  ((PIND & (1<<PIND2)) >> (PIND2-2));   //Hall GRN //MSB

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

  uint8_t hallB_state = 0;
  static uint8_t hallB_state_previous = 0;

  if (PINC & (1<<PINC1) ) { hallB_state = HALL_B_HIGH; }
  else                    { hallB_state = HALL_B_LOW;  }

  if ( (hallB_state          == HALL_B_HIGH ) &&
       (hallB_state_previous == HALL_B_LOW  )  )
  {
    //rising edge just occurred on Hall B
    hall_calculateRPM(); //estimate speed on Hall_B rising edge
  }

  hallB_state_previous = hallB_state;
}

////////////////////////////////////////////////////////////////////////////////////////

//JTS2doNow: This should be inlined because it's called inside ISR
void hall_calculateRPM(void)
{
  static uint8_t sampleCount = 1;
  static uint16_t sumOfSamples = 0;

  uint16_t timer_value;
  uint32_t new_measured_speed;

  // Two 8 bits variables are use to simulate a 16 bits timers
  timer_value = (ovf_timer<<8) + TCNT0;

  if (timer_value == 0) {timer_value += 1 ;} // prevent DIV by 0 in next line
  
  new_measured_speed = K_SPEED / timer_value;
  
  if(new_measured_speed > 255) new_measured_speed = 255; // Variable saturation


  #ifdef AVERAGE_SPEED_MEASUREMENT
    // To avoid noise an average is realized on 8 samples
    sumOfSamples += new_measured_speed;
    if(sampleCount >= NUM_SAMPLES_PER_RPM_CALCULATION)
    {
      sampleCount = 1;
      hall_measuredRPM_set(sumOfSamples >> 3);
      sumOfSamples = 0;
    }
    else sampleCount++;
  #else
    // else get the real speed
    hall_measuredRPM_set(new_measured_speed);
  #endif

  // Reset Timer 0 register and variables
  TCNT0=0x00;
  ovf_timer = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

/******************************************************************************/
/******************************************************************************/
/*         TIMER 0 : Speed Measurement                                        */
/******************************************************************************/
/******************************************************************************/

/**
 * @brief Timer 0 Configuration
 * The timer 0 is used to generate an IT when an overflow occurs
 * @pre None
 * @post Timer0 initialized.
*/
void hall_init_rpm_timer0(void)
{
  TCCR0A = 0;
  TCCR0B = (1<<CS02)|(0<<CS01)|(0<<CS00); // 256 prescaler (16us)
  TIMSK0 = (1<<TOIE0);
}

////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief Timer0 Overflow for speed measurement
  * @pre configuration of timer 0
  * @post generate an overflow when the motor turns too slowly
*/
ISR(TIMER0_OVF_vect)
{
  TCNT0=0x00;
  ovf_timer++;
  // if they are no commutation after 125 ms
  // 125 ms = (61<<8) * 8us
  if(ovf_timer >= 100)
  {
    ovf_timer = 0;
    hall_measuredRPM_set(0);
  }
}