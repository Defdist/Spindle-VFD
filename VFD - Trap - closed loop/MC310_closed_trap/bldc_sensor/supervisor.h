#ifndef _SUPERVISOR_H_
	#define _SUPERVISOR_H_

	#define SLOWDOWN_PORT PORTC
	#define SLOWDOWN_DDR DDRC
	#define SLOWDOWN_PIN PINC
	#define SLOWDOWN_BIT 3
	#define SLOWDOWN_MASK (1<<SLOWDOWN_BIT)

	void setPC3_high(void);
	void setPC3_low(void);

#endif
