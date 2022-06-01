#include "grBLDC.h"

//32M1 power stage controller

////////////////////////////////////////////////////////////////////////////////////////

void psc_init (void)
{
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
void psc_configureOutputWaveforms(uint8_t duty)
{
  #if(CURRENT_DECAY == SLOW_DECAY_SYNCHRONOUS)
    uint8_t dutydt;   /* duty with dead time */
    if (duty >= DEADTIME) {dutydt = duty - DEADTIME;}
  #endif
   
  Psc_lock();

  // Duty = 0   => Duty Cycle   0%
  // Duty = 255 => Duty Cycle 100%
 
  //SA_VAL: When PSC counter is less    than this value, high FET is enabled
  //SB_VAL: When PSC counter is greater than this value, low  FET is enabled
  //The difference between SA and SB sets the dead time between phases 
  
  //RA_VAL: Not used in centered mode //can be used to synchronize ADC
  //RB_VAL: Not used in centered mode
  
  //Psc_set_module_n(A_SA_VAL, A_RA_VAL, A_SB_VAL);

  //while all six PSC phases are chopping simultaneously, only two phases are routed to output pins at the same time //see mosfet_commutate()
  // #if (CURRENT_DECAY == FAST_DECAY)
  //   Psc_set_module_A(duty,A_RA_VAL,duty);
  //   Psc_set_module_B(duty,B_RA_VAL,duty);
  //   Psc_set_module_C(duty,C_RA_VAL,duty);

  // #elif (CURRENT_DECAY == SLOW_DECAY_SYNCHRONOUS)
  //   Psc_set_module_A(duty,A_RA_VAL,dutydt);
  //   Psc_set_module_B(duty,B_RA_VAL,dutydt);
  //   Psc_set_module_C(duty,C_RA_VAL,dutydt);

  // #else //SLOW_DECAY
  //   Psc_set_module_A(duty,A_RA_VAL,0);
  //   Psc_set_module_B(duty,B_RA_VAL,0);
  //   Psc_set_module_C(duty,C_RA_VAL,0);
  // #endif
   
  if(motor_direction_get() == CCW) //JTS2doNow: Sample direction pin (PB3) to determine spindle direction
  {
      // switch(hallState)
      // {
      //     case 1: Set_Q5Q2(); break;  
      //     case 2: Set_Q1Q4(); break;
      //     case 3: Set_Q5Q4(); break;
      //     case 4: Set_Q3Q6(); break;
      //     case 5: Set_Q3Q2(); break;
      //     case 6: Set_Q1Q6(); break;
      //     default: mosfet_turnOffAll(); break;
      // }
  }
  else //direction == CW
  {
      switch(hallState)
      {
          case 1: //Set_Q1Q6(); //0A 2B
            Psc_set_module_A(duty,A_RA_VAL,0);
            Psc_set_module_B(0,B_RA_VAL,0);
            Psc_set_module_C(0,C_RA_VAL,duty);
          break;

          case 2: //Set_Q3Q2(); 1A 0B
            Psc_set_module_A(0,A_RA_VAL,duty);
            Psc_set_module_B(duty,B_RA_VAL,0);
            Psc_set_module_C(0,C_RA_VAL,0);
          break;

          case 3: //Set_Q3Q6(); 1A 2B
            Psc_set_module_A(0,A_RA_VAL,0);
            Psc_set_module_B(duty,B_RA_VAL,0);
            Psc_set_module_C(0,C_RA_VAL,duty);
          break;

          case 4: //Set_Q5Q4(); 2A 1B
            Psc_set_module_A(0,A_RA_VAL,0);
            Psc_set_module_B(0,B_RA_VAL,duty);
            Psc_set_module_C(duty,C_RA_VAL,0);
          break;

          case 5: //Set_Q1Q4(); 0A 1B
            Psc_set_module_A(duty,A_RA_VAL,0);
            Psc_set_module_B(0,B_RA_VAL,duty);
            Psc_set_module_C(0,C_RA_VAL,0);
          break;

          case 6: //Set_Q5Q2(); 2A 0B
            Psc_set_module_A(0,A_RA_VAL,duty);
            Psc_set_module_B(0,B_RA_VAL,0);
            Psc_set_module_C(duty,C_RA_VAL,0);
          break;
          
          default: /*mosfet_turnOffAll();*/ break;
      }
  }

  Psc_unlock();
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