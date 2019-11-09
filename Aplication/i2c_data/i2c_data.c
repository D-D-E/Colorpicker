#include "i2c_data.h"
#include "crc.h"
#include "i2c.h"
#include "led.h"
#include "delay.h"

void I2C_Init()
{
	MX_I2C2_Init();
	MX_CRC_Init();
}

uint32_t check_sum[1] = {0};
void ColorToEEPROM() //save led to EEPROM
{
	uint16_t led[4] = {0,0,0,0};
	led[0] = Led_Get_Arr_Color()[0];
	led[1] = Led_Get_Arr_Color()[1];
	led[2] = Led_Get_Arr_Color()[2];

	check_sum[0] = CRC_calc((uint32_t *)led, 2);
	I2C2_SendData(0x00, (uint8_t *)Led_Get_Arr_Color(), 6);
	delay(5);
	I2C2_SendData(0x2A, (uint8_t *)check_sum, 4);
}

void setLedI2C() //load led from EEPROM
{
	uint16_t i2c_led[4] = {0, 0, 0, 0};
	uint32_t check_sum[2] = {0};

	I2C2_ReadData(0x00, (uint8_t *)i2c_led, 6);
	delay(5);
	I2C2_ReadData(0x2A, (uint8_t *)check_sum, 4);

	uint32_t check = CRC_calc((uint32_t *)i2c_led, 2);

	if(check_sum[0] == check)
	{
		Led_Set(i2c_led[eRed], i2c_led[eGreen], i2c_led[eBlue]);
	}
	else Led_Set(0, 0, 0);
}
