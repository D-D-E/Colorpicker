#include "encoder_driver.h"

static bool button_status = false, rotate_status = false, rotate_pin_A, rotate_pin_B;

void GPIO_Init()
{
    LL_EXTI_InitTypeDef EXTI_InitStruct = {0};

    EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_1;
    EXTI_InitStruct.LineCommand = ENABLE;
    EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
    EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
    LL_EXTI_Init(&EXTI_InitStruct);

    EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_14;
    EXTI_InitStruct.LineCommand = ENABLE;
    EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
    EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_FALLING;
    LL_EXTI_Init(&EXTI_InitStruct);

    LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTB, LL_GPIO_AF_EXTI_LINE1);
    LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTB, LL_GPIO_AF_EXTI_LINE14);


	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = LL_GPIO_PIN_1 | LL_GPIO_PIN_14 | LL_GPIO_PIN_15;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    NVIC_SetPriority(EXTI1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),8, 0));
    NVIC_EnableIRQ(EXTI1_IRQn);


    NVIC_SetPriority(EXTI15_10_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),8, 0));
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void EXTI1_IRQHandler(void)
{
	LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_1);

	button_status = true;
}

void EXTI15_10_IRQHandler(void)
{
	LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_14);

	rotate_status = true;
	rotate_pin_A = GPIO_Read_Pin(14);
	rotate_pin_B = GPIO_Read_Pin(15);
}

bool GetButton(void)
{
	return button_status;
}

void ClearButton()
{
    button_status = false;
}

bool GetRotateStatus(void)
{
	return rotate_status;
}

void ClearRotateStatus()
{
    rotate_status = false;
}

bool GetRotatePinB()
{
	return rotate_pin_A;
}

bool GetRotatePinA()
{
	return rotate_pin_B;
}

uint8_t GPIO_Read_Pin(uint8_t mask)
{
	uint16_t port_bits = LL_GPIO_ReadInputPort(GPIOB);
	return ((port_bits & (1 << mask)) != 0);
}
