#include "i2c_data.h"
#include "ESP8266.h"
#include "crc.h"
#include "i2c.h"
#include "led.h"
#include "delay.h"

#define LED_ADDR 				0x00
#define LED_CHECK_SUM_ADDR		0x2A
#define SSID_ADDR				0xA0
#define PASWD_ADDR				0xD0
#define WIFI_CHECK_SUM			0xC2

void I2C_Init()
{
	MX_I2C2_Init();
	MX_CRC_Init();
}

void ColorToEEPROM() //save led to EEPROM
{
	uint32_t check_sum[1] = {0};
	uint16_t i2c_led[4] = {0,0,0,0};
	i2c_led[0] = Led_Get_Arr_Color()[0];
	i2c_led[1] = Led_Get_Arr_Color()[1];
	i2c_led[2] = Led_Get_Arr_Color()[2];

	check_sum[0] = CRC_calc((uint32_t *)i2c_led, 2);
	I2C2_SendData(LED_ADDR, (uint8_t *)i2c_led, 6);
	delay(5);
	I2C2_SendData(LED_CHECK_SUM_ADDR, (uint8_t *)check_sum, 4);
}

void ColorFromEEPROM() //load led from EEPROM
{
	uint16_t i2c_led[4] = {0, 0, 0, 0};
	uint32_t check_sum[1] = {0};

	I2C2_ReadData(LED_ADDR, (uint8_t *)i2c_led, 6);
	delay(5);
	I2C2_ReadData(LED_CHECK_SUM_ADDR, (uint8_t *)check_sum, 4);

	uint32_t check = CRC_calc((uint32_t *)i2c_led, 2);

	if(check_sum[0] == check)
	{
		Led_Set(i2c_led[eRed], i2c_led[eGreen], i2c_led[eBlue]);
	}
	else Led_Set(0, 0, 0);
}

void WifiToEEPROM()
{
	uint32_t check_sum[2] = {0};
	check_sum[0] = CRC_calc((uint32_t *)GetSSID(), 16);
	check_sum[1] = CRC_calc((uint32_t *)GetPasw(), 16);

	I2C2_SendData(SSID_ADDR, (uint8_t *)GetSSID(), 32);
	delay(5);
	I2C2_SendData(PASWD_ADDR, (uint8_t *)GetPasw(), 32);
	delay(5);
	I2C2_SendData(WIFI_CHECK_SUM, (uint8_t *)check_sum, 8);
}

void WifiFromEEPROM(uint8_t * ssid, uint8_t * paswd)
{
	uint32_t check_sum[2] = {0};

	I2C2_ReadData(SSID_ADDR, (uint8_t *)ssid, 32);
	delay(5);
	I2C2_ReadData(PASWD_ADDR, (uint8_t *)paswd, 32);
	delay(5);
	I2C2_ReadData(WIFI_CHECK_SUM, (uint8_t *)check_sum, 8);

	uint32_t check_SSID = CRC_calc((uint32_t *)ssid, 2);
	uint32_t check_PASWD = CRC_calc((uint32_t *)paswd, 2);

	if(check_SSID != check_sum[0] || check_PASWD != check_sum[1])
	{
		ssid = NULL;
		paswd = NULL;
	}
}
