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
	
	A4910pinPB4_reset_Init();
	A4910pinPB4_reset_Toggle();
	A4910pinPB4_reset_Set();
	A4910pinPB4_reset_Clear();

	A4910_Disable();
	A4910_Enable();

#endif
