#ifndef hall_h
	#define hall_h
	
	// Hall sensor interrupt vector configuration
    #define HALL_AC_vect (PCINT2_vect) //HallA & HallC share PCINT2
    #define HALL_B_vect  (PCINT1_vect) //HallB is on PCINT1
    
	uint8_t hall_getPosition(void);

	void hall_init(void);

	#define HALL_B_HIGH 1
	#define HALL_B_LOW  0

#endif
