#include "esp_task.h"
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
	while(ESP_SetModeBoth()==0)
	{
		gMissConnection++;
		ESP_Resset();
		delay(100);
		if(gMissConnection >= fails)
		{
			return 0;
		}
	}

	if(GPIO_Read_Pin(1) == 0)
	{
		ESP_SetModeSoftAP();
		ESP_SetParamsSoftAP("ESP", "12345678");
	}

	ESP_StartTCPServer(80);

	return 1;
}

static void pxESP(void * arg)
{
	uint8_t config_flag = 0;
	StatusLedInit();
	ESPInit();

	if(espStart(5))
	{
		StatusLedON();
	}
	else ErrorBlink();

	while(1)
	{
		if(strlen(GetSSID()) > 1 && config_flag == 0)
		{
			config_flag = 1;
			char ssid[64], paswd[64];
			strcpy(ssid, GetSSID());
			strcpy(paswd, GetPasw());
			if(ESP_SetModeBoth()==0, ESP_SetParamsStation(ssid, paswd)==0)
			{
				config_flag = 0;
			}
		}
		ESP_Request(PAGES, FUNCTIONS, 4);
		osDelay(10);
	}
}


void ESPTaskInit(void)
{
	xTaskCreate(pxESP, "ESP", configMINIMAL_STACK_SIZE, NULL, osPriorityAboveNormal, NULL);
}

