#include "i2c.h"
#include "main.h"
#include "delay.h"

#define I2C_REQUEST_WRITE                       0x00
#define I2C_REQUEST_READ                        0x01
#define SLAVE_OWN_ADDRESS                       0xA0
#define TIMEOUT									100

void MX_I2C2_Init(void)
{
	LL_I2C_InitTypeDef I2C_InitStruct = {0};
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
	  /**I2C2 GPIO Configuration
	  PB10   ------> I2C2_SCL
	  PB11   ------> I2C2_SDA
	  */
	GPIO_InitStruct.Pin = LL_GPIO_PIN_10|LL_GPIO_PIN_11;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2);

	  /** I2C Initialization
	  */
	LL_I2C_DisableOwnAddress2(I2C2);
	LL_I2C_DisableGeneralCall(I2C2);
	LL_I2C_EnableClockStretching(I2C2);
	I2C_InitStruct.PeripheralMode = LL_I2C_MODE_I2C;
	I2C_InitStruct.ClockSpeed = 100000;
	I2C_InitStruct.DutyCycle = LL_I2C_DUTYCYCLE_2;
	I2C_InitStruct.OwnAddress1 = 0;
	I2C_InitStruct.TypeAcknowledge = LL_I2C_ACK;
	I2C_InitStruct.OwnAddrSize = LL_I2C_OWNADDRESS1_7BIT;
	LL_I2C_Init(I2C2, &I2C_InitStruct);
	LL_I2C_SetOwnAddress2(I2C2, 0);
}

bool I2C2_SendData(uint16_t addr, uint8_t * data, uint32_t data_length)
{
	LL_I2C_DisableBitPOS(I2C2);
	LL_I2C_AcknowledgeNextData(I2C2, LL_I2C_ACK);
	LL_I2C_GenerateStartCondition(I2C2);
	while(!LL_I2C_IsActiveFlag_SB(I2C2));

	(void) I2C2->SR1;
	LL_I2C_TransmitData8(I2C2, SLAVE_OWN_ADDRESS | I2C_REQUEST_WRITE);
	while(!LL_I2C_IsActiveFlag_ADDR(I2C2));

	LL_I2C_ClearFlag_ADDR(I2C2);

	LL_I2C_TransmitData8(I2C2, (uint8_t) (addr>>8));
	while(!LL_I2C_IsActiveFlag_TXE(I2C2));

	LL_I2C_TransmitData8(I2C2, (uint8_t) addr);
	while(!LL_I2C_IsActiveFlag_TXE(I2C2));

	for(int i = 0; i < data_length; i++)
	{
		LL_I2C_TransmitData8(I2C2, data[i]);
		while(!LL_I2C_IsActiveFlag_TXE(I2C2));
	}
	LL_I2C_GenerateStopCondition(I2C2);
	return 1;
}

bool I2C2_ReadData(uint16_t addr, uint8_t * data, uint32_t data_length)
{
  LL_I2C_DisableBitPOS(I2C2);
  LL_I2C_AcknowledgeNextData(I2C2, LL_I2C_ACK);
  LL_I2C_GenerateStartCondition(I2C2);
  while(!LL_I2C_IsActiveFlag_SB(I2C2));

  (void) I2C2->SR1;
  LL_I2C_TransmitData8(I2C2, SLAVE_OWN_ADDRESS | I2C_REQUEST_WRITE);
  while(!LL_I2C_IsActiveFlag_ADDR(I2C2));

  LL_I2C_ClearFlag_ADDR(I2C2);
  LL_I2C_TransmitData8(I2C2, (uint8_t) (addr>>8));
  while(!LL_I2C_IsActiveFlag_TXE(I2C2));

  LL_I2C_TransmitData8(I2C2, (uint8_t) addr);
  while(!LL_I2C_IsActiveFlag_TXE(I2C2));

  LL_I2C_GenerateStartCondition(I2C2);
  while(!LL_I2C_IsActiveFlag_SB(I2C2));
  (void) I2C2->SR1;
  LL_I2C_TransmitData8(I2C2, SLAVE_OWN_ADDRESS | I2C_REQUEST_READ);
  while (!LL_I2C_IsActiveFlag_ADDR(I2C2));
  LL_I2C_ClearFlag_ADDR(I2C2);
  for(int i = 0; i < data_length; i++)
  {
    if(i < (data_length-1))
    {
      while(!LL_I2C_IsActiveFlag_RXNE(I2C2));
      data[i] = LL_I2C_ReceiveData8(I2C2);
    }
    else
    {
      LL_I2C_AcknowledgeNextData(I2C2, LL_I2C_NACK);
      LL_I2C_GenerateStopCondition(I2C2);
      while(!LL_I2C_IsActiveFlag_RXNE(I2C2));
      data[i] = LL_I2C_ReceiveData8(I2C2);
    }
  }
  return 1;
}
