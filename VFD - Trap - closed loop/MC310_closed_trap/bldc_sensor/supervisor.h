#ifndef _SUPERVISOR_H_
	#define _SUPERVISOR_H_

	#define SLOWDOWN_PORT PORTC
	#define SLOWDOWN_DDR DDRC
	#define SLOWDOWN_PIN PINC
	#define SLOWDOWN_BIT 3
	#define SLOWDOWN_MASK (1<<SLOWDOWN_BIT)

	#define PD3_PORT PORTD
	#define PD3_DDR DDRD
	#define PD3_PIN PIND
	#define PD3_BIT 3
	#define PD3_MASK (1<<PD3_BIT)

	void setPC3_high(void);
	void setPC3_low(void);
	
	void setPD3_high(void);
	void setPD3_low(void);

#endif
