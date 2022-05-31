#include "grBLDC.h"

//analog comparators

//////////////////////////////////////////////////////////////////////////////////////////////////

void comparator_init(void)
{
  //JTS2doLater: We'll eventually use these to throttle back current, using 1V1 bandgap 
  Comp_0_config();
  Comp_1_config();
  Comp_2_config();
}