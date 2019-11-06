#include "delay.h"

void delay(uint16_t value)
{
	LL_mDelay(value);
}

uint32_t getSysTick(void)
{
	return SysTick->VAL;
}
