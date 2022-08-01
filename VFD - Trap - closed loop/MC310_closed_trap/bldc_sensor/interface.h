#ifndef _INTERFACE_H_
	#define _INTERFACE_H_

	#define GOALRPM_LPF_SETTLED  1
	#define GOALRPM_LPF_CHANGING 2

	#define DIRECTION_PIN_CHANGE_vect (PCINT0_vect) //direction pin is on PCINT0

	void interface_init(void);
	void interface_handler(void);

	void interface_sendStatus_RPM(void);
#endif
