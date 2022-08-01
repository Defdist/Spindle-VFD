#include "grBLDC.h"

volatile uint8_t runControlLoop = FALSE;

volatile uint16_t motorRPM_measured = 0;

////////////////////////////////////////////////////////////////////////////////////////

uint8_t timing_runControlLoop_get(void)          { return runControlLoop; }
void    timing_runControlLoop_set(uint8_t state) { runControlLoop = state; }

////////////////////////////////////////////////////////////////////////////////////////

//Configure 8b Timer0 //count up to OCR0A
//interrupt occurs when timer value is OCR0A
//interrupt causes main control loop to execute
void timing_timer0_init(void)
{
  TCCR0A = (1<<WGM01); //set timer mode=CTC, don't connect timer to any output pins
  TCCR0B = (1<<CS01)|(1<<CS00); //prescale Timer0 clock to CPU/64 prescaler //MUST also change TIMER0_TICK_PERIOD_us constant!
  OCR0A  = TIMER0_COUNTS_TO; // f_interrupt = 1/(16MHz/64DIV)*(OCR0A+1) //OCR0A=7: 32us tick (512 clocks @ 16 MHz)
  TIMSK0 = (1<<OCIE0A); // Output compare A Match interrupt Enable
}

////////////////////////////////////////////////////////////////////////////////////////

//Timer0 interrupt occurs when timer hits 'OCR0A' value
//used to run main control loop 
ISR(TIMER0_COMPA_vect) { timing_runControlLoop_set(TRUE); }

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

//configure 16b Timer1: count up to 2^16
//used to calculate RPM (by measuring time between HallB rising edges)
void timing_timer1_init(void)
{
  TCCR1A = 0; //set timer mode=normal, don't connect timer to any output pins
  TCCR1B = (0<<CS12)|(1<<CS11)|(1<<CS10); //prescale Timer1 clock to CPU/64 prescaler //MUST also change TIMER1_TICK_PERIOD_us constant!
  TIMSK1 = (1<<TOIE1); //generate interrupt each time an overflow occurs
}

////////////////////////////////////////////////////////////////////////////////////////

//used to determine actual spindle RPM
//Timer1 increments every 4us ( 1/[16MHz/64] )
//Timer1 overflow interrupt occurs if no HallB rising edge occurs after ~262 milliseconds (2^16 * 4us) //HallB interrupt resets TCNT1 to zero)
//The value on Timer1 is the time between each Hall_B rising edge
ISR(TIMER1_OVF_vect)
{
  //timer1 hit max value //spindle isn't spinning
  TCNT1 = 0; //set Timer1 value to 0 //don't reset... we only want interrupt to fire once
  timing_measuredRPM_set(0);
}

////////////////////////////////////////////////////////////////////////////////////////

inline void timing_calculateRPM(void)
{
  uint16_t timerCount = TCNT1; //retrieve 16b timer value
  TCNT1 = 0; //reset Timer 1 ASAP (to minimize jitter)
  
  #define MICROSECONDS_PER_SECOND 1000000
  #define SECONDS_PER_MINUTE 60
  #define BLDC_NUM_POLE_PAIRS 4
  #define SHEAVE_RATIO 2

  //Derivation:
    //timeSinceLastInterrupt_us = timerCount * TIMER1_TICK_PERIOD_us = timerCount * 4
    //hallFrequency_Hz = 1 / (timeSinceLastInterrupt_us * 1E-6)
    //shaftRPM_BLDC = (hallFrequency_Hz / BLDC_NUM_POLE_PAIRS) * SECONDS_PER_MINUTE
    //spindleRPM = shaftRPM_BLDC * SHEAVE_RATIO
  #define TIMER1_SPINDLE_RPM_CONSTANT (uint32_t)((SHEAVE_RATIO * MICROSECONDS_PER_SECOND * SECONDS_PER_MINUTE) / (BLDC_NUM_POLE_PAIRS * TIMER1_TICK_PERIOD_us))
  
  uint16_t spindleRPM_measured = TIMER1_SPINDLE_RPM_CONSTANT / timerCount; //executes in 625 ns (10 clock cycles)
  //Examples:
    //when spindleRPM_measured is 10000, timerCount was   750
    //when spindleRPM_measured is  9987, timerCount was   751
    //when spindleRPM_measured is  9973, timerCount was   752
    //when spindleRPM_measured is  9000, timerCount was   834
    //when spindleRPM_measured is  8000, timerCount was   938
    //when spindleRPM_measured is  7987, timerCount was   939   
    //when spindleRPM_measured is  7000, timerCount was  1071
    //when spindleRPM_measured is  6000, timerCount was  1250
    //when spindleRPM_measured is  5000, timerCount was  1500
    //when spindleRPM_measured is  4000, timerCount was  1875
    //when spindleRPM_measured is  3000, timerCount was  2500
    //when spindleRPM_measured is  2000, timerCount was  3750
    //when spindleRPM_measured is  1000, timerCount was  7500
    //when spindleRPM_measured is   115, timerCount was 65217 //close to 2^16 counter limit

  #ifdef AVERAGE_RPM_MEASUREMENT
    static uint8_t sampleCount = 0;
    static uint32_t sumOfSamples = 0;

    sumOfSamples += spindleRPM_measured;
    if(++sampleCount > NUM_SAMPLES_PER_RPM_CALCULATION)
    {
      sampleCount = 0;
      timing_measuredRPM_set(sumOfSamples>>POWER_OF__NUM_SAMPLES_PER_RPM_CALCULATION);
      sumOfSamples = 0;
    }
  
  #else
    timing_measuredRPM_set(spindleRPM_measured); 
  #endif
}

////////////////////////////////////////////////////////////////////////////////////////

uint16_t timing_measuredRPM_get(void) { return motorRPM_measured; }

////////////////////////////////////////////////////////////////////////////////////////

void timing_measuredRPM_set(uint16_t measured_speed) { motorRPM_measured = measured_speed; }



