#include "request.h"
#include "led.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "ESP8266.h"

const char *PAGES[] = {"GET /PICKER ", "GET /PICKER?picker="};
const foo FUNCTIONS[] = {PICKER, PICKER_parse};

const char htmlpicker1[] = {"<html><head><title>ESP8266</title></head><body><script>let flag = true;function setFlag(){flag = false;};function reload(){console.log(flag);if(flag){document.location.reload(true);}};setTimeout(reload, 5000);</script><p>Choose your color:</p><form method=\"get\"><input type=\"color\" value=\"#"};
const char htmlpicker2[] = {"\" id=\"cp\" onclick=\"setFlag()\" name=\"picker\" /><input type=\"submit\" value=\"SEND\" /></form></body></html>"};

const char statusOK[] = {"HTTP/1.1 200 OK\r\nConnection: Keep-Alive\r\nContent-Type: text/html"};
const char statusOK_CL0[] = {"HTTP/1.1 200 OK\r\nConnection: Keep-Alive\r\nContent-Type: text/html\r\nContent-Length: 0"};

const char statusNOTFOUND[] = {"HTTP/1.1 404 Not Found\r\n"};

void PICKER()
{
	char hex[7] = {0x00, 0x00, 0x00}, ContentLength[22];

	ESP_SendConstData(statusOK, strlen(statusOK), 1);

	int length = strlen(htmlpicker1) + strlen(htmlpicker2) + 6;
	sprintf(ContentLength, "Content-Length: %04d\r\n", length);
	ESP_SendData(ContentLength, 22, 1);

	sprintf(hex, "%02x%02x%02x", Led_Get_Color(eRed)*255/4095, Led_Get_Color(eGreen)*255/4095, Led_Get_Color(eBlue)*255/4095);

	ESP_SendConstData(htmlpicker1, strlen(htmlpicker1), 0);
	ESP_SendData(hex, 6, 0);
	ESP_SendConstData(htmlpicker2, strlen(htmlpicker2), 1);
}

void PickerParseLed()
{
	char * search;
	search = strstr(ESP_GetAnswer(), "?picker=%");
	if(search != NULL)
	{
		char hex[2];
		uint16_t colors[3] = {0, 0, 0};
		for(int i = 0, l = 0; i < 6; i += 2, l++)
		{
			int position = search - ESP_GetAnswer() + 11 + i;
			hex[0] = ESP_GetAnswer()[position];
			hex[1] = ESP_GetAnswer()[position + 1];
			colors[l] = strtol(hex, NULL, 16);
		}
		Led_Set(colors[0]*4095/255, colors[1]*4095/255, colors[2]*4095/255);
	}
}

void PICKER_parse()
{
	PickerParseLed();

	PICKER();
}

uint8_t requestConstFind(const char * key)
{
	if(strstr(ESP_GetAnswer(), key) != NULL)
	{
		return 1;
	}
	return 0;
}


void ESP_Request(const char ** pages, const foo * functions, uint8_t number)
{
	uint8_t linkID = requestRefresh();
	SetLinkID(linkID);

	if(linkID >= 0 && linkID < 5)
	{
		for(int i = 0; i < number; i++)
		{
			if(pages != NULL
		       && functions != NULL
		       && requestConstFind(pages[i]))
			{
				functions[i]();
				return;
			}
		}
		ESP_SendConstData(statusNOTFOUND, strlen(statusNOTFOUND), 1);
	}
	else return;
}
