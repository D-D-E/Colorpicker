#ifndef ENCODER_DRIVER_ENCODER_DRIVER_H_
#define ENCODER_DRIVER_ENCODER_DRIVER_H_
#include "main.h"
#include "stdint.h"
#include "stdbool.h"

bool GetButton(void);
void ClearButton(void);

bool GetRotateStatus(void);
void ClearRotateStatus();
bool GetRotatePinA();
bool GetRotatePinB();

void GPIO_Init();
uint8_t GPIO_Read_Pin(uint8_t mask);

void EXTI1_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

#endif /* ENCODER_DRIVER_ENCODER_DRIVER_H_ */
