#include "led.h"
#include "led_driver.h"

uint16_t led[3] = {0, 0, 0};

void LedInit(void)
{
    MX_TIM4_Init();
}

static uint16_t OverflowProtection(uint16_t value)
{
    if(value > 4095)
        return 4095;
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
    switch(color)
    {
        case eRed: led[0] = OverflowProtection(value); break;
        case eGreen: led[1] = OverflowProtection(value); break;
        case eBlue: led[2] = OverflowProtection(value); break;
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
    uint16_t map_res = value * max_value / 4095;

    return map_res;
}

void Led_Refresh(uint16_t max_value)
{
    TIM4_SET_CH1(map(led[0], max_value));
    TIM4_SET_CH2(map(led[1], max_value));
    TIM4_SET_CH3(map(led[2], max_value));
}

uint16_t * Led_Get_Arr_Color(void)
{
    return led;
}
