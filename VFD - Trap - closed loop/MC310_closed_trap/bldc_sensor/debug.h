#ifndef _DEBUG_H_
	#define _DEBUG_H_

	//Connects to Arduino Uno pin A4
	#define SLOWDOWN_PORT PORTC
	#define SLOWDOWN_DDR DDRC
	#define SLOWDOWN_PIN PINC
	#define SLOWDOWN_BIT 3
	#define SLOWDOWN_MASK (1<<SLOWDOWN_BIT)

	//Connects to Arduino Uno pin A2
	#define PD3_PORT PORTD
	#define PD3_DDR DDRD
	#define PD3_PIN PIND
	#define PD3_BIT 3
	#define PD3_MASK (1<<PD3_BIT)

	void unoPinA4_high(void);
	void unoPinA4_low(void);
	void unoPinA4_input(void);
	
	void unoPinA2_high(void);
	void unoPinA2_low(void);
	void unoPinA2_input(void);	
	

#endif
