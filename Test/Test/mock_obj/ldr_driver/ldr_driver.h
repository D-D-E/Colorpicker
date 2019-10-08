#ifndef LDR_DRIVER_LDR_DRIVER_H_
#define LDR_DRIVER_LDR_DRIVER_H_
#include "stdint.h"

void MX_ADC1_Init(void);
void ADC1_Activate(void);
void ADC1_2_IRQHandler(void);
uint16_t ADC1_Get();

void SetADC1(uint16_t value);

#endif
