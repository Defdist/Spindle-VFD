#ifndef _MC_LIB_H_
	#define _MC_LIB_H_

	void mci_motor_run(void);
	void mci_motor_stop(void);
	uint8_t mci_motorState_get(void);

	void mc_motor_init(void);

	void mci_motor_desiredSpeed_set(uint8_t speed);
	uint8_t mci_motor_desiredSpeed_get(void);

	uint8_t mci_motorDirection_get(void);

	void mci_motor_measuredSpeed_set(uint8_t measured_speed);
	uint8_t mci_motor_measuredSpeed_get(void);

	uint16_t mci_motor_measuredCurrent_get(void);
	void mci_motor_measuredCurrent_integrate(uint16_t current);

	uint8_t mc_potentiometerValue_get(void);
	void mc_potentiometerValue_set(uint8_t potentiometer);

	#define RUNNING 1
	#define STOPPED 0

#endif
