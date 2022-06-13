#ifndef _TIMING_H_
	#define _TIMING_H_

	//#define AVERAGE_RPM_MEASUREMENT //enable averaging
	//#define NUM_SAMPLES_PER_RPM_CALCULATION 8 //Number of samples to calculate motor speed (if enabled)
	//#define POWER_OF__NUM_SAMPLES_PER_RPM_CALCULATION 3 //2 ^ n = NUM_SAMPLES_PER_RPM_CALCULATION 

	#define TIMER0_TICK_PERIOD_us 4 //this changes if TCCR0B prescaler value changes! //(CPU/64DIV): 4 microseconds
	#define TIMER0_COUNTS_TO      7
	#define TIMER0_INTERRUPT_PERIOD_us (TIMER0_TICK_PERIOD_us*(TIMER0_COUNTS_TO+1))
	#define CONTROL_LOOP_PERIOD_us TIMER0_INTERRUPT_PERIOD_us

	#define TIMER1_TICK_PERIOD_us 4 //this changes if TCCR1B prescaler value changes! //(CPU/64DIV): 4 microseconds

	uint8_t timing_runControlLoop_get(void);
	void    timing_runControlLoop_set(uint8_t state);

	void timing_timer0_init(void);
	void timing_timer1_init(void);

	void timing_calculateRPM(void);

	void     timing_measuredRPM_set(uint16_t measured_speed);
	uint16_t timing_measuredRPM_get(void);

#endif
