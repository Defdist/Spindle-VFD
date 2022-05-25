#include "grBLDC.h"

#define PSWAP0 2
#define PSWAP1 3
#define PSWAP2 4

uint8_t overcurrent = FALSE;


                        
static uint8_t inrush_mask_flag = FALSE;
static uint16_t inrush_delay = 0;

uint8_t g_tick = FALSE;             //!< Use for control the sampling period value

uint8_t current_EOC = FALSE; //End Of Conversion Flag

static char ADC_stateMachine = ADC_UNITIALIZED;
static char ADC_hardwareStatus = FREE;  // ADC State //running = BUSY //not running = FREE

////////////////////////////////////////////////////////////////////////////////////////

/******************************************************************************/
/******************************************************************************/
/*        Hardware Initialization                                             */
/******************************************************************************/
/******************************************************************************/


//! @brief mc_motor_init_HW : Hardware Initialization
//! @post initialization of hardware
void mc_motor_init_HW(void)
{
  // Output Pin configuration (used by PSC outputs)
  // PD0 => UH     PB7 => UL
  // PC0 => VH     PB6 => VL
  // PB0 => WH     PB1 => WL

  // Set MOSFET Drive pins low (soo all FETs are off when set to output in next step)
  PORTB &= ~(1<<PORTB7 | 1<<PORTB6 | 1<<PORTB1 | 1<<PORTB0);
  PORTC &= ~(1<<PORTC0);
  PORTD &= ~(1<<PORTD0);

  // Set PSC MOSFET pins to output
  DDRB = (1<<DDB7)|(1<<DDB6)|(1<<DDB1)|(1<<DDB0);
  DDRC = (1<<DDC0);
  DDRD = (1<<DDD0);
  
  //Enable A4910 (FET driver IC)
  A4910pinPB4_reset_Init(); //configure pin to digital output
  A4910_Enable(); //enable MOSFET driver

  // Set to disable digital input circuitry on all pins used as analog inputs.
  // This reduces power consumption, particularly when an analog signal is near Vcc/2.
  // Digital Inputs for comparators are not disabled.
  DIDR1 = (1<<ADC9D)|(1<<ADC8D); //CUR_B & CUR_C ADC inputs
  DIDR0 = (1<<ADC5D)|(1<<ADC6D); //CUR_A ADC input
  
  //vref_source(); // Select the Vref Source
  //JTS2doLater: need to use 2.56 internal reference when measuring phase currents (absolute accuracy)
  //JTS2doLater: need to use VCC when measuring PWM from 328p (ratiometric)
  //The first ADC measurement after each switch should be discarded
  ADCSRB &= ~(1<<ISRCEN); //disable 100 uA current source on AREF pin.
  ADCSRB |= (1<<AREFEN); //connect AREF pin to the internal analog reference.
  
  //Select the Vref Source
  Adc_enable_external_vref();

  init_adc();
  Adc_config();
  //Amp1_config(); //JTS2doLater: Configure phase current amplifiers
  
  // Be careful : initialize DAC and Over_Current before PWM.
  // DAC is used for over current level
  //JTS2doLater: Handle overcurrent differently... AVR194 routes the DAC output to another micro
  //JTS2doLater: I've disconnected the DAC register from the pin, but right now no overcurrent.
  //Dac_config();
  /* set the overcurrent level */
  //Dac_set_8_bits(IMAX);
    
  hall_init_rpm_timer0();
  mc_motor_init_timer1();

  //JTS2doLater: We'll eventually use these to throttle back current, using 1V1 bandgap 
  Comp_0_config();
  Comp_1_config();
  Comp_2_config();
  
  //JTS rewrote
  // Use PCINT17 to detect change on H1 (A) sensor
  // Use PCINT18 to detect change on H3 (C) sensor
  PCMSK2 = ( (1<<PCINT17) | (1<<PCINT18) );
  // Use PCINT9 to detect change on H2 (B) sensor
  PCMSK1 = (1<<PCINT9);
  // Enable pin change interrupts on PCMSK1 & 2
  PCICR = ( (1<<PCIE1) | (1<<PCIE2) );

  Start_pll_64_mega(); // Start the PLL and use the 64 MHz PLL output
  Wait_pll_ready();

  PSC_Init();
}

////////////////////////////////////////////////////////////////////////////////////////

//! @brief PSC Init : Initialize the PSC according to the settings in config.h
void PSC_Init (void)
{
   Psc_set_module_A(A_SA_VAL,A_RA_VAL,A_SB_VAL);
   Psc_set_module_B(B_SA_VAL,B_RA_VAL,B_SB_VAL);
   Psc_set_module_C(C_SA_VAL,C_RA_VAL,C_SB_VAL);
   Psc_set_register_RB(RB_VAL);

   Psc_config();

   Psc_config_input_0(PSC_OVERLAP_ENABLE,\
                      PSC_USE_PIN,\
                      PSC_USE_LOW_LEVEL,\
                      PSC_INPUT_FILTER_ENABLE,\
                      PSC_SYNCHRONOUS_OUTPUT_CONTROL,\
                      PSC_INPUT_NO_ACTION);

   Psc_config_input_1(PSC_OVERLAP_ENABLE,\
                      PSC_USE_COMPARATOR,\
                      PSC_USE_HIGH_LEVEL,\
                      PSC_INPUT_FILTER_ENABLE,\
                      PSC_SYNCHRONOUS_OUTPUT_CONTROL,\
                      PSC_INPUT_NO_ACTION);

   Psc_config_input_2(PSC_OVERLAP_ENABLE,\
                      PSC_USE_PIN,\
                      PSC_USE_LOW_LEVEL,\
                      PSC_INPUT_FILTER_ENABLE,\
                      PSC_SYNCHRONOUS_OUTPUT_CONTROL,\
                      PSC_INPUT_NO_ACTION);

   PIFR = (1<<PEV2)|(1<<PEV1)|(1<<PEV0)|(1<<PEOP);
   PIM = (1<<PEVE1);

   Psc_run();
}

////////////////////////////////////////////////////////////////////////////////////////

/***************************************************************************/
/***************************************************************************/
/*     All functions for motor's phases commutation                        */
/***************************************************************************/
/***************************************************************************/



//////////////////////////////////////////////////////////////////////////////////////////////////

//Set the duty cycle values in the PSC according to the value calculate by the regulation loop
void psc_setDutyCycle(uint8_t level)
{
  uint8_t duty;
  duty = level;

  #if ((CURRENT_DECAY == SLOW_DECAY_SYNCHRONOUS)||(CURRENT_DECAY == FAST_DECAY_SYNCHRONOUS))
    uint8_t dutydt;   /* duty with dead time */
    if (duty >= DEADTIME) {dutydt = duty - DEADTIME;}
  #endif
   
  Psc_lock();

  // Duty = 0   => Duty Cycle   0%
  // Duty = 255 => Duty Cycle 100%
 
  #if (CURRENT_DECAY == FAST_DECAY)
    Psc_set_module_A(duty,A_RA_VAL,duty);
    Psc_set_module_B(duty,B_RA_VAL,duty);
    Psc_set_module_C(duty,C_RA_VAL,duty);
  #else
  #if ((CURRENT_DECAY == SLOW_DECAY_SYNCHRONOUS)||(CURRENT_DECAY == FAST_DECAY_SYNCHRONOUS))
    Psc_set_module_A(duty,A_RA_VAL,dutydt);
    Psc_set_module_B(duty,B_RA_VAL,dutydt);
    Psc_set_module_C(duty,C_RA_VAL,dutydt);
  #else
    Psc_set_module_A(duty,A_RA_VAL,0);
    Psc_set_module_B(duty,B_RA_VAL,0);
    Psc_set_module_C(duty,C_RA_VAL,0);
  #endif
#endif
   
  Psc_unlock();
}

//////////////////////////////////////////////////////////////////////////////////////////////////

//Set commutation outputs based on sensor position
void mc_commutateFETs(uint8_t hallState)
{
    if ( mci_motorState_get() == STOPPED ) { turnOffAllFETs(); }
    else //motor == RUNNING
    {
      psc_setDutyCycle( pid_dutyCycle_get() );

      if(mci_motorDirection_get() == CCW)
      {
          switch(hallState)
          {
              case 1: Set_Q5Q2(); break;
              case 2: Set_Q1Q4(); break;
              case 3: Set_Q5Q4(); break;
              case 4: Set_Q3Q6(); break;
              case 5: Set_Q3Q2(); break;
              case 6: Set_Q1Q6(); break;
              default: turnOffAllFETs(); break;
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
              default: turnOffAllFETs(); break;
          }
      }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////

/******************************************************************************/
/******************************************************************************/
/*    TIMER 1 :  generate the g_tick                                          */
/******************************************************************************/
/******************************************************************************/

/**
 * @brief timer 1 Configuration
 * Use to generate a 256us tick for sampling speed regulation
 * @pre None
 * @post An interrupt all 256us
*/
void mc_motor_init_timer1(void)  //JTS2doNow: swap with counter 0, which uses software 16 bit.
{
  TCCR1A = 0; //Normal port operation + Mode CTC
  TCCR1B = 1<<WGM12 | 1<<CS11 | 1<<CS10 ; // Mode CTC + clock prescaler=64
  TCCR1C = 0;
  OCR1AH = 0; //output compare register high byte
  OCR1AL = 63; // f ocra = 1/(16MHz/64)*(63+1) = 256 us tick
  TIMSK1=(1<<OCIE1A); // Output compare A Match interrupt Enable
}

////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief Launch the regulation loop (see main.c) .
  * @pre configuration of timer 1 registers
  * @post g_tick use in main.c for regulation loop
*/
ISR(TIMER1_COMPA_vect) //main tick //timer configured in mc_motor_init_timer1()
{
  g_tick = TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

/******************************************************************************/
/******************************************************************************/
/*       ADC use for current and potentiometer measurement                    */
/******************************************************************************/
/******************************************************************************/

//! @brief Launch the sampling procedure to get current value
//! @pre amplifier and IT initialization
//! @post Set the End Of Conversion flag

ISR(ADC_vect)
{
  Adc_select_channel(ADC_INPUT_GND); /* release the amplified channel */
  if(ADC_stateMachine == ADC_MEASURE_REQUESTED_RPM) hall_goalRPM_set(Adc_get_8_bits_result());
  if(ADC_stateMachine == ADC_MEASURE_CURRENT) mci_motor_measuredCurrent_integrate(Adc_get_10_bits_result());
  ADC_hardwareStatus = FREE;
}

////////////////////////////////////////////////////////////////////////////////////////

void mc_ADC_Scheduler(void)
{
  switch(ADC_stateMachine)
  {
  case ADC_UNITIALIZED:
    ADC_hardwareStatus = FREE;
    ADC_stateMachine = ADC_MEASURE_CURRENT;
    break;

  //JTS2doNow: Confusing... case doesn't match ADC action
  case ADC_MEASURE_CURRENT:
    //ADC just finished measuring current... now we need to configure the ADC to measure desired RPM
    if(ADC_hardwareStatus == FREE)
    {
      ADC_hardwareStatus = BUSY;
      Adc_left_adjust_result();
      Adc_start_conv_channel(ADC_INPUT_ADC5); //configure ADC to measure desired RPM (from grbl)
      ADC_stateMachine = ADC_MEASURE_REQUESTED_RPM;
    }
    break;

  case ADC_MEASURE_REQUESTED_RPM:
    //ADC just finished measuring goal RPM... now we need to configure the ADC to measure current
    if(ADC_hardwareStatus == FREE)
    {
      ADC_hardwareStatus = BUSY;
      Adc_right_adjust_result();
      Adc_start_conv_channel(ADC_INPUT_AMP1); /* get current on amplifier 1 */
      ADC_stateMachine = ADC_MEASURE_CURRENT; //this case gets current sensor
    }
    break;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////

// //Disable overcurrent detection during startup (inrush current)
// void mc_disableOvercurrentDuringStartup(void)
// {
//   inrush_delay = (uint16_t) 500;
//   inrush_mask_flag = TRUE;
  
//   //disable over current
//   Psc_config_input_1(PSC_OVERLAP_ENABLE,\
//                      PSC_USE_COMPARATOR,\
//                      PSC_USE_HIGH_LEVEL,\
//                      PSC_INPUT_FILTER_ENABLE,\
//                      PSC_SYNCHRONOUS_OUTPUT_CONTROL,\
//                      PSC_INPUT_NO_ACTION);
// }

//////////////////////////////////////////////////////////////////////////////////////////////////

////manage delay when the overcurrent detection is disabled
//void mc_inrush_task(void)
//{ 
  //if (inrush_mask_flag == TRUE)
  //{
    //if (inrush_delay-- == 0)
    //{
        //inrush_mask_flag = FALSE;
      //
        ////enable over current
        //Psc_config_input_1(PSC_OVERLAP_ENABLE,\
                        //PSC_USE_COMPARATOR,\
                        //PSC_USE_HIGH_LEVEL,\
                        //PSC_INPUT_FILTER_ENABLE,\
                        //PSC_SYNCHRONOUS_OUTPUT_CONTROL,\
                        //PSC_INPUT_HALT);
    //}
  //}
//}
//
//// Overcurrent detection
//#ifdef __GNUC__
  //ISR(PSC_FAULT_vect)
//#else
//#pragma vector = PSC_FAULT_vect
//__interrupt void mc_overcurrent_detect(void)
//#endif
//{
  //PIFR = (1<<PEV1); // clear the interrupt
  //overcurrent = TRUE;
  //mci_motor_stop();
//}

//////////////////////////////////////////////////////////////////////////////////////////////////

void turnOffAllFETs(void)
{
  POC = ( (0<<POEN0A)|(0<<POEN0B) |
          (0<<POEN1A)|(0<<POEN1B) |
          (0<<POEN2A)|(0<<POEN2B) );

  PORTB &= ( ~(1<<PORTB7) ); //turn off Q2
  PORTB &= ( ~(1<<PORTB6) ); //turn off Q4
  PORTB &= ( ~(1<<PORTB0) ); //turn off Q5
  PORTB &= ( ~(1<<PORTB1) ); //turn off Q6
  PORTC &= ( ~(1<<PORTC0) ); //turn off Q3
  PORTD &= ( ~(1<<PORTD0) );  //turn off Q1
}