#include "grBLDC.h"

//32M1 power stage controller

////////////////////////////////////////////////////////////////////////////////////////

void psc_init (void)
{
  // Output Pin configuration (used by PSC outputs)
  // PD0 => UH     PB7 => UL
  // PC0 => VH     PB6 => VL
  // PB0 => WH     PB1 => WL

  // Set MOSFET Drive pins low (soo all FETs are off when set to output in next step)
  PORTB &= ~(1<<PORTB7 | 1<<PORTB6 | 1<<PORTB1 | 1<<PORTB0);
  PORTC &= ~(1<<PORTC0);
  PORTD &= ~(1<<PORTD0);

  // Configure MOSFET pins to output
  DDRB |= (1<<DDB7)|(1<<DDB6)|(1<<DDB1)|(1<<DDB0);
  DDRC |= (1<<DDC0);
  DDRD |= (1<<DDD0);

  psc_connectAllMOSFETs(); //debug

   //SA_VAL: When PSC counter is less    than this value, high FET is enabled
   //SB_VAL: When PSC counter is greater than this value, low  FET is enabled
   //The difference between SA and SB sets the dead time between phases 
   //RA_VAL: Not used in centered mode //can be used to synchronize ADC
   //RB_VAL: Not used in centered mode 
   Psc_set_module_A(A_SA_VAL,A_RA_VAL,A_SB_VAL);
   Psc_set_module_B(B_SA_VAL,B_RA_VAL,B_SB_VAL);
   Psc_set_module_C(C_SA_VAL,C_RA_VAL,C_SB_VAL);
   Psc_set_register_RB(RB_VAL); //max value 12b free-running PSC counter counts up to

   Psc_config();

   Psc_config_input_0(PSC_OVERLAP_ENABLE,\
                      PSC_USE_COMPARATOR,\
                      PSC_USE_LOW_LEVEL,\
                      PSC_INPUT_FILTER_ENABLE,\
                      PSC_SYNCHRONOUS_OUTPUT_CONTROL,\
                      PSC_INPUT_NO_ACTION); //PSC input is ignored

   Psc_config_input_1(PSC_OVERLAP_ENABLE,\
                      PSC_USE_COMPARATOR,\
                      PSC_USE_HIGH_LEVEL,\
                      PSC_INPUT_FILTER_ENABLE,\
                      PSC_SYNCHRONOUS_OUTPUT_CONTROL,\
                      PSC_INPUT_NO_ACTION);

   Psc_config_input_2(PSC_OVERLAP_ENABLE,\
                      PSC_USE_COMPARATOR,\
                      PSC_USE_LOW_LEVEL,\
                      PSC_INPUT_FILTER_ENABLE,\
                      PSC_SYNCHRONOUS_OUTPUT_CONTROL,\
                      PSC_INPUT_NO_ACTION);

   PIFR = (1<<PEV2)|(1<<PEV1)|(1<<PEV0)|(1<<PEOP); //PSC interrupt flag register

   PIM = (0<<PEVE1)|(0<<PEVE1)|(0<<PEVE2)|(0<<PEOPE); //PSC interrupt mask register
                         //PEVE0 high: when fault occurs on PSC1, generate interrupt //low: no interrupt
                         //PEVE1 high: when fault occurs on PSC1, generate interrupt //low: no interrupt
                         //PEVE2 high: when fault occurs on PSC1, generate interrupt //low: no interrupt
                         //PEOPE high: PSC generates interrupt when end of cycle reached //low: no interrupt

   Psc_run();
}

//////////////////////////////////////////////////////////////////////////////////////////////////

//Set the duty cycle values in the PSC according to the value calculate by the regulation loop
  // duty =   0: Duty Cycle   0%
  // duty = 255: Duty Cycle 100%
void psc_commutateOutputWaveforms(uint8_t duty)
{ 
  if ( motor_state_get() == STOPPED )
  {
    psc_disconnectAllMOSFETs();

    //disable PWM on all FETs
    Psc_set_module_A(0,A_RA_VAL,0);
    Psc_set_module_B(0,B_RA_VAL,0);
    Psc_set_module_C(0,C_RA_VAL,0);
    //Syntax:
      //Psc_set_module_n(A_SA_VAL, A_RA_VAL, A_SB_VAL);
      //SA_VAL: When PSC counter is less    than this value, high FET is enabled
      //SB_VAL: When PSC counter is greater than this value, low  FET is enabled
      //The difference between SA and SB sets the dead time between phases 
      
      //RA_VAL: Not used in centered mode //can be used to synchronize ADC
      //RB_VAL: Not used in centered mode 
  }
  else //(motor_state_get() == RUNNING)
  {
    psc_connectAllMOSFETs();
    
    uint8_t hallState = hall_getPosition();

  	//flip hall bits (6->1, 5->2. 4->3, 3->4, 2->5, 1->6)
    if(motor_direction_get() == MOTOR_CCW) { hallState = ((~hallState) & 0b00000111); }

  	Psc_lock();

  	//Determine which two PSC outputs will generate PWM waveforms 
  	switch(hallState)
  	{
  		case 1:  
  		Psc_set_module_A(duty,A_RA_VAL,0); //PWM_Q1 (PSC0A)(PD0)
  		Psc_set_module_B(0,B_RA_VAL,0);
  		Psc_set_module_C(0,C_RA_VAL,duty); //PWM_Q6 (PSC2B)(PB1)
  		break;

  		case 2: //Set_Q3Q2(); 1A 0B
  		Psc_set_module_A(0,A_RA_VAL,duty); //PWM_Q2 (PSC0B)(PB7)
  		Psc_set_module_B(duty,B_RA_VAL,0); //PWM_Q3 (PSC1A)(PC0)
  		Psc_set_module_C(0,C_RA_VAL,0);
  		break;

  		case 3: //Set_Q3Q6(); 1A 2B
  		Psc_set_module_A(0,A_RA_VAL,0);
  		Psc_set_module_B(duty,B_RA_VAL,0); //PWM_Q3 (PSC1A)(PC0)
  		Psc_set_module_C(0,C_RA_VAL,duty); //PWM_Q6 (PSC2B)(PB1)
  		break;

  		case 4: //Set_Q5Q4(); 2A 1B
  		Psc_set_module_A(0,A_RA_VAL,0);
  		Psc_set_module_B(0,B_RA_VAL,duty); //PWM_Q4 (PSC1B)(PB6)
  		Psc_set_module_C(duty,C_RA_VAL,0); //PWM_Q5 (PSC2A)(PB0)
  		break;

  		case 5: //Set_Q1Q4(); 0A 1B
  		Psc_set_module_A(duty,A_RA_VAL,0); //PWM_Q1 (PSC0A)(PD0)
  		Psc_set_module_B(0,B_RA_VAL,duty); //PWM_Q4 (PSC1B)(PB6)
  		Psc_set_module_C(0,C_RA_VAL,0);
  		break;

  		case 6: //Set_Q5Q2(); 2A 0B
  		Psc_set_module_A(0,A_RA_VAL,duty); //PWM_Q2 (PSC0B)(PB7)
  		Psc_set_module_B(0,B_RA_VAL,0);
  		Psc_set_module_C(duty,C_RA_VAL,0); //PWM_Q5 (PSC2A)(PB0)
  		break;
        
  		default: psc_disconnectAllMOSFETs(); break;
  	}

    Psc_unlock();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void psc_disconnectAllMOSFETs(void)
{
  //set standard pin outputs low
  PORTB &= ( ~((1<<PORTB7)|(1<<PORTB6)|(1<<PORTB0)|(1<<PORTB1)) ); //Turn off Q2/Q4/Q5/Q6, respectively
  PORTC &= ( ~(1<<PORTC0) ); //turn off Q3
  PORTD &= ( ~(1<<PORTD0) ); //turn off Q1

  //POC: PSC output configuration
  POC = ( (0<<POEN0A)|(0<<POEN0B) |  //0:disconnect PSC outputs 0A & 0B from I/O pins //1:connect PSC output
          (0<<POEN1A)|(0<<POEN1B) |  //0:disconnect PSC outputs 1A & 1B from I/O pins //1:connect PSC output
          (0<<POEN2A)|(0<<POEN2B) ); //0:disconnect PSC outputs 2A & 2B from I/O pins //1:connect PSC output
}

//////////////////////////////////////////////////////////////////////////////////////////////////

//used if PSCs are controlling commutation
void psc_connectAllMOSFETs(void)
{
  //POC: PSC output configuration
  POC = ( (1<<POEN0A)|(1<<POEN0B) |  //0:disconnect PSC outputs 0A & 0B from I/O pins //1:connect PSC output
          (1<<POEN1A)|(1<<POEN1B) |  //0:disconnect PSC outputs 1A & 1B from I/O pins //1:connect PSC output
          (1<<POEN2A)|(1<<POEN2B) ); //0:disconnect PSC outputs 2A & 2B from I/O pins //1:connect PSC output
}

//////////////////////////////////////////////////////////////////////////////////////////////////

// uint8_t overcurrent = FALSE;
                      
// uint8_t inrush_mask_flag = FALSE;
// uint16_t inrush_delay = 0;

// //Disable overcurrent detection during startup (inrush current)
// void mc_disableOvercurrentDuringStartup(void)
// {
//   inrush_delay = (uint16_t) 500;
//   inrush_mask_flag = TRUE;
  
//   //disable over current
//   Psc_config_input_1(PSC_OVERLAP_ENABLE,\
//                      PSC_USE_COMPARATOR,\
//                      PSC_USE_HIGH_LEVEL,\
//                      PSC_INPUT_FILTER_ENABLE,\
//                      PSC_SYNCHRONOUS_OUTPUT_CONTROL,\
//                      PSC_INPUT_NO_ACTION);
// }

//////////////////////////////////////////////////////////////////////////////////////////////////

////manage delay when the overcurrent detection is disabled
//void mc_inrush_task(void)
//{ 
  //if (inrush_mask_flag == TRUE)
  //{
    //if (inrush_delay-- == 0)
    //{
        //inrush_mask_flag = FALSE;
      //
        ////enable over current
        //Psc_config_input_1(PSC_OVERLAP_ENABLE,\
                        //PSC_USE_COMPARATOR,\
                        //PSC_USE_HIGH_LEVEL,\
                        //PSC_INPUT_FILTER_ENABLE,\
                        //PSC_SYNCHRONOUS_OUTPUT_CONTROL,\
                        //PSC_INPUT_HALT);
    //}
  //}
//}
//
//// Overcurrent detection
//#ifdef __GNUC__
  //ISR(PSC_FAULT_vect)
//#else
//#pragma vector = PSC_FAULT_vect
//__interrupt void mc_overcurrent_detect(void)
//#endif
//{
  //PIFR = (1<<PEV1); // clear the interrupt
  //overcurrent = TRUE;
  //motor_stop();
//}