#ifndef hall_h
	#define hall_h
	
	// Hall sensor interrupt vector configuration
    #define HALL_AC_vect (PCINT2_vect) //HallA & HallC share PCINT2
    #define HALL_B_vect  (PCINT1_vect) //HallB is on PCINT1

	//#define AVERAGE_SPEED_MEASUREMENT //enable averaging
	#define NUM_SAMPLES_PER_RPM_CALCULATION 8 //Number of samples to calculate motor speed (if enabled)
    
	uint8_t hall_getPosition(void);

	void hall_init(void);

	uint8_t adc_goalRPM_get(void);
	void    adc_goalRPM_set(uint8_t potentiometer);

	#define HALL_B_HIGH 1
	#define HALL_B_LOW  0

#endif
