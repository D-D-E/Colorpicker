#include "led_driver.h"

uint32_t red, green, blue;

void MX_TIM4_Init(void)
{}

void TIM4_SET_CH1(uint16_t duty_cycle)
{
    red = duty_cycle;
}

void TIM4_SET_CH2(uint16_t duty_cycle)
{
    green = duty_cycle;
}

void TIM4_SET_CH3(uint16_t duty_cycle)
{
    blue = duty_cycle;
}

uint16_t Get_CH1(void)
{
    return red;
}

uint16_t Get_CH2(void)
{
    return green;
}

uint16_t Get_CH3(void)
{
    return blue;
}
