//!
//! @file $RCSfile: main.c,v $
//!
//! Copyright (c) 2006 Atmel.
//!
//! @brief Main module : It is based on an infinite loop
//!
//! @version $Revision: 1.6 $
//!

//_____  I N C L U D E S ___________________________________________________

#include <ioavr.h>
#include <stdio.h>

#include "config.h"
#include "mc_interface.h"
#include "inavr.h"

#include "lib_mcu/compiler.h"
#include "lib_mcu/pll/pll_drv.h"
#include "lib_mcu/adc/adc_drv.h"



//_____ M A C R O S ________________________________________________________


//_____ D E F I N I T I O N S ______________________________________________
void   init(void);
void   ADC_Init(void);
void   Start_ADC(void);
void   PSC_Init(unsigned int ot0,  unsigned int ot1);
void   store_new_amplitude(U16 new_val);

S16    read_acquisition(void);

//_____ D E C L A R A T I O N S ____________________________________________
volatile U8     Main_Tick = 0; // Periodic clock to generate

extern volatile U8   Flag_IT_ADC;
extern volatile Bool mci_run_stop;


int main(void)
{
  static S16 a;
 
  init();                       // Ports initiation, Timer 0 configuration and Comparators activation 
  ADC_Init();                   // ADC initiation and Potentiometer' value as input of ADC  
  PSC_Init(2, MAX_PWM);         // PSC initiation
 
  mci_run();
           
  while(1)
  {
    if (Main_Tick)              // In the timer0 interrupt, the parameter Main_Tick will be set,
    {                           // which makes the condition is true, so that the ADC conversion will be started
     Main_Tick=0;               // This tick here is used to define the time, how long the poti's value should be updated.               
     Start_ADC();
    }

    if (Flag_IT_ADC)
    {
     a = (read_acquisition());  // The parameter Flag_IT_ADC will be set the ADC interrupt. In this part
     if (a>0x210)               // the value of the poti will be read, according to which the running direction of the motor
     {                          // will be set and the value will be used to update the upcoming PWM.
       mci_backward(); 
       store_new_amplitude(a);  
       mci_run();
     }
     
     if (a<0x190) 
     {
       mci_forward();
       a= 0x400-a;
       store_new_amplitude(a);  
       mci_run();
      }       

      if ((a>=0x190) && (a<=0x210) )
      {
        mci_stop();
      }   

      Flag_IT_ADC=0;
     }   /* end of Flag_IT_ADC */
      
   }     /* end of while(1) */
  
}        /* end of main */


