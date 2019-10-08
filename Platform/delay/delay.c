#include "delay.h"

void delay(uint16_t value)
{
	LL_mDelay(value);
}

uint32_t get_sys_tick(void)
{
	return SysTick->VAL;
}
