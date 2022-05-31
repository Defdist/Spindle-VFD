#ifndef _TIMING_H_
	#define _TIMING_H_

	uint8_t timing_runControlLoop_get(void);
	void    timing_runControlLoop_set(uint8_t state);

	void timing_timer0_init(void);
	void timing_timer1_init(void);

	void timing_calculateRPM(void);

	void     timing_measuredRPM_set(uint16_t measured_speed);
	uint16_t timing_measuredRPM_get(void);

#endif
