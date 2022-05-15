/*C**************************************************************************
* $RCSfile: test_int_PSC2.c,v $
*----------------------------------------------------------------------------
* Copyright (c) 2003 Atmel.
*----------------------------------------------------------------------------
* RELEASE:      $Name: ballast-valid-si-1_0_0 $      
* REVISION:     $Revision: 1.1 $     
* FILE_CVSID:   $Id: test_int_PSC2.c,v 1.1 2004/10/01 12:24:56 raubree Exp $       
*----------------------------------------------------------------------------
* PURPOSE: 
* This file provides a program to generate a PSC Waveform
*****************************************************************************/



/*_____ I N C L U D E S ____________________________________________________*/
#include "lib_mcu/compiler.h"
#include "lib_mcu/mcu.h"
#include "lib_mcu/pll.h"

#define DEAD_TIME_0 100
#define ON_TIME_0 2400
#define DEAD_TIME_1 200
#define ON_TIME_1 1300

  unsigned char Fault = 0;
  unsigned char Ent = 0;
  
  /* push SW1 to select Retrigger Interrupt */
  /* push SW2 to select End of Cycle Interrupt */
  
  /* PE is connected to switches */
  /* PD is connected to leds */
  
  /* careful : PE1 is clock input */
  /*           don't forget to remove XTAL1 jumper on STK500 */


/*F**************************************************************************
* NAME: PSC2 Interrupt
*****************************************************************************/
#pragma vector = (PSC2_CAPT_vect)
__interrupt void PSC2_Capture_IT(void)
{
//	PIFR1 = (1<<PEV1B);
	PIFR2 = 0x1F;
        Ent++;
	Ent = Ent & 0xF;
	PORTD = ~((Ent<<4)|Fault);

}

#pragma vector = (PSC2EC_vect)
__interrupt void PSC2_End_Cycle_IT(void)
{
	PIFR2 = 0x1F;
	Ent++;
        Ent = Ent & 0xF;
	PORTD = ~((Ent<<4)|Fault);
}

/*F**************************************************************************
* NAME: PSC2 Init
*****************************************************************************/
void PSC2_Init (void)
{
  PSOC2 = (1<<POEN2A)|(1<<POEN2B);
  OCR2SAH = HIGH(DEAD_TIME_0);
  OCR2SAL = LOW(DEAD_TIME_0);
  OCR2RAH = HIGH(ON_TIME_0);
  OCR2RAL = LOW(ON_TIME_0);
  OCR2SBH = HIGH(DEAD_TIME_1);
  OCR2SBL = LOW(DEAD_TIME_1);
  OCR2RBH = HIGH(ON_TIME_1);
  OCR2RBL = LOW(ON_TIME_1);
  PCNF2 = (1<<PMODE21)|(0<<PMODE20)|(1<<POP2); /* Four Ramp Mode */
  PFRC2A = (1<<PCAPE2A)|(0<<PISEL2A)|(1<<PELEV2A)|(1<<PRFM2A3);
  PFRC2B = 0;
  PCTL2 = (1<<PRUN2); /* RUN !! */
}

/*F**************************************************************************
* NAME: main
*****************************************************************************/
int main (void)
{
//  OSCCAL=110;
  start_PLL_64();
  wait_PLL();
  PSC2_Init();
//  PIM2 = (1<<PEVE2A);
  PIM2 = (0<<PEOPE2);
  Enable_interrupt();
//  DDRE = (1<<DDE2);

  PORTD = 0xFF;
  DDRD = 0xFB;
  while(1)
  {
    if (bit_is_clear(PINE,PINE1))
    {
      while (bit_is_clear(PINE,PINE1));
      PIM2 = (1<<PEVE2A); /* External Event */
    }
	
    if (bit_is_clear(PINE,PINE2))
    {
      while (bit_is_clear(PINE,PINE2));
      PIM2 = (1<<PEOPE2);  /* End of cycle */
    }

  }
} 




