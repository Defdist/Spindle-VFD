#ifndef _MOSFET_H_
	#define _MOSFET_H_

    void mosfet_init(void);

    void mosfet_commutate(uint8_t position);

    void mosfet_turnOffAll(void);

    //////////////////////////////////////////////////////////////////////

    //Select which two FETs are connected to the PSC output timers (the other four phases are disconnected (trapezoidal)
    //PORTD0: FET Q1
    //PORTB7: FET Q2
    //PORTC0: FET Q3
    //PORTB6: FET Q4
    //PORTB0: FET Q5
    //PORTB1: FET Q6

    #if (CURRENT_DECAY == SLOW_DECAY_SYNCHRONOUS)
        #define Set_Q5Q4()                \
          PORTB &= ( ~((1<<PORTB1)|(1<<PORTB7)));\ //Q6 & Q2 turned off
          POC = (0<<POEN0A)|(0<<POEN0B)|\ //PhaseU highFET/lowFET //0:pins disconnected from PSC //1:connected to PSC outputs
                (0<<POEN1A)|(0<<POEN1B)|\ //PhaseV
                (1<<POEN2A)|(1<<POEN2B);\ //PhaseW
          PORTB |=   (1<<PORTB6); //Q4 turned on

        #define Set_Q5Q2()                \
          PORTB &= ( ~((1<<PORTB1)|(1<<PORTB6)));\ //Q6 & Q4 turned off
          POC = (0<<POEN0A)|(0<<POEN0B)|\
                (0<<POEN1A)|(0<<POEN1B)|\
                (1<<POEN2A)|(1<<POEN2B);\ //Both PhaseW FETs connected to PSC 
          PORTB |=   (1<<PORTB7); //Q2 turned on

        #define Set_Q3Q6()                \
          PORTB &= ( ~((1<<PORTB6)|(1<<PORTB7)));\ //Q4 & Q2 turned off
          POC = (0<<POEN0A)|(0<<POEN0B)|\
                (1<<POEN1A)|(1<<POEN1B)|\
                (0<<POEN2A)|(0<<POEN2B);\
          PORTB |=   (1<<PORTB1); //Q6 turned on

        #define Set_Q3Q2()                \
          PORTB &= ( ~((1<<PORTB1)|(1<<PORTB6)));\ //Q6 & Q4 turned off
          POC = (0<<POEN0A)|(0<<POEN0B)|\
                (1<<POEN1A)|(1<<POEN1B)|\
                (0<<POEN2A)|(0<<POEN2B);\
          PORTB |=   (1<<PORTB7); //Q2 turned on

        #define Set_Q1Q6()                \
          PORTB &= ( ~((1<<PORTB6)|(1<<PORTB7)));\ //Q4 & Q2 turned off
          POC = (1<<POEN0A)|(1<<POEN0B)|\
                (0<<POEN1A)|(0<<POEN1B)|\
                (0<<POEN2A)|(0<<POEN2B);\
          PORTB |=   (1<<PORTB1);//Q6 turned on

        #define Set_Q1Q4()                \
          PORTB &= ( ~((1<<PORTB1)|(1<<PORTB7)));\ //Q6 & Q2 turned off
          POC = (1<<POEN0A)|(1<<POEN0B)|\
                (0<<POEN1A)|(0<<POEN1B)|\
                (0<<POEN2A)|(0<<POEN2B);\
          PORTB |=   (1<<PORTB6);//Q4 turned on

      #else //SLOW_DECAY or FAST_DECAY
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
