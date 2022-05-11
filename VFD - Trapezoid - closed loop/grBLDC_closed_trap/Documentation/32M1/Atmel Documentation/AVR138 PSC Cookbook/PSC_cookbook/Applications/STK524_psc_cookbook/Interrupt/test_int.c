/*C**************************************************************************
* $RCSfile: test_int.c,v $
*----------------------------------------------------------------------------
* Copyright (c) 2003 Atmel.
*----------------------------------------------------------------------------
* RELEASE:      $Name: ballast-valid-si-1_0_0 $      
* REVISION:     $Revision: 1.2 $     
* FILE_CVSID:   $Id: test_int.c,v 1.2 2004/08/25 15:31:49 raubree Exp $       
*----------------------------------------------------------------------------
* PURPOSE: 
* This file provides a program to generate a PSC Waveform
*****************************************************************************/



/*_____ I N C L U D E S ____________________________________________________*/
#include "lib_mcu/compiler.h"
#include "lib_mcu/mcu.h"

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
  
/*F**************************************************************************
* NAME: PSC1 Interrupt
*****************************************************************************/

#pragma vector = (PSC1_CAPT_vect)
__interrupt void PSC1_Capture_IT(void)
{
//	PIFR1 = (1<<PEV1B);
	PIFR1 = 0x1F;
    Ent++;
	Ent = Ent & 0xF;
	PORTD = ~((Ent<<4)|Fault);

}

#pragma vector = (PSC1EC_vect)
__interrupt void PSC1_End_Cycle_IT(void)
{
	PIFR1 = 0x1F;
	Ent++;
    Ent = Ent & 0xF;
	PORTD = ~((Ent<<4)|Fault);
}



/*F**************************************************************************
* NAME: PSC1 Init
*****************************************************************************/
void PSC1_Init (void)
{
  PSOC1 = (1<<POEN1A)|(1<<POEN1B);
  OCR1SAH = HIGH(DEAD_TIME_0);
  OCR1SAL = LOW(DEAD_TIME_0);
  OCR1RAH = HIGH(ON_TIME_0);
  OCR1RAL = LOW(ON_TIME_0);
  OCR1SBH = HIGH(DEAD_TIME_1);
  OCR1SBL = LOW(DEAD_TIME_1);
  OCR1RBH = HIGH(ON_TIME_1);
  OCR1RBL = LOW(ON_TIME_1);
  PCNF1 = (1<<PMODE11)|(1<<POP1);
  PFRC1A = (1<<PCAPE1A)|(0<<PISEL1A)|(1<<PELEV1A)|(1<<PRFM1A3);
  PFRC1B = 0;
  PCTL1 = (1<<PRUN1); /* RUN !! */
}

/*F**************************************************************************
* NAME: main
*****************************************************************************/
int main (void)
{

  PSC1_Init();
  PIM1 = (1<<PEVE1A);
  Enable_interrupt();
  
  PORTD = 0xFF;
  DDRD = 0xFF;
  while(1)
  {
    if (bit_is_clear(PINE,PINE1))
	{

	  while (bit_is_clear(PINE,PINE1));
      PIM1 = (1<<PEVE1A);
    }
	
    if (bit_is_clear(PINE,PINE2))
	{

	  while (bit_is_clear(PINE,PINE2));
      PIM1 = (1<<PEOPE1);
	  
    }

  }
} 




