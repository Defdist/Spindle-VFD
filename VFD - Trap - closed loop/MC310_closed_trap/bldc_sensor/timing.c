#include "grBLDC.h"

uint8_t runControlLoop = FALSE;

uint16_t motorRPM_measured = 0;

////////////////////////////////////////////////////////////////////////////////////////

uint8_t timing_runControlLoop_get(void)          { return runControlLoop; }
void    timing_runControlLoop_set(uint8_t state) { runControlLoop = state; }

//////////////////////////////////////////////////////////////////////////////////////////////////

//Configure 8b Timer0
//counter increments every 16 microseconds
//interrupt occurs when timer value hit OCR0A
void timing_timer0_init(void)
{
  TCCR0A = 0; //set timer mode=normal, don't connect timer to any output pins
  TCCR0B = (1<<WGM01)|(1<<CS01)|(1<<CS00); // Mode CTC + clock prescaler=64
  TIMSK0 = (1<<OCIE0A); // Output compare A Match interrupt Enable
  OCR0A = 63; // f ocra = 1/(16MHz/64)*(63+1) = 256 us tick
}

////////////////////////////////////////////////////////////////////////////////////////

//Timer0 interrupt occurs when timer hits 'OCR0A' value
//used to run main control loop 
ISR(TIMER0_COMPA_vect) { timing_runControlLoop_set(TRUE); }

//////////////////////////////////////////////////////////////////////////////////////////////////

//configure 16b Timer1
//increment counter every 16 microseconds
//used to calculate RPM
void timing_timer1_init(void)
{
  TCCR1A = 0; //set timer mode=normal, don't connect timer to any output pins
  TCCR1B = (1<<CS02)|(0<<CS01)|(0<<CS00); // prescale Timer0 clock to CPU/256 prescaler // counter increments every 16us ( 1/[16MHz/256] )
  TIMSK1 = (1<<TOIE1); //generate interrupt each time an overflow occurs (every 4.096 ms, unless the hall state has changed)
}

////////////////////////////////////////////////////////////////////////////////////////

//Timer1 interrupt occurs when timer overflows //~1.05 seconds ( 2^16 * 1/[16MHz/256] )
//if the motor is spinning, then this interrupt should never occur (the Hall_B interrupt should occur first)
//The value on Timer1 is the time between each Hall_B rising edge //used to determine actual RPM
ISR(TIMER1_OVF_vect)
{
  //motor isn't spinning
  TCNT1=0x00; //set Timer1 value to 0
  
  timing_measuredRPM_set(0);
}

////////////////////////////////////////////////////////////////////////////////////////

uint16_t timer1Count_get16bit(void)
{
  uint8_t tempLoByte = TCNT1L; //must read low byte first! //latches high byte into shared register
  uint8_t tempHiByte = TCNT1H; //then read high byte (from shared register)

  return ( (tempHiByte<<8) + tempLoByte );
}

////////////////////////////////////////////////////////////////////////////////////////

inline void timing_calculateRPM(void)
{
  
  uint16_t timerCount = timer1Count_get16bit();
  
  if (timerCount == 0) { timerCount = 1; } // prevent divide-by-0 in next line
  
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

  TCNT1 = 0x00; // Reset Timer 1 value to zero
}

////////////////////////////////////////////////////////////////////////////////////////

void     timing_measuredRPM_set(uint16_t measured_speed) { motorRPM_measured = measured_speed; }
uint16_t timing_measuredRPM_get(void) { return motorRPM_measured; }