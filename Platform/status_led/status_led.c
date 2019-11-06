#include "status_led.h"
#include "main.h"
#include "delay.h"
#include "cmsis_os.h"


void StatusLedInit(void)
{
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);

  	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = LL_GPIO_PIN_13;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void StatusLedON()
{
	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_13);
}

void StatusLedOFF()
{
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_13);
}

void ErrorBlink()
{
	while(1)
	{
		LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_13);
		delay(200);
	}
}

void ErrorPowerBlink()
{
	while(1)
	{
		LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_13);
		delay(100);
	}
}

void APModeBlink()
{
	for(int i = 0; i < 20; i++)
	{
		LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_13);
		delay(50);
	}
	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_13);
}
