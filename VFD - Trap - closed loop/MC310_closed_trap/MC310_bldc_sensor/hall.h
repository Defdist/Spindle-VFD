

#ifndef hall_h
	#define hall_h
	
	// Hall sensor interrupt vector configuration
    #define HALL_AC() (PCINT2_vect) //HallA & HallC share PCINT2
    #define HALL_B()  (PCINT1_vect)

	uint8_t hall_getPosition(void);

	

#endif
