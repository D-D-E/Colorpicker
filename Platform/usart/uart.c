#include "uart.h"
#include "ring_buffer.h"

//char uart_rx_buffer[512];

void USART_SendData_byte(char data)
{
	LL_USART_TransmitData8(USART1, data);
	while (!LL_USART_IsActiveFlag_TC(USART1));
}

void USART_SendData(char * data, uint32_t data_length)
{
	for(int i = 0; i < data_length; i++)
	{
		LL_USART_TransmitData8(USART1, data[i]);
		LL_mDelay(2);
		while (!LL_USART_IsActiveFlag_TC(USART1));
	}
}

void USART_CharReception_Callback(void)
{
	__IO uint32_t received_char;
	received_char = LL_USART_ReceiveData8(USART1);

	RingBuff_Push(received_char);
  //LL_USART_TransmitData8(USART1, received_char);
}

void Error_Callback(void)
{
  __IO uint32_t sr_reg;

  NVIC_DisableIRQ(USART1_IRQn);

  sr_reg = LL_USART_ReadReg(USART1, SR);
  if (sr_reg & LL_USART_SR_NE)
  {

  }
}

void USART1_IRQHandler(void)
{
  if(LL_USART_IsActiveFlag_RXNE(USART1) && LL_USART_IsEnabledIT_RXNE(USART1))
  {
    USART_CharReception_Callback();
  }
  else
  {
    Error_Callback();
  }
}

void USART1_Device_Reset(void)
{
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_8);
	LL_mDelay(100);
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_8);
}

void MX_USART1_UART_Init(void)
{
  LL_USART_InitTypeDef USART_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_9;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;

  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;

  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USART1 interrupt Init */
  NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(USART1_IRQn);

  USART_InitStruct.BaudRate = 115200;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;

  LL_USART_Init(USART1, &USART_InitStruct);
  LL_USART_ConfigAsyncMode(USART1);
  LL_USART_Enable(USART1);

  LL_USART_EnableIT_RXNE(USART1);
  LL_USART_EnableIT_ERROR(USART1);

  //Reset gpio
  GPIO_InitStruct.Pin = LL_GPIO_PIN_8;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_8);
}

