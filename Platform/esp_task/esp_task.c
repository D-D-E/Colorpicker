#include "esp_task.h"
#include "ESP8266.h"
#include "request.h"
#include "status_led.h"
#include "cmsis_os.h"

static uint8_t gMissConnection = 0;
static uint8_t espStart(int fails)
{
	while((ESP_SetModeSoftAP()==0) || (ESP_SetParamsSoftAP("ESP", "12345678")==0) || (ESP_StartTCPServer(80)==0))
	{
		gMissConnection++;
		////LL_mDelay(200);
		ESP_Resset();
		if(gMissConnection >= fails)
		{
			return 0;
		}
	}
	return 1;
}

static void pxESP(void * arg)
{
	StatusLedInit();
	ESPInit();

	if(!espStart(5))
	{
		ErrorBlink();
	}
	else StatusLedON();

	while(1)
	{
		ESP_Request(PAGES, FUNCTIONS, 2);
		osDelay(10);
	}
}


void ESPTaskInit(void)
{
	xTaskCreate(pxESP, "ESP", configMINIMAL_STACK_SIZE, NULL, osPriorityAboveNormal, NULL);
}
