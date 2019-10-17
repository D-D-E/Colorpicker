#include "ldr_driver.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

uint16_t ADC1_value = 0;
uint16_t random_range_min = 0, random_range_max = 0;
bool random_active = 0;

void MX_ADC1_Init(void)
{}

void ADC1_Activate(void)
{}

uint16_t ADC1_Get()
{
    if(random_active)
    {
        ADC1_value = random_range_min + rand() % random_range_max;
    }
    return ADC1_value;
}

void SetADC1(uint16_t value)
{
    random_active = 0;
    ADC1_value = value;
}

void SetADC1_random(uint16_t min, uint16_t max)
{
    random_range_max = max;
    random_range_min = min;
    random_active = 1;
}
