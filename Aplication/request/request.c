#include "request.h"
#include "led.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "ring_buffer.h"
#include "ESP8266.h"
#include "i2c_data.h"
#include "display.h"

const char *PAGES[] = {"GET /PICKER ", "POST /PICKER", "GET /CONFIG ", "POST /CONFIG "};
const function_pointer FUNCTIONS[] = {PICKER, PICKER_parse, CONFIG, CONFIG_parse};

const char htmlpicker1[] = {"<html><head><title>ESP8266</title></head><body><script>let flag = true;function setFlag(){flag = false;};function reload(){if(flag){window.location = window.location.href;}};setTimeout(reload, 5000);</script><p>Choose your color:</p><form enctype=\"text/plain\" method=\"post\"><input type=\"color\" value=\"#"};
const char htmlpicker2[] = {"\" id=\"cp\" onclick=\"setFlag()\" name=\"picker\" /><input type=\"submit\" value=\"SEND\" /></form></body></html>"};

const char htmlconfig[] = {"<html><head><title>ESP8266_config</title></head><body><script>function getp(){var p = document.getElementById(\"ssid\").value;p=p.replace(\" \",\"?\");document.getElementById(\"ssid\").value=p;console.log(p);};</script><p>Set params:</p><form method=\"post\"><table width=\"100%\" cellspacing=\"0\" cellpadding=\"4\"><tr><td align=\"right\" width=\"60\">SSID:</td><td><input type=\"text\" required id=\"ssid\" maxlength=\"32\" name=\"ssid\"/></td></tr><tr><td align=\"right\" width=\"60\">Password:</td><td><input type=\"text\" id=\"paswd\" maxlength=\"32\" name=\"paswd\"/></td></tr><tr><td align=\"right\" width=\"60\"></td><td><input type=\"hidden\" id=\"dns\" name=\"dns\"/></td></tr></table><p><input type=\"submit\" id=\"sb\" onclick=\"getp()\" value=\"SEND\"/></p></form></body></html>"};

const char statusOK[] = {"HTTP/1.1 200 OK\r\nConnection: Keep-Alive\r\nContent-Type: text/html"};
const char statusOK_CL0[] = {"HTTP/1.1 200 OK\r\nConnection: Keep-Alive\r\nContent-Type: text/html\r\nContent-Length: 0"};

const char statusNOTFOUND[] = {"HTTP/1.1 404 Not Found"};

void CONFIG()
{
	char ContentLength[23];
	ESP_SendConstData(statusOK, strlen(statusOK), 1);

	int length = strlen(htmlconfig);
	sprintf(ContentLength, "Content-Length: %04d\r\n", length);
	ESP_SendConstData(ContentLength, 22, 1);
	ESP_SendConstData(htmlconfig, strlen(htmlconfig), 1);
}

void CONFIG_parse()
{
	char * search;
	char ssid_temp[32], paswd_temp[32];
	memset(ssid_temp, 0, 32);
	memset(paswd_temp, 0, 32);

	search = strstr(ESP_GetAnswer(), "ssid=");
	if(search != NULL)
	{
		search += 5;
		for(int i = 0, l = 0; i < 32; i++, l++)
		{
			if(search[i] == '&')
			{
				break;
			}
			if(search[i] == '%' && search[i+1] == '3' && search[i+2] == 'F') // search space code and replace by space
			{
				i += 2;
				search[i] = ' ';
			}

			ssid_temp[l] = search[i];
		}
	}
	SetSSID(ssid_temp);

	search = strstr(ESP_GetAnswer(), "paswd=");
	if(search != NULL)
	{
		search += 6;
		for(int i = 0; i < 32; i++)
		{
			if(search[i] == '&')
			{
				break;
			}
			paswd_temp[i] = search[i];
		}

		SetPASWD(paswd_temp);
	}
	CONFIG();
	//ESP_SendConstData(statusOK_CL0, strlen(statusOK_CL0), 1);
}

void PICKER()
{
	char hex[7], ContentLength[23];
	hex[6] = 0;

	ESP_SendConstData(statusOK, strlen(statusOK), 1);

	int length = strlen(htmlpicker1) + strlen(htmlpicker2) + 6;
	sprintf(ContentLength, "Content-Length: %04d\r\n", length);
	ESP_SendConstData(ContentLength, 22, 1);

	sprintf(hex, "%02x%02x%02x", Led_Get_Color(eRed)*255/4096, Led_Get_Color(eGreen)*255/4096, Led_Get_Color(eBlue)*255/4096);

	ESP_SendConstData(htmlpicker1, strlen(htmlpicker1), 0);
	ESP_SendConstData(hex, 6, 0);
	ESP_SendConstData(htmlpicker2, strlen(htmlpicker2), 1);
}

void PickerParseLed()
{
	char * search;
	search = strstr(ESP_GetAnswer(), "picker=#");
	if(search != NULL)
	{
		char hex[3];
		hex[2] = 0;
		uint16_t colors[3] = {0, 0, 0};
		for(int i = 0, l = 0; i < 6; i += 2, l++)
		{
			int position = search - ESP_GetAnswer() + 8 + i;
			hex[0] = ESP_GetAnswer()[position];
			hex[1] = ESP_GetAnswer()[position + 1];
			colors[l] = strtol(hex, NULL, 16);
		}
		Led_Set(colors[0]*4096/255, colors[1]*4096/255, colors[2]*4096/255);
	}
}

void PICKER_parse()
{
	PickerParseLed();
	//ColorToEEPROM();
	display();
	PICKER();
}

uint8_t requestConstFind(const char * key)
{
	if(strstr(ESP_GetAnswer(), key) != NULL)
	{
		return 1;
	}
	else asm("NOP");
	return 0;
}


void ESP_Request(const char ** pages, const function_pointer * functions, uint8_t number)
{
	uint8_t linkID = requestRefresh(); //parse request for id, URL, post data
	SetLinkID(linkID);

	if(linkID >= 0 && linkID < 5)
	{
		if(pages != NULL
	       && functions != NULL)
		{
			for(int i = 0; i < number; i++)
			{
				if(requestConstFind(pages[i]))
				{
					functions[i]();
					RingBuff_Clear();
					return;
				}
			}
		}
		ESP_SendConstData(statusNOTFOUND, strlen(statusNOTFOUND), 1);
		ESP_SendConstData(statusOK_CL0, strlen(statusOK_CL0), 1);
	}
}
