#include "grBLDC.h"

void setPC3_high(void) { SLOWDOWN_DDR |= SLOWDOWN_MASK; SLOWDOWN_PORT |= SLOWDOWN_MASK; }

void setPD3_high(void) { PD3_DDR |= PD3_MASK; PD3_PORT |= PD3_MASK; }

void setPC3_low(void) { SLOWDOWN_PORT &= ~(SLOWDOWN_MASK); }

void setPD3_low(void) { PD3_PORT &= ~(PD3_MASK); }