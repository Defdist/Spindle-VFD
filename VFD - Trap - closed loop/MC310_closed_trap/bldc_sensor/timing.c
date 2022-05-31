#include "grBLDC.h"

uint8_t gTick = FALSE;             //Use to control the sampling period

uint16_t motorSpeed_measured = 0;

//JTS2doNow: T0 is 8 bits, while T1 is 16 bits.  Swap T0<->T1.
uint8_t ovf_timer = 0; // variable "ovf_timer" is use to simulate a 16 bits timer with 8 bits timer

////////////////////////////////////////////////////////////////////////////////////////

uint8_t timing_gTick_get(void) { return gTick; }
void    timing_gTick_set(uint8_t state) { gTick = state; }

////////////////////////////////////////////////////////////////////////////////////////

//interrupt occurs when timer overflows
//launches regulation loop
ISR(TIMER1_COMPA_vect) //main tick
{
  timing_gTick_set(TRUE);
}

//////////////////////////////////////////////////////////////////////////////////////////////////

//configure Timer1
//generate interrupt every 256us
void timing_timer1_init(void)  //JTS2doNow: swap with counter 0, which uses software 16 bit.
{
  TCCR1A = 0; //Normal port operation + Mode CTC
  TCCR1B = 1<<WGM12 | 1<<CS11 | 1<<CS10 ; // Mode CTC + clock prescaler=64
  TCCR1C = 0;
  OCR1AH = 0; //output compare register high byte
  OCR1AL = 63; // f ocra = 1/(16MHz/64)*(63+1) = 256 us tick
  TIMSK1=(1<<OCIE1A); // Output compare A Match interrupt Enable
}

//////////////////////////////////////////////////////////////////////////////////////////////////

//Configure 8b Timer0
//counter increments every 16 microseconds
void timing_timer0_init(void)
{
  TCCR0A = 0; //set timer mode=normal, don't connect timer to any output pins
  TCCR0B = (1<<CS02)|(0<<CS01)|(0<<CS00); // prescale Timer0 clock to CPU/256 prescaler // counter increments every 16us (16MHz/256)
  TIMSK0 = (1<<TOIE0); //generate interrupt each time an overflow occurs (every 4.096 ms, unless the hall state has changed)
}

////////////////////////////////////////////////////////////////////////////////////////

//Timer0 interrupt
//used to measure motor RPM
ISR(TIMER0_OVF_vect)
{
  TCNT0=0x00; //reset Timer0 count (so it can keep counting)
  ovf_timer++; //increment pseudo-16b counter value (ovf_timer is upper byte)
  
  // 125 ms = (61<<8) * 8us
  if(ovf_timer >= 100)
  {
    ovf_timer = 0;
    timing_measuredRPM_set(0); //disable motor if no commutation occurs in 125 ms
  }
}

////////////////////////////////////////////////////////////////////////////////////////

inline void timing_calculateRPM(void)
{
  uint16_t timerCount = (ovf_timer<<8) + TCNT0; //pseudo-16b counter //(ovf_timer variable + Timer0 result)
  
  if (timerCount == 0) { timerCount++; } // prevent divide-by-0 in next line
  
  uint16_t new_measured_speed = K_SPEED / timerCount;
  
  //if(new_measured_speed > 255) new_measured_speed = 255; // Variable saturation

  #ifdef AVERAGE_SPEED_MEASUREMENT
    // To avoid noise an average is realized on 8 samples
    static uint16_t sampleCount = 1;
    static uint16_t sumOfSamples = 0;

    sumOfSamples += new_measured_speed;
    if(sampleCount >= NUM_SAMPLES_PER_RPM_CALCULATION)
    {
      sampleCount = 1;
      timing_measuredRPM_set(sumOfSamples >> 3);
      sumOfSamples = 0;
    }
    else sampleCount++;
  #else
    // else get the real speed
  timing_measuredRPM_set(new_measured_speed); 
  #endif

  // Reset Timer 0 register and variables
  TCNT0=0x00;
  ovf_timer = 0;
}

////////////////////////////////////////////////////////////////////////////////////////

void     timing_measuredRPM_set(uint16_t measured_speed) { motorSpeed_measured = measured_speed; }
uint16_t timing_measuredRPM_get(void) { return motorSpeed_measured; }