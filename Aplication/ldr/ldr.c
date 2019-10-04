#include "ldr.h"
#include "ldr_driver.h"
#define N 10

void LDRInit(void)
{
	MX_ADC1_Init();
}

uint16_t LDR_Get(void)
{
	uint64_t adc = 0;
	uint16_t adc_value = 0;

	for(int i = 0; i < N; i++)
	{
		ADC1_Activate();
		adc += (((4095 - ADC1_Get()) * 65535) / 4095);

		adc_value = adc / N;
	}

	return adc_value;
}
