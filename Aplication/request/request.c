#include "request.h"
#include "led.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

const char *PAGES[] = {"GET /PICKER ", "GET /PICKER?picker="};
const foo FUNCTIONS[] = {PICKER, PICKER_picker};

const char htmlpicker1[] = {"<html><head><title>ESP8266</title></head><body><script>let flag = true;function setFlag(){flag = false;};function reload(){console.log(flag);if(flag){document.location.reload(true);}};setTimeout(reload, 5000);</script><p>Choose your color:</p><form method=\"get\"><input type=\"color\" value=\"#"};
const char htmlpicker2[] = {"\" id=\"cp\" onclick=\"setFlag()\" name=\"picker\" /><input type=\"submit\" value=\"SEND\" /></form></body></html>"};

const char statusOK[] = {"HTTP/1.1 200 OK\r\nConnection: Keep-Alive\r\nContent-Type: text/html"};
const char statusOK_CL0[] = {"HTTP/1.1 200 OK\r\nConnection: Keep-Alive\r\nContent-Type: text/html\r\nContent-Length: 0"};

void PICKER()
{
	char hex[7], ContentLength[22];

	ESP_SendConstData(statusOK, strlen(statusOK), 1);

	int length = strlen(htmlpicker1) + strlen(htmlpicker2) + 6;
	sprintf(ContentLength, "Content-Length: %04d\r\n", length);
	ESP_SendData(ContentLength, 22, 1);

	sprintf(hex, "%02x%02x%02x", Led_Get_Color(eRed)*255/65535, Led_Get_Color(eGreen)*255/65535, Led_Get_Color(eBlue)*255/65535);

	ESP_SendConstData(htmlpicker1, strlen(htmlpicker1), 0);
	ESP_SendData(hex, 6, 0);
	ESP_SendConstData(htmlpicker2, strlen(htmlpicker2), 1);
}

void PickerSetLed()
{
	char * search;
	search = strstr(ESP_GetRequest(), "?picker=%");
	if(search != NULL)
	{
		char hex[2];
		uint16_t colors[3] = {0, 0, 0};
		for(int i = 0, l = 0; i < 6; i += 2, l++)
		{
			int position = search - ESP_GetRequest() + 11 + i;
			hex[0] = ESP_GetRequest()[position];
			hex[1] = ESP_GetRequest()[position + 1];
			colors[l] = strtol(hex, NULL, 16);
		}
		Led_Set(colors[0]*65535/255, colors[1]*65535/255, colors[2]*65535/255);
	}
}

void PICKER_picker()
{
	PickerSetLed();

	PICKER();
}
