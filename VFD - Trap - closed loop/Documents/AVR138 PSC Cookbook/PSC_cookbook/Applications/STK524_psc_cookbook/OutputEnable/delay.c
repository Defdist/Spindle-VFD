 /*C**************************************************************************
* $RCSfile: delay.c,v $
*----------------------------------------------------------------------------
* Copyright (c) 2003 Atmel.
*----------------------------------------------------------------------------
* RELEASE:      $Name: ballast-valid-si-1_0_0 $      
* REVISION:     $Revision: 1.1.1.1 $     
* FILE_CVSID:   $Id: delay.c,v 1.1.1.1 2004/04/06 15:25:43 raubree Exp $       
*----------------------------------------------------------------------------
* PURPOSE: 
* This file provides a program to generate a delay
*****************************************************************************/


/*_____ I N C L U D E S ____________________________________________________*/
//#include "lib_mcu/compiler.h"
//#include "lib_mcu/mcu.h"

  void delay(void)
   {
      unsigned long count;
      count=0x30000;
      while(count!=0) count--;
   }
