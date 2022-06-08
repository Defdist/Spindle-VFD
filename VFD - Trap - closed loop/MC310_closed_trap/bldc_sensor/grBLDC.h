//main include file

#ifndef grBLDC_h
	#define grBLDC_h

	#ifdef __GNUC__ // Use AVR-GCC library
		#include <avr/io.h>
		#include <avr/power.h>
		#include <avr/pgmspace.h>
		#include <avr/interrupt.h>
	#elif __ICCAVR__ // Use IAR-AVR library
   		#include <ioavr.h>
	#else
   		#error Current COMPILER not supported
	#endif

	#include <stdio.h>
	#include <stdint.h>
	#include <stdbool.h>

	#include "a4910.h"
	#include "adc.h"
	#include "dac.h"
	#include "psc.h"
	#include "motor.h"
	#include "Drivers\dac\dac_drv.h"
	#include "Drivers\psc\psc_drv.h"
	#include "Drivers\pll\pll_drv.h"
	#include "Drivers\comparator\comparator_drv.h"
	#include "Drivers\adc\adc_drv.h"
	#include "hall.h"
	#include "pid.h"
	#include "debug.h"
	#include "timing.h"
	#include "comparator.h"
	#include "interface.h"

	#define TRUE 1
	#define FALSE 0

    #define lowByte(data_w)  ((uint8_t)data_w)
    #define highByte(data_w) ((uint8_t)(data_w>>8))

	#define FOSC_HZ 16000000 //Hz
#endif
