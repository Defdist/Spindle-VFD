/*H**************************************************************************
* NAME:         uart_bdr.h
*----------------------------------------------------------------------------
* Copyright (c) 2006 Atmel.
*----------------------------------------------------------------------------
* RELEASE:      demo-bldc-sensor-at90pwm3-4_6_0
* REVISION:     1.5.2.3
*----------------------------------------------------------------------------
* PURPOSE:
* Provide Baudrate configuration for MCU
*****************************************************************************/
#ifndef _UART_BDR_H
#define _UART_BDR_H

#ifndef AVRGCC
   #define Uart_set_baudrate(bdr)  ( UBRRH = (Uchar)((((Uint32)FOSC*1000L)/((Uint32)bdr*16)-1)>>8),\
                                  UBRRL = (Uchar)(((Uint32)FOSC*1000 )/((Uint32)bdr*16)-1)    )
#else
  #define Uart_set_baudrate(bdr)  ( UBRR = (U16)(((U32)FOSC*1000L)/((U32)bdr*16)-1))
#endif

#define Uart_double_bdr()          (UCSRA |= (1<<U2X1))

#endif/* _UART_BDR_H */

