#include "grBLDC.h"

void unoPinA4_input(void) { SLOWDOWN_DDR &= ~(SLOWDOWN_MASK); }
void unoPinA2_input(void) {      PD3_DDR &= ~(     PD3_MASK); }

void unoPinA4_high(void) { SLOWDOWN_DDR |= SLOWDOWN_MASK; SLOWDOWN_PORT |= SLOWDOWN_MASK; }
void unoPinA2_high(void) {      PD3_DDR |=      PD3_MASK;      PD3_PORT |=      PD3_MASK; }

void unoPinA4_low(void) { SLOWDOWN_DDR |= SLOWDOWN_MASK; SLOWDOWN_PORT &= ~(SLOWDOWN_MASK); }
void unoPinA2_low(void) {      PD3_DDR |=      PD3_MASK;      PD3_PORT &= ~(     PD3_MASK); }