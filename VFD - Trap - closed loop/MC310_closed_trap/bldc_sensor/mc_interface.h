#ifndef _MC_LIB_H_
	#define _MC_LIB_H_

	void mci_motor_run(void);
	void mci_motor_stop(void);
	uint8_t mci_motorState_get(void);

	void mc_motor_init(void);

	uint8_t mci_motorDirection_get(void);
	void mci_motorDirection_set(uint8_t direction);

	uint16_t mci_motor_measuredCurrent_get(void);
	void mci_motor_measuredCurrent_integrate(uint16_t current);

	#define RUNNING 1
	#define STOPPED 0

#endif
