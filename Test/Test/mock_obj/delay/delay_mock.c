#include "delay.h"

void delay(uint16_t value)
{
	return;
}

uint32_t sys_tick = 0;
uint32_t getSysTick(void)
{
    sys_tick++;
	return sys_tick;
}
