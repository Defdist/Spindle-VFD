#ifndef _MC_DRV_H_
    #define _MC_DRV_H_

    #define Clear_Port_Q2() 
    #define Set_Port_Q2()   (PORTB |=   (1<<PORTB1))
    #define Set_Port_Q4()   (PORTB |=   (1<<PORTB6))
    #define Set_Port_Q6()   (PORTB |=   (1<<PORTB7))

  void turnOffAllFETs(void);

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

    #elif (CURRENT_DECAY == FAST_DECAY_SYNCHRONOUS)
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
                (0<<POEN2A)|(0<<POEN2B);

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

    // ADC scheduler definitions
    #define ADC_UNITIALIZED           0
    #define ADC_MEASURE_REQUESTED_RPM 1
    #define ADC_MEASURE_CURRENT       2

    #define FREE  0
    #define BUSY  1

    // Hardware initialization
    void mc_motor_init_HW(void);
    void PSC_Init (void);

    // Phases commutation functions
    void psc_setDutyCycle(uint8_t level);
    void mc_commutateFETs(uint8_t position);

    // Sampling time configuration
    void mc_motor_init_timer1(void);

    // ADC use for current measure and potentiometer...
    void mc_ADC_Scheduler(void);
    uint8_t mc_Get_Current(void);
    uint8_t mc_Get_Potentiometer(void);

    // Over Current Detection
    //void mc_disableOvercurrentDuringStartup(void); //JTS2doLater
    void mc_inrush_task(void); /* manage the inrush current */

#endif
