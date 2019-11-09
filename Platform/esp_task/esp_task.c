#include "esp_task.h"
#include "i2c.h"
#include "encoder_driver.h"
#include "ESP8266.h"
#include "delay.h"
#include "request.h"
#include "status_led.h"
#include "cmsis_os.h"
#include <string.h>
#include <stdbool.h>

static uint8_t gMissConnection = 0;

static uint8_t espStart(int fails)
{
	if(GPIO_Read_Pin(1) == 0) //if encoder button pushed turn softAP
	{
		while(ESP_SetModeSoftAP()==0 || ESP_SetParamsSoftAP("ESP", "12345678")==0 || ESP_StartTCPServer(80)==0)
		{
			gMissConnection++;
			ESP_Resset();
			if(gMissConnection >= fails)
			{
				return 0;
			}
		}

	}
	else //else read ssid and passwd from EEPROM and connect to wifi
	{
		char ssid[64], paswd[64];

		I2C2_ReadData(0xA0, (uint8_t *)ssid, 32);
		delay(5);
		I2C2_ReadData(0xD0, (uint8_t *)paswd, 32);

		while(strlen(ssid)==0 || ESP_SetModeStation()==0 || ESP_SetParamsStation(ssid, paswd)==0 || ESP_StartTCPServer(80)==0)
		{
			I2C2_ReadData(0xA0, (uint8_t *)ssid, 32);
			delay(5);
			I2C2_ReadData(0xD0, (uint8_t *)paswd, 32);

			gMissConnection++;
			ESP_Resset();
			if(gMissConnection >= fails)
			{
				return 0;
			}
		}
	}

	return 1;
}

static void pxESP(void * arg)
{
	uint8_t config_flag = 0;
	StatusLedInit();
	ESPInit();

	if(espStart(5)) // start blinking if cannot start
	{
		StatusLedON();
	}

	while(1)
	{
		if(strlen(GetSSID()) > 1 && config_flag == 0) // check if change wifi settings
		{
			ESP_StopTCPServer(80); //dummy for reset tcp server flag
			config_flag = 1;

			if(ESP_SetModeBoth()==0 || ESP_SetParamsStation(GetSSID(), GetPasw())==0 || ESP_StartTCPServer(80)==0)
			{
				config_flag = 0;
			}
			//APModeBlink();
			I2C2_SendData(0xA0, (uint8_t *)GetSSID(), 32); //save new wifi settings
			delay(5);
			I2C2_SendData(0xD0, (uint8_t *)GetPasw(), 32);
		}

		ESP_Request(PAGES, FUNCTIONS, 4); // process requests
		osDelay(10);
	}
}


void ESPTaskInit(void)
{
	xTaskCreate(pxESP, "ESP", configMINIMAL_STACK_SIZE, NULL, osPriorityAboveNormal, NULL);
}

