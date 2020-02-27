//******************************************************************************
//!
//! @file $Id: mc_drv.c 1137 2008-04-17 16:35:06Z raubree $
//!
//! Copyright (c) 2007 Atmel.
//!
//! @brief Driver level : Init, PWM ...
//!
//! @todo
//! @bug
//******************************************************************************

//_____  I N C L U D E S ___________________________________________________

#include "config.h"

#include "mc_drv.h"
#include "mc_interface.h"
#include "mc_control.h"

#include "psc\psc_drv.h"
#include "adc\adc_drv.h"
#include "dac\dac_drv.h"
#include "pll\pll_drv.h"
#include "comparator\comparator_drv.h"

#define PSWAP0 2
#define PSWAP1 3
#define PSWAP2 4

Bool overcurrent = FALSE;

U8 count = 1;     // variable "count" is use to calculate the "average" speed on 'n' samples
U16 average = 0;
static U8 ovf_timer = 0; // variable "ovf_timer" is use to simulate a 16 bits timer with 8 bits timer

static Bool inrush_mask_flag = FALSE;
static U16 inrush_delay = 0;

Bool g_mc_read_enable = FALSE;  // the speed can be read
Bool g_tick = FALSE;             //!< Use for control the sampling period value

Bool current_EOC = FALSE; //End Of Conversion Flag

static char State = CONV_INIT; // State of the ADC scheduler
static char ADC_State = FREE;  // ADC State : running = BUSY not running = FREE

/******************************************************************************/
/******************************************************************************/
/*        Hardware Initialization                                             */
/******************************************************************************/
/******************************************************************************/


//! @brief mc_init_HW : Hardware Initialization
//! @post initialization of hardware
void mc_init_HW(void)
{
  // Output Pin configuration (used by PSC outputs)
  // PD0 => UH     PB7 => UL
  // PC0 => VH     PB6 => VL
  // PB0 => WH     PB1 => WL

  // Warning Output Low for MOSFET Drivers
  PORTB &= ~(1<<PORTB7 | 1<<PORTB6 | 1<<PORTB1 | 1<<PORTB0);
  PORTC &= ~(1<<PORTC0);
  PORTD &= ~(1<<PORTD0);

  // PORT B :
  DDRB = (1<<DDB7)|(1<<DDB6)|(1<<DDB1)|(1<<DDB0);
  // PORT C :
  DDRC = (1<<DDC0);
  // PORT D :
  DDRD = (1<<DDD0);
  
  Init_PC7(); /* PC7 is used to display the overcurrent */

  // Disable Digital Input for amplifier1
  // Digital Inputs for comparators are not disabled.
  DIDR1 = (1<<ADC9D)|(1<<ADC8D);

  // Select the Vref Source
//  init_vref_source ();

//  init_adc();
  Adc_config();
  Amp1_config();
  
  // Be careful : initialize DAC and Over_Current before PWM.
  // DAC is used for oevr current level
  Dac_config();
  /* set the overcurrent level */
  Dac_set_8_bits(IMAX);
    
  mc_init_timer0();
  mc_init_timer1();

  Comp_0_config();
  Comp_1_config();
  Comp_2_config();
  
  // Use PCINT14 to detect change on H2 sensor
  PCMSK1 = (1<<PCINT14);
  PCICR = (1<<PCIE1);

//  Start_pll_32_mega(); // Start the PLL and use the 32 MHz PLL output
  Start_pll_64_mega(); // Start the PLL and use the 64 MHz PLL output
  Wait_pll_ready();


  // => PSCx_Init(Period_Half, Dutyx0_Half, Synchro, Dutyx1_Half)
  PSC_Init();

}




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



/***************************************************************************/
/***************************************************************************/
/*     All functions for motor's phases commutation                        */
/***************************************************************************/
/***************************************************************************/

/**
* @brief Get the value of hall sensors (1 to 6)
* @param return an unsigned char
*  value of hall sensor
* @pre configuration of port PB and PD
* @post new value of position
*/
Hall_Position mc_get_hall(void)
{
  return HALL_SENSOR_VALUE();
}

/**
 * @brief External interruption
 *                 Sensor (A) mode toggle
 * @pre configuration of external interruption (initialization)
 * @post New value in Hall variable
 */
#ifdef __GNUC__
  ISR(HALL_A())
#else
#pragma vector = HALL_A()
__interrupt void mc_hall_a(void)
#endif
{
  mc_switch_commutation(HALL_SENSOR_VALUE());

  //estimation speed on rising edge of Hall_A
  if (PIND&(1<<PORTD7))
  {
    mc_estimation_speed();
    g_mc_read_enable=FALSE; // Wait 1 period
  }
  else
  {
    g_mc_read_enable=TRUE;
  }

}

/**
 * @brief External interruption
 *                 Hall Sensor (B) mode toggle
 * @pre configuration of external interruption (initialization)
 * @post New value in Hall variable
 */
#ifdef __GNUC__
  ISR(HALL_B())
#else
#pragma vector = HALL_B()
__interrupt void mc_hall_b(void)
#endif
{
  mc_switch_commutation(HALL_SENSOR_VALUE());
}

 /**
 * @brief External interruption
 *                 Hall Sensor (C) mode toggle
 * @pre configuration of external interruption (initialization)
 * @post New value in Hall variable
 */
#ifdef __GNUC__
  ISR(HALL_C())
#else
#pragma vector = HALL_C()
__interrupt void mc_hall_c(void)
#endif
{
  mc_switch_commutation(HALL_SENSOR_VALUE());
}

/**
* @brief Set the duty cycle values in the PSC according to the value calculate by the regulation loop
*/
void mc_duty_cycle(U8 level)
{
   U8 duty;
   duty = level;

#if ((CURRENT_DECAY == SLOW_DECAY_SYNCHRONOUS)||(CURRENT_DECAY == FAST_DECAY_SYNCHRONOUS))
   U8 dutydt;   /* duty with dead time */
   if (duty >= DEADTIME) dutydt = duty - DEADTIME;
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

/**
* @brief Set the Switching Commutation value on outputs
*   according to sensor or estimation position
*
* @param position (1 to 6) and direction (FORWARD or BACKWARD)
*/
void mc_switch_commutation(Hall_Position position)
{
  // get the motor direction to commute the right switches.
  char direction = mci_get_motor_direction();

  // Switches are commuted only if the user start the motor
  if (mci_motor_is_running())
  {
    mc_duty_cycle(mc_get_duty_cycle());
    switch(position)
    {
    // cases according to rotor position
      case HS_001:  if (direction==CCW)  {Set_Q5Q2();}
                    else                      {Set_Q1Q6();}
                    break;

      case HS_101:  if (direction==CCW)  {Set_Q3Q2();}
                    else                      {Set_Q1Q4();}
                    break;

      case HS_100:  if (direction==CCW)  {Set_Q3Q6();}
                    else                      {Set_Q5Q4();}
                    break;

      case HS_110:  if (direction==CCW)  {Set_Q1Q6();}
                    else                      {Set_Q5Q2();}
                    break;

      case HS_010:  if (direction==CCW)  {Set_Q1Q4();}
                    else                      {Set_Q3Q2();}
                    break;

      case HS_011:  if (direction==CCW)  {Set_Q5Q4();}
                    else                      {Set_Q3Q6();}
                    break;
      default : break;
      }
  }
  else
  {
    Set_none(); // all switches are switched OFF
  }
}

/******************************************************************************/
/******************************************************************************/
/*    TIMER 1 :  generate the g_tick                                          */
/******************************************************************************/
/******************************************************************************/

/**
 * @brief timer 1 Configuration
 * Use to generate a 250us activation  for sampling speed regulation
 * @pre None
 * @post An interrupt all 256us
*/
void mc_init_timer1(void)
{
  TCCR1A = 0; //Normal port operation + Mode CTC
  TCCR1B = 1<<WGM12 | 1<<CS11 | 1<<CS10 ; // Mode CTC + prescaler 64
  TCCR1C = 0;
  OCR1AH = 0;
  OCR1AL = 63; // f ocra = 16MHz %64 %63
  TIMSK1=(1<<OCIE1A); // Output compare A Match interrupt Enable
}

/**
  * @brief Launch the regulation loop (see main.c) .
  * @pre configuration of timer 1 registers
  * @post g_tick use in main.c for regulation loop
*/
#ifdef __GNUC__
  ISR(TIMER1_COMPA_vect)
#else
#pragma vector = TIMER1_COMPA_vect
__interrupt void launch_sampling_period(void)
#endif
{
  g_tick = TRUE;
}

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
void mc_init_timer0(void)
{
  TCCR0A = 0;
  TCCR0B = (1<<CS02)|(0<<CS01)|(0<<CS00); // 256 prescaler (16us)
  TIMSK0 = (1<<TOIE0);
}

/**
  * @brief Timer0 Overflow for speed measurement
  * @pre configuration of timer 0
  * @post generate an overflow when the motor turns too slowly
*/
#ifdef __GNUC__
  ISR(TIMER0_OVF_vect)
#else
#pragma vector = TIMER0_OVF_vect
__interrupt void ovfl_timer0(void)
#endif
{
  TCNT0=0x00;
  ovf_timer++;
  // if they are no commutation after 125 ms
  // 125 ms = (61<<8) * 8us
  if(ovf_timer >= 100)
  {
    ovf_timer = 0;
    mc_set_measured_speed(0);
    //if the motor was turning and no stop order
    // was given, motor run automatically.
    if(mci_motor_is_running())mci_retry_run();
  }
}

/**
* @brief estimation speed
* @pre configuration of timer 0 \n
*           and define or not AVERAGE_SPEED_MEASURENT in config_motor.h
* @post new value for real speed
*/
void mc_estimation_speed(void)
{
  U16 timer_value;
  U32 new_measured_speed;

  if (g_mc_read_enable==TRUE)
  {
    // Two 8 bits variables are use to simulate a 16 bits timers
    timer_value = (ovf_timer<<8) + TCNT0;

    if (timer_value == 0) {timer_value += 1 ;} // warning DIV by 0
    new_measured_speed = K_SPEED / timer_value;
    if(new_measured_speed > 255) new_measured_speed = 255; // Variable saturation


    #ifdef AVERAGE_SPEED_MEASUREMENT
      // To avoid noise an average is realized on 8 samples
      average += new_measured_speed;
      if(count >= N_SAMPLE)
      {
        count = 1;
        mc_set_measured_speed(average >> 3);
        average = 0;
      }
      else count++;
    #else
      // else get the real speed
      mc_set_measured_speed(new_measured_speed);
    #endif

    // Reset Timer 0 register and variables
    TCNT0=0x00;
    ovf_timer = 0;
    g_mc_read_enable=FALSE;
  }
}

/******************************************************************************/
/******************************************************************************/
/*       ADC use for current and potentiometer measurement                    */
/******************************************************************************/
/******************************************************************************/

//! @brief Launch the sampling procedure to get current value
//! @pre amplifier and IT initialization
//! @post Set the End Of Conversion flag
#ifdef __GNUC__
  ISR(ADC_vect)
#else
#pragma vector = ADC_vect
__interrupt void ADC_end_of_conversion(void)
#endif
{
  Adc_select_channel(ADC_INPUT_GND); /* release the amplified channel */
  if(State == CONV_POT) mc_set_potentiometer_value(Adc_get_8_bits_result());
  if(State == CONV_CURRENT) mci_store_measured_current(Adc_get_10_bits_result());
  ADC_State = FREE;
}


//! @brief Launch the scheduler for the ADC
//! @post Get results for Potentiometer and current values.
void mc_ADC_Scheduler(void)
{
  switch(State)
  {
  case CONV_INIT :
    ADC_State = FREE;
    State = CONV_CURRENT;
    break;

  case CONV_CURRENT :              /* previous state was CONV_CURRENT */
    if(ADC_State == FREE)
    {
      ADC_State = BUSY;
      State= CONV_POT;                        /* new state is CONV_POT */
      Adc_left_adjust_result();
      Adc_start_conv_channel(ADC_INPUT_ISRC); /* get POT on ISRC input */
    }
    break;

  case CONV_POT :                           /* previous state was CONV_POT */
    if(ADC_State == FREE)
    {
      ADC_State = BUSY;
      State = CONV_CURRENT;                   /* new state is CONV_CURRENT */
      Adc_right_adjust_result();
      Adc_start_conv_channel(ADC_INPUT_AMP1); /* get current on amplifier 1 */
    }
    break;
  }
}

/******************************************************************************/
/******************************************************************************/
/*       Over Current Configuration                                           */
/******************************************************************************/
/******************************************************************************/


//! @brief the purpose of this function is to disable \n
//!   the overcurrent detection during startup (inrush current) \n
void mc_disable_during_inrush(void)
{
  inrush_delay = (U16) 500;
  inrush_mask_flag = TRUE;
  Disable_over_current();
}

//! @brief the purpose of this function is to manage the delay \n
//!   used when the overcurrent detection is disabled \n
void mc_inrush_task(void)
{ 
  if (inrush_mask_flag == TRUE)
  {
    if (inrush_delay-- == 0)
    {
      inrush_mask_flag = FALSE;
      Enable_over_current();
    }
  }
}

// Overcurrent detection
#ifdef __GNUC__
  ISR(PSC_FAULT_vect)
#else
#pragma vector = PSC_FAULT_vect
__interrupt void mc_overcurrent_detect(void)
#endif
{
  PIFR = (1<<PEV1); // clear the interrupt
  overcurrent = TRUE;
  mci_stop();
}
