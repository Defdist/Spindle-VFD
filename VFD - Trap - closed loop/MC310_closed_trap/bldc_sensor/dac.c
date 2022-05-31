#include "grBLDC.h"

//digital to analog converter

//////////////////////////////////////////////////////////////////////////////////////////////////

// void dac_init(void)
// {
  //Amp1_config(); //JTS2doLater: Configure phase current amplifiers
  
  // Be careful : initialize DAC and Over_Current before PWM.
  // DAC is used for over current level
  //JTS2doLater: Handle overcurrent differently... AVR194 routes the DAC output to another micro
  //JTS2doLater: I've disconnected the DAC register from the pin, but right now no overcurrent.
  //Dac_config();
  /* set the overcurrent level */
  //Dac_set_8_bits(IMAX);
// }