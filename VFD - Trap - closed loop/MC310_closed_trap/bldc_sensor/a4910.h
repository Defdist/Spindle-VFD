//!
//! @file ascii.h,v
//!
//! Copyright (c) 2006 Atmel.
//!
//! @brief This file provides ASCII functions for the µshell task.
//!
//! @version 1.1
//!

#ifndef a4910_h
	#define a4910_h
	
	#define BLDC_ENABLE_PORT PORTB
	#define BLDC_ENABLE_DDR DDRB
	#define BLDC_ENABLE_PIN PINB
	#define BLDC_ENABLE_BIT 4 //PB4
	#define BLDC_ENABLE_MASK (1<<BLDC_ENABLE_BIT)
	
	void A4910pinPB4_reset_Init(void);
	void A4910pinPB4_reset_Toggle(void);
	void A4910pinPB4_reset_Set(void);
	void A4910pinPB4_reset_Clear(void);

	void A4910_Disable(void);
	void A4910_Enable(void);

#endif
