//******************************************************************************
//!
//! @file $Id: mc_drv.h 1137 2008-04-17 16:35:06Z raubree $
//!
//! Copyright (c) 2007 Atmel.
//!
//! @brief Low Level Functions
//!
//!
//! @todo
//! @bug
//******************************************************************************


#ifndef _MC_DRV_H_
#define _MC_DRV_H_


  #define Disable_over_current() \
   Psc_config_input_1(PSC_OVERLAP_ENABLE,\
                      PSC_USE_COMPARATOR,\
                      PSC_USE_HIGH_LEVEL,\
                      PSC_INPUT_FILTER_ENABLE,\
                      PSC_SYNCHRONOUS_OUTPUT_CONTROL,\
                      PSC_INPUT_NO_ACTION);

  #define Enable_over_current() \
   Psc_config_input_1(PSC_OVERLAP_ENABLE,\
                      PSC_USE_COMPARATOR,\
                      PSC_USE_HIGH_LEVEL,\
                      PSC_INPUT_FILTER_ENABLE,\
                      PSC_SYNCHRONOUS_OUTPUT_CONTROL,\
                      PSC_INPUT_HALT);



  // Comparator interruption
#ifdef __GNUC__
  #define HALL_A() (ANACOMP0_vect)
#else
  #define HALL_A() (ANA_COMP0_vect)
#endif
  #define HALL_B() (PCINT1_vect)
#ifdef __GNUC__
  #define HALL_C() (ANACOMP2_vect)
#else
  #define HALL_C() (ANA_COMP2_vect)
#endif


  #define HALL_SENSOR_VALUE()        \
    (Hall_Position)(\
    ( (PIND & (1<<PIND7)) >> PIND7 ) \
  | ( (PINC & (1<<PINC6)) >> 5 )     \
  | ( (PIND & (1<<PIND5)) >> 3 ))

  #define Clear_Port_Q5() (PORTB &= ( ~(1<<PORTB0)))
  #define Clear_Port_Q3() (PORTC &= ( ~(1<<PORTC0)))
  #define Clear_Port_Q1() (PORTD &= ( ~(1<<PORTD0)))
  #define Clear_Port_Q6() (PORTB &= ( ~(1<<PORTB1)))
  #define Clear_Port_Q4() (PORTB &= ( ~(1<<PORTB6)))
  #define Clear_Port_Q2() (PORTB &= ( ~(1<<PORTB7)))
  #define Set_Port_Q2()   (PORTB |=   (1<<PORTB1))
  #define Set_Port_Q4()   (PORTB |=   (1<<PORTB6))
  #define Set_Port_Q6()   (PORTB |=   (1<<PORTB7))

  // Six step commutation
  #define Set_none()                \
    POC = (0<<POEN0A)|(0<<POEN0B)|\
          (0<<POEN1A)|(0<<POEN1B)|\
          (0<<POEN2A)|(0<<POEN2B);\
    Clear_Port_Q2();                \
    Clear_Port_Q4();                \
    Clear_Port_Q6();                \
    Clear_Port_Q1();                \
    Clear_Port_Q3();                \
    Clear_Port_Q5();

#if (CURRENT_DECAY == SLOW_DECAY_SYNCHRONOUS)
  #define Set_Q5Q4()                \
    PORTB &= ( ~((1<<PORTB1)|(1<<PORTB7)));\
    POC = (0<<POEN0A)|(0<<POEN0B)|\
          (0<<POEN1A)|(0<<POEN1B)|\
          (1<<POEN2A)|(1<<POEN2B);\
    PORTB |=   (1<<PORTB6);

  #define Set_Q5Q2()                \
    PORTB &= ( ~((1<<PORTB1)|(1<<PORTB6)));\
    POC = (0<<POEN0A)|(0<<POEN0B)|\
          (0<<POEN1A)|(0<<POEN1B)|\
          (1<<POEN2A)|(1<<POEN2B);\
    PORTB |=   (1<<PORTB7);

  #define Set_Q3Q6()                \
    PORTB &= ( ~((1<<PORTB6)|(1<<PORTB7)));\
    POC = (0<<POEN0A)|(0<<POEN0B)|\
          (1<<POEN1A)|(1<<POEN1B)|\
          (0<<POEN2A)|(0<<POEN2B);\
    PORTB |=   (1<<PORTB1);

  #define Set_Q3Q2()                \
    PORTB &= ( ~((1<<PORTB1)|(1<<PORTB6)));\
    POC = (0<<POEN0A)|(0<<POEN0B)|\
          (1<<POEN1A)|(1<<POEN1B)|\
          (0<<POEN2A)|(0<<POEN2B);\
    PORTB |=   (1<<PORTB7);

  #define Set_Q1Q6()                \
    PORTB &= ( ~((1<<PORTB6)|(1<<PORTB7)));\
    POC = (1<<POEN0A)|(1<<POEN0B)|\
          (0<<POEN1A)|(0<<POEN1B)|\
          (0<<POEN2A)|(0<<POEN2B);\
    PORTB |=   (1<<PORTB1);

  #define Set_Q1Q4()                \
    PORTB &= ( ~((1<<PORTB1)|(1<<PORTB7)));\
    POC = (1<<POEN0A)|(1<<POEN0B)|\
          (0<<POEN1A)|(0<<POEN1B)|\
          (0<<POEN2A)|(0<<POEN2B);\
    PORTB |=   (1<<PORTB6);
  // *** end SLOW_DECAY_SYNCHRONOUS
#else

#if (CURRENT_DECAY == FAST_DECAY_SYNCHRONOUS)
  #define Set_Q5Q4()                \
    POC=0;\
    PCTL =  (PCTL&~((1<<PSWAP2)|(1<<PSWAP1)|(1<<PSWAP0)))\
                 | ((0<<PSWAP2)|(1<<PSWAP1)|(0<<PSWAP0));\
    POC = (0<<POEN0A)|(0<<POEN0B)|\
          (1<<POEN1A)|(1<<POEN1B)|\
          (1<<POEN2A)|(1<<POEN2B);

  #define Set_Q5Q2()                \
    POC=0;\
    PCTL =  (PCTL&~((1<<PSWAP2)|(1<<PSWAP1)|(1<<PSWAP0)))\
                 | ((0<<PSWAP2)|(0<<PSWAP1)|(1<<PSWAP0));\
    POC = (1<<POEN0A)|(1<<POEN0B)|\
          (0<<POEN1A)|(0<<POEN1B)|\
          (1<<POEN2A)|(1<<POEN2B);

  #define Set_Q3Q6()                \
    POC=0;\
    PCTL =  (PCTL&~((1<<PSWAP2)|(1<<PSWAP1)|(1<<PSWAP0)))\
                 | ((1<<PSWAP2)|(0<<PSWAP1)|(0<<PSWAP0));\
    POC = (0<<POEN0A)|(0<<POEN0B)|\
          (1<<POEN1A)|(1<<POEN1B)|\
          (1<<POEN2A)|(1<<POEN2B);

  #define Set_Q3Q2()                \
    POC=0;\
    PCTL =  (PCTL&~((1<<PSWAP2)|(1<<PSWAP1)|(1<<PSWAP0)))\
                 | ((0<<PSWAP2)|(0<<PSWAP1)|(1<<PSWAP0));\
    POC = (1<<POEN0A)|(1<<POEN0B)|\
          (1<<POEN1A)|(1<<POEN1B)|\
          (0<<POEN2A)|(0<<POEN2B);

  #define Set_Q1Q6()                \
    POC=0;\
    PCTL =  (PCTL&~((1<<PSWAP2)|(1<<PSWAP1)|(1<<PSWAP0)))\
                 | ((1<<PSWAP2)|(0<<PSWAP1)|(0<<PSWAP0));\
    POC = (1<<POEN0A)|(1<<POEN0B)|\
          (0<<POEN1A)|(0<<POEN1B)|\
          (1<<POEN2A)|(1<<POEN2B);

  #define Set_Q1Q4()                \
    POC=0;\
    PCTL =  (PCTL&~((1<<PSWAP2)|(1<<PSWAP1)|(1<<PSWAP0)))\
                 | ((0<<PSWAP2)|(1<<PSWAP1)|(0<<PSWAP0));\
    POC = (1<<POEN0A)|(1<<POEN0B)|\
          (1<<POEN1A)|(1<<POEN1B)|\
          (0<<POEN2A)|(0<<POEN2B);\
  // *** end FAST_DECAY_SYNCHRONOUS

#else 

  // *** then SLOW_DECAY or FAST_DECAY
  #define Set_Q5Q4()                \
    POC = (0<<POEN0A)|(0<<POEN0B)|\
          (0<<POEN1A)|(1<<POEN1B)|\
          (1<<POEN2A)|(0<<POEN2B);

  #define Set_Q5Q2()                \
    POC = (0<<POEN0A)|(1<<POEN0B)|\
          (0<<POEN1A)|(0<<POEN1B)|\
          (1<<POEN2A)|(0<<POEN2B);

  #define Set_Q3Q6()                \
    POC = (0<<POEN0A)|(0<<POEN0B)|\
          (1<<POEN1A)|(0<<POEN1B)|\
          (0<<POEN2A)|(1<<POEN2B);

  #define Set_Q3Q2()                \
    POC = (0<<POEN0A)|(1<<POEN0B)|\
          (1<<POEN1A)|(0<<POEN1B)|\
          (0<<POEN2A)|(0<<POEN2B);

  #define Set_Q1Q6()                \
    POC = (1<<POEN0A)|(0<<POEN0B)|\
          (0<<POEN1A)|(0<<POEN1B)|\
          (0<<POEN2A)|(1<<POEN2B);

  #define Set_Q1Q4()                \
    POC = (1<<POEN0A)|(0<<POEN0B)|\
          (0<<POEN1A)|(1<<POEN1B)|\
          (0<<POEN2A)|(0<<POEN2B);
#endif
#endif

  // ADC scheduler definitions
  #define CONV_INIT     0
  #define CONV_POT      1
  #define CONV_CURRENT  2

  #define FREE  0
  #define BUSY  1
  /**************************/
  /* prototypes declaration */
  /**************************/

  // Hardware initialization
  void mc_init_HW(void);
  void PSC_Init (void);

  // Phases commutation functions
  Hall_Position mc_get_hall(void);
  void mc_duty_cycle(U8 level);
  void mc_switch_commutation(Hall_Position position);

  // Sampling time configuration
  void mc_init_timer1(void);

  // Estimation speed
  void mc_init_timer0(void);
  void mc_estimation_speed(void);

  // ADC use for current measure and potentiometer...
  void mc_ADC_Scheduler(void);
  U8 mc_Get_Current(void);
  U8 mc_Get_Potentiometer(void);

  // Over Current Detection
  void mc_disable_during_inrush(void);
  void mc_inrush_task(void); /* manage the inrush current */

#endif
