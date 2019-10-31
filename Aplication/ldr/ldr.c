#include "ldr.h"
#include "ldr_driver.h"
#define N 10

void LDRInit(void)
{
	MX_ADC1_Init();
}

uint16_t LDR_Get(void)
{
	uint32_t adc = 0;
	uint16_t adc_value = 0;

	for(int i = 0; i < N; i++)
	{
		ADC1_Activate();
		adc_value = ADC1_Get();

		if(adc_value > 4096) // additional overflow protection
		    adc_value = 4096;

		adc += (4096 - adc_value);
	}
	adc_value = adc / N;

	return adc_value;
}
