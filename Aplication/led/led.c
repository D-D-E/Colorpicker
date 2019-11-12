#include "led.h"
#include "led_driver.h"

uint16_t led[3] = {0, 0, 0};

void LedInit(void)
{
	MX_TIM4_Init();
}

static uint16_t OverflowProtection(uint16_t value)
{
    if(value > 4096)
        return 4096;
    return value;
}

void Led_Set(uint16_t red, uint16_t green, uint16_t blue)
{
	led[0] = OverflowProtection(red);
	led[1] = OverflowProtection(green);
	led[2] = OverflowProtection(blue);
}

void Led_Set_Color(color color, uint16_t value)
{
	if(color >= 0 && color < 3)
	{
		led[color] = OverflowProtection(value);
	}
}

uint16_t Led_Get_Color(color color)
{
	return led[color];
}

uint16_t * Led_Get_Arr_Color()
{
	return led;
}

static uint16_t map(uint16_t value, uint16_t max_value)
{
	uint16_t map_res = value * max_value / 4096;

	return map_res;
}

void Led_Refresh(uint16_t max_value)
{
	TIM4_SET_CH1(map(led[0], max_value));
	TIM4_SET_CH2(map(led[1], max_value));
	TIM4_SET_CH3(map(led[2], max_value));
}
