#include "grBLDC.h"

void setPC3_high(void)
{
	SLOWDOWN_DDR |= SLOWDOWN_MASK;
	SLOWDOWN_PORT |= SLOWDOWN_MASK;
}

void setPC3_low(void)
{
	SLOWDOWN_PORT &= ~(SLOWDOWN_MASK);
}