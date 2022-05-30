

#ifndef hall_h
	#define hall_h
	
	// Hall sensor interrupt vector configuration
    #define HALL_AC() (PCINT2_vect) //HallA & HallC share PCINT2
    #define HALL_B()  (PCINT1_vect)

	uint8_t hall_getPosition(void);

	// Estimate speed
    void hall_init_rpm_timer0(void);
    void hall_calculateRPM(void);

    void hall_measuredRPM_set(uint16_t measured_speed);
	uint16_t hall_measuredRPM_get(void);

	uint8_t hall_goalRPM_get(void);
	void hall_goalRPM_set(uint8_t potentiometer);

	#define HALL_B_HIGH 1
	#define HALL_B_LOW  0

#endif
