#include "led.h"
#include "led_driver.h"

uint32_t led[3] = {0, 0, 0};

void LedInit(void)
{
	MX_TIM4_Init();
}

void Led_Set(uint16_t red, uint16_t green, uint16_t blue)
{
	led[0] = red;
	led[1] = green;
	led[2] = blue;
}

void Led_Set_Color(color color, uint16_t value)
{
	switch(color)
	{
		case eRed: led[0] = value; break;
		case eGreen: led[1] = value; break;
		case eBlue: led[2] = value; break;
		default: break;
	}

}

uint16_t Led_Get_Color(color color)
{
	switch(color)
	{
		case eRed: return led[0]; break;
		case eGreen: return led[1]; break;
		case eBlue: return led[2]; break;
		default: break;
	}
	return 0;
}

static uint16_t map(uint16_t value, uint16_t max_value)
{
	uint16_t map_res = value * max_value / 65535;
	return map_res;
}

void Led_Refresh(uint16_t max_value)
{
	TIM4_SET_CH1(map(led[0], max_value));
	TIM4_SET_CH2(map(led[1], max_value));
	TIM4_SET_CH3(map(led[2], max_value));
}
