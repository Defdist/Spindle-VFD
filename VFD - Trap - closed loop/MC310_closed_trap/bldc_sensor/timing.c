#include "grBLDC.h"

uint8_t runControlLoop = FALSE;

uint16_t motorRPM_measured = 0;

////////////////////////////////////////////////////////////////////////////////////////

uint8_t timing_runControlLoop_get(void)          { return runControlLoop; }
void    timing_runControlLoop_set(uint8_t state) { runControlLoop = state; }

//////////////////////////////////////////////////////////////////////////////////////////////////

//Configure 8b Timer0
//counter increments every 4 microseconds
//interrupt occurs when timer value hit OCR0A
void timing_timer0_init(void)
{
  TCCR0A = (1<<WGM01); //set timer mode=CTC, don't connect timer to any output pins
  TCCR0B = (1<<CS01)|(1<<CS00); //CPU/64 prescaler
  OCR0A  = 7; // f_interrupt = 1/(16MHz/64DIV)*(OCR0A+1) = //OCR0A=7: 32 us tick (512 clocks @ 16 MHz)
  TIMSK0 = (1<<OCIE0A); // Output compare A Match interrupt Enable
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
  TCCR1B = (1<<CS12)|(0<<CS11)|(0<<CS10); // prescale Timer0 clock to CPU/256 prescaler // counter increments every 16us ( 1/[16MHz/256] )
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

inline void timing_calculateRPM(void)
{
  
  uint16_t timerCount = TCNT1; //retrive 16b timer value
  
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