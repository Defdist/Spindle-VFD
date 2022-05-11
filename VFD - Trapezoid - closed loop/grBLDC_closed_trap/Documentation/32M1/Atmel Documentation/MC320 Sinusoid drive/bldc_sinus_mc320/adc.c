//!
//! @file $RCSfile: adc.c,v $
//!
//! Copyright (c) 2006 Atmel.
//!
//! @brief Initialize and Read ADC functions
//!
//! @version $Revision: 1.5 $
//!

//_____  I N C L U D E S ___________________________________________________

#include <ioavr.h>

#include "config.h"
#include "inavr.h"
#include "adc.h"
#include "adc_drv.h"


//_____ M A C R O S ________________________________________________________


//_____ D E F I N I T I O N S ______________________________________________
#define USE_ADC

#define ADC_RIGHT_ADJUST_RESULT                 0 //!< 0: Result left adjusted  1: Result right adjusted
#define ADC_HIGH_SPEED_MODE                     1 //
#define ADC_INTERNAL_VREF                       1 //!< 0: External Vref         1: Internal Vref  2: Vref is connected to Vcc
#define ADC_IT                                  1 //!< 0: No ADC End of Conv IT 1: ADC End of conversion generates an IT
#define ADC_PRESCALER                           4 //!< 2, 4, 8, 16, 32, 64, 128  : The input ADC frequency is the system clock frequency divided by the const value


//_____ D E C L A R A T I O N S ____________________________________________
volatile U8   Flag_IT_ADC = 0 ;

/**********************************************************/
/*           ADC Initiation                               */
/*           - reference voltage                          */
/*           - Poti as input                              */
/*           - Amplification configuration                */
/**********************************************************/


void ADC_Init(void)
{

   /* Digital Input Disable Register 0 */
   DIDR0 = (0<<ADC7D) | (0<<ADC6D ) | (0<<ADC5D ) | (0<<ADC4D ) | (0<<ADC3D ) | (0<<ADC2D ) | (0<<ADC1D ) | (0<<ADC0D );

   /* Digital Input Disable Register 1 */
   /* disable digital input on AMP 0 */
   /* disable digital input on AMP 0 */
   DIDR1 = (0<<ACMP0D) | (1<<AMP0PD) | (1<<AMP0ND) | (0<<ADC10D) | (1<<ADC9D) | (1<<ADC8D);

   /* init amplifier 0 */
   /* Amplifier enable */
   /* Amplifier is activated by the compare match of Timer 0 */
   AMP0CSR = (1 <<AMP0EN) | (0 <<AMP0IS) | (AMP_GAIN_20 <<AMP0G0) | (AMP_TRIG_ON_PSC0 <<AMP0TS0);


   /* init ADC */
   /* select input */
   ADMUX = (ADC_VREF_INTERNAL <<REFS0) | (0 <<ADLAR) | (ADC_INPUT_ISRC <<MUX0);

   /* High Speed Mode   */ 
   ADCSRB = (1<<ADHSM) | (ADC_TRIG_SRC_FREE_RUNNING <<ADTS0);

}

/* ADC enable          */
/* start conversion */
/* interrupt enable    */
void   Start_ADC(void)
{
   ADCSRA = (1<<ADEN) | (1<<ADSC) | (0<<ADATE) | (1<<ADIE) | (ADC_PRESCALER_16 <<ADPS0) ;
}

/**********************************************************/
/*           read value from ADC                          */
/**********************************************************/


S16 read_acquisition(void)
{
   Union16     resultADC ;

   LSB(resultADC) = ADCL ;  // the ADC output has 10 bit resolution
   MSB(resultADC) = ADCH ;

   return (resultADC.w) ;
}


/**********************************************************/
/*           ADC Interrupt                                */
/**********************************************************/

#pragma vector = ADC_vect
__interrupt void Read_Measure(void)
{
   Flag_IT_ADC=1;
}

