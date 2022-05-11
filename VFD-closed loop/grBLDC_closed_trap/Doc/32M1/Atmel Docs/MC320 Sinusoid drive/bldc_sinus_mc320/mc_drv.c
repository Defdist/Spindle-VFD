//!
//! @file $RCSfile: mc_drv.c,v $
//!
//! Copyright (c) 2006 Atmel.
//!
//! @brief Hardware Level of the Motor Control
//!
//! @version $Revision: 1.5 $
//!

//_____  I N C L U D E S ___________________________________________________

#include <ioavr.h>
#include "inavr.h"
#include <stdio.h>

#include "config.h"
#include "table_sin81.h"

#include "lib_mcu/pll/pll_drv.h"
#include "lib_mcu/compiler.h"


//_____ M A C R O S ________________________________________________________


/* definition of Hall sectors MC100 */
/* be careful this definition is one sector in advance */
/*                Hall_C      Hall_B        Hall_A     */
#define HAS1     (1<<PIND5) | (0<<PINC6) | (1<<PIND7)
#define HAS2     (0<<PIND5) | (0<<PINC6) | (1<<PIND7)
#define HAS3     (0<<PIND5) | (1<<PINC6) | (1<<PIND7)
#define HAS4     (0<<PIND5) | (1<<PINC6) | (0<<PIND7)
#define HAS5     (1<<PIND5) | (1<<PINC6) | (0<<PIND7)
#define HAS6     (1<<PIND5) | (0<<PINC6) | (0<<PIND7)

//_____ D E F I N I T I O N S ______________________________________________

void   init(void);
void   PSC_Init(unsigned int ot0,  unsigned int ot1);
void   PSC_Load (unsigned int dt0a,  unsigned int dt1a,
                 unsigned int dt0b,  unsigned int dt1b,
                 unsigned int dt0c,  unsigned int dt1c);
void   SVPWM(U16 amp, U8 Counter_Value, U8 Top, U8 Sector);
void   PSC_Start(void);
void   PSC_Stop(void);
void   Do_Sensor_Interrupt(void);
void   Start_ADC(void);

S16    read_acquisition() ;
U16    mc_control_speed_16b(U16 speed_ref , U16 speed_measure);

//_____ D E C L A R A T I O N S ____________________________________________
volatile U8   Hall_Sector = HAS1 ;     //!< current Hall sector
volatile U8   Mem_Hall_Sector = HAS1 ; //!< future Hall sector
volatile U8   Sensor_Counter_Up = 0;   //!< measure of the time
volatile U8   Sensor_Counter_Down = 1; //!< current counter for svpwm
volatile U8   Top_Counter = 1;         //!< current top counter
volatile U8   Mem_Top_Counter = 1;     //!< memorization at top
volatile U8   Delay_For_Change = 1;    //!< delay
volatile U8   Prescaler_Main_Tick;     //!< prescaler for Tick

volatile U16  Mem_Top_CounterX8 = 1;   //!< for filter
volatile U16  Amplitude = 0;           //!< voltage to apply
volatile U16  PWM0, PWM1, PWM2;        //!< duty cycle

extern volatile Bool mci_run_stop;     //!< command for motor
extern volatile U8   Main_Tick;        //!< Tick signal for main
extern Bool mci_direction;

    
/*************************************************************************************/
/*     PSC initiation                                                                */
/*     - centered aligned mode,                                                      */
/*     - fast clock input (the PWM clock (64 MHz) comes from the PLL)                */
/*************************************************************************************/

void PSC_Init(unsigned int ot0,  unsigned int ot1)
{
   Start_pll_64_mega();   // start the PLL at 64 MHz
   Wait_pll_ready();

   POCR0RAH = HIGH(ot0);
   POCR0RAL = LOW(ot0);

   POCR_RBH = HIGH(ot1);
   POCR_RBL = LOW(ot1);
   
   PCNF = (1<<PMODE) | (1<<POPA)|(1<<POPB) ;  /* fast clock input used */
  
   POCR1RAH = HIGH(ot0);
   POCR1RAL = LOW(ot0);
  
   POCR2RAH = HIGH(ot0); 
   POCR2RAL = LOW(ot0);
 
   // connect the PSC waveform generator outputs to the port outputs
   POC = (1<<POEN0B) | (1<<POEN0A) |(1<<POEN1B) | (1<<POEN1A) | (1<<POEN2B) | (1<<POEN2A) ;

}

/*************************************************************/
/*     PSC is loaded with new PWMs                           */
/*************************************************************/

inline void PSC_Load (unsigned int dt0a,  unsigned int dt1a,
               unsigned int dt0b,  unsigned int dt1b,
               unsigned int dt0c,  unsigned int dt1c)
{
   PCNF = (1<<PULOCK)|(1<<PMODE) | (1<<POPA) | (1<<POPB);
  
   POCR0SAH = HIGH(dt0a);
   POCR0SAL = LOW(dt0a);
   POCR0SBH = HIGH(dt1a);
   POCR0SBL = LOW(dt1a);
    
   POCR1SAH = HIGH(dt0b);
   POCR1SAL = LOW(dt0b);
   POCR1SBH = HIGH(dt1b);
   POCR1SBL = LOW(dt1b);

   POCR2SAH = HIGH(dt0c);
   POCR2SAL = LOW(dt0c);
   POCR2SBH = HIGH(dt1c);
   POCR2SBL = LOW(dt1c);

   PCNF = (0<<PULOCK)|(1<<PMODE) | (1<<POPA) | (1<<POPB);
  
}

/********************************************/
/*     PSC starts                           */
/********************************************/

void PSC_Start(void)
{
  PCTL = (1<<PRUN) | (1<<PCCYC)| (1<<PCLKSEL); 
}


/********************************************/
/*     PSC stops                            */
/********************************************/

void PSC_Stop(void)
{
  PCTL =  (1<<PCCYC)| (1<<PCLKSEL); 
}

/***********************************************************/
/*     TIMER 0 Compare Interrupt                           */
/*         - drive the Counter_up and Counter_down         */
/*         - calculate the new duty cycles                 */ 
/*         - generate the Main_Tick                        */
/***********************************************************/

#pragma vector = TIMER0_COMPA_vect
__interrupt void Timer0_IT(void)

{
  U8     theta1, theta2 ;  
  U16    tau1, tau2 ;
  U16    Thetai_1;
  Set_PC7();

  if (Delay_For_Change != 0)
  {
      Delay_For_Change --;
      
      if (Delay_For_Change == 0)
      {
         Top_Counter = Mem_Top_Counter;
         
         if (Top_Counter == 0) 
         {
             Top_Counter++; /* to avoid "divide by 0" */
         }
         
         Sensor_Counter_Down = Mem_Top_Counter;
         Hall_Sector = Mem_Hall_Sector;
         /* end Change_Sector */
      }
   }

   /* increment Sensor_Counter_Up */
   if ( Sensor_Counter_Up < 255 )
   {
      Sensor_Counter_Up += 1;
   }

   /* decrement Sensor_Counter_Down */
   if (Sensor_Counter_Down != 0) 
   {
     Sensor_Counter_Down -= 1;
   } 

   // -------------- space vector PWM algorithm -----------------
   Thetai_1 = ((U16)(Top_Counter - Sensor_Counter_Down) * MAX_THETA) / Top_Counter;

   Enable_interrupt();

   theta2 = (unsigned char) Thetai_1 ;                                               // calculation of the shift in the sinus table, theta1 and theta2
                                                                                                                                                                                                                                                                         
   theta1 = (unsigned char) (MAX_THETA - theta2) ;

   /* 128 is the max value of the normalized sin table */
   tau1 = ((U32)Amplitude * tab_sin[theta1]) / 128 ;                                 // according to theta1, theta2 and the value, read from the Poti
   tau2 = ((U32)Amplitude * tab_sin[theta2]) / 128 ;                                 // tau1 and tau2 can be figured out, used to calculate PWMs

   if (mci_direction == CW)
   {
      switch (Hall_Sector)                                                            // according to the signals of the Hall sensors,
      {                                                                               // the PWMs on the U, V, W can be calculated, 
       case HAS5 :                                                                    // in order to make the comutation happen on time.
         PWM0 = (unsigned short int) (MAX_PWM/2 - tau1 - tau2) ;
         PWM1 = (unsigned short int) (MAX_PWM/2 + tau1 - tau2) ;
         PWM2 = (unsigned short int) (MAX_PWM/2 + tau1 + tau2) ; break ;
         
       case HAS4 :
         PWM0 = (unsigned short int) (MAX_PWM/2 - tau1 + tau2) ;
         PWM1 = (unsigned short int) (MAX_PWM/2 - tau1 - tau2) ;
         PWM2 = (unsigned short int) (MAX_PWM/2 + tau1 + tau2) ; break ;
         
       case HAS3 :
         PWM0 = (unsigned short int) (MAX_PWM/2 + tau1 + tau2) ;
         PWM1 = (unsigned short int) (MAX_PWM/2 - tau1 - tau2) ;
         PWM2 = (unsigned short int) (MAX_PWM/2 + tau1 - tau2) ; break ;
         
      case HAS2 :
         PWM0 = (unsigned short int) (MAX_PWM/2 + tau1 + tau2) ;
         PWM1 = (unsigned short int) (MAX_PWM/2 - tau1 + tau2) ;
         PWM2 = (unsigned short int) (MAX_PWM/2 - tau1 - tau2) ; break ;
         
      case HAS1 :
         PWM0 = (unsigned short int) (MAX_PWM/2 + tau1 - tau2) ;
         PWM1 = (unsigned short int) (MAX_PWM/2 + tau1 + tau2) ;
         PWM2 = (unsigned short int) (MAX_PWM/2 - tau1 - tau2) ; break ;
         
      case HAS6 :
         PWM0 = (unsigned short int) (MAX_PWM/2 - tau1 - tau2) ;
         PWM1 = (unsigned short int) (MAX_PWM/2 + tau1 + tau2) ;
         PWM2 = (unsigned short int) (MAX_PWM/2 - tau1 + tau2) ; break ;
         
      default :
         PWM0 = (unsigned short int) (MAX_PWM/2) ;
         PWM1 = (unsigned short int) (MAX_PWM/2) ;
         PWM2 = (unsigned short int) (MAX_PWM/2) ; break ;
      }
          
      PSC_Load (PWM0, PWM0+DEAD_TIME, PWM2, PWM2+DEAD_TIME, PWM1, PWM1+DEAD_TIME);            // for the motor running direction CW
   }                                                                                          // PWMs are loaded to U, V, W
   
   else
   {
      switch (Hall_Sector)
      {
      case HAS1 :
         PWM0 = (unsigned short int) (MAX_PWM/2 - tau1 - tau2) ;
         PWM1 = (unsigned short int) (MAX_PWM/2 + tau1 - tau2) ;
         PWM2 = (unsigned short int) (MAX_PWM/2 + tau1 + tau2) ; break ;
         
      case HAS2 :
         PWM0 = (unsigned short int) (MAX_PWM/2 - tau1 + tau2) ;
         PWM1 = (unsigned short int) (MAX_PWM/2 - tau1 - tau2) ;
         PWM2 = (unsigned short int) (MAX_PWM/2 + tau1 + tau2) ; break ;
         
      case HAS3 :
         PWM0 = (unsigned short int) (MAX_PWM/2 + tau1 + tau2) ;
         PWM1 = (unsigned short int) (MAX_PWM/2 - tau1 - tau2) ;
         PWM2 = (unsigned short int) (MAX_PWM/2 + tau1 - tau2) ; break ;
         
      case HAS4 :
         PWM0 = (unsigned short int) (MAX_PWM/2 + tau1 + tau2) ;
         PWM1 = (unsigned short int) (MAX_PWM/2 - tau1 + tau2) ;
         PWM2 = (unsigned short int) (MAX_PWM/2 - tau1 - tau2) ; break ;
         
      case HAS5 :
         PWM0 = (unsigned short int) (MAX_PWM/2 + tau1 - tau2) ;
         PWM1 = (unsigned short int) (MAX_PWM/2 + tau1 + tau2) ;
         PWM2 = (unsigned short int) (MAX_PWM/2 - tau1 - tau2) ; break ;
         
      case HAS6 :
         PWM0 = (unsigned short int) (MAX_PWM/2 - tau1 - tau2) ;
         PWM1 = (unsigned short int) (MAX_PWM/2 + tau1 + tau2) ;
         PWM2 = (unsigned short int) (MAX_PWM/2 - tau1 + tau2) ; break ;
         
      default :
         PWM0 = (unsigned short int) (MAX_PWM/2) ;
         PWM1 = (unsigned short int) (MAX_PWM/2) ;
         PWM2 = (unsigned short int) (MAX_PWM/2) ; break ;
      }
      
      PSC_Load (PWM0, PWM0+DEAD_TIME, PWM1, PWM1+DEAD_TIME, PWM2, PWM2+DEAD_TIME);     // for the motor running direction CCW
   }                                                                                   // PWMs are loaded to U, V, W

  Prescaler_Main_Tick -= 1;

   if (Prescaler_Main_Tick == 0)
   {
      Prescaler_Main_Tick = 78;                                                        // 78 * 64µS generates 5mS
      Main_Tick=1;
   }
   
   Clear_PC7();
}




/************************************************************************************************/
/*     The function will be called in every comparator interrupt                                */
/*         - PIND7 | PIND5 | PINC6 will be stored in the parameter Mem_Hall_Sector              */
/*         - Hall_Sector takes Mem_Hall_Sector over, which will be used for motor comutation    */
/************************************************************************************************/

inline void Do_Sensor_Interrupt(void)
{
   if ( Sensor_Counter_Up > 3 ) // DONE THE FIRST TIME
   {
      if (Delay_For_Change != 0)
      {
         /* Last Delay not finished : Force Change_Sector */
         Top_Counter = Mem_Top_Counter;
         if (Top_Counter == 0) 
         {
           Top_Counter++; /* to avoid "divide by 0" */
         }
         Sensor_Counter_Down = Mem_Top_Counter;
         Hall_Sector = Mem_Hall_Sector;
         /* end Change_Sector */
      }

      /* Filter and memorize the Conuter_Up in the Top_Counter */
      Mem_Top_CounterX8 = (((U16)7 * Mem_Top_CounterX8) + (U16)8 * Sensor_Counter_Up)>>3 ;   
      Mem_Top_Counter = Mem_Top_CounterX8 >> 3;

      Sensor_Counter_Up = 0; /* reset the Counter_Up */

      /* Get the status of the 3 Hall sensors */
      /* Hall_Sector = PIND7.PIND6.0.0.0.PINB2.0 */
      Mem_Hall_Sector = ( PIND & ( (1<<PIND7)|(1<<PIND5) ) ) | (PINC & (1<<PINC6)); 

      /* arm the Delay_For_Change */
      Delay_For_Change = Mem_Top_Counter - ADVANCE;

   } /* else false interrupt */

}

/***********************************************************/
/*     Comparator Interrupt                                */
/*         - call Do_Sensor_Interrupt()                    */
/***********************************************************/

#pragma vector = ANA_COMP0_vect
__interrupt void Hall_A(void)
 
{
   Do_Sensor_Interrupt();

}


#pragma vector = ANA_COMP1_vect
__interrupt void Hall_B(void)
 
{
   Do_Sensor_Interrupt();
}

 
#pragma vector = ANA_COMP2_vect
__interrupt void Hall_C(void)
 
{
   Do_Sensor_Interrupt();
}



void svpwm_init(void)
{
   Sensor_Counter_Up = 4;
   Mem_Top_Counter = 200;
   Top_Counter = Mem_Top_Counter+1;
   Delay_For_Change = 200;
}


void store_new_amplitude(U16 new_val)                          // use the value, read from Poti, to calculate the parameter Amplitude
{                                                              // in order to get the actual PWMs.
   Disable_interrupt();
   Amplitude = (U16)(((U32)MAX_AMPLITUDE * (U32)new_val)>>10);
   Enable_interrupt();
}

