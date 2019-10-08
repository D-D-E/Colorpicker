#include "ESP8266.h"
#include "uart.h"
#include "delay.h"
#include "ring_buffer.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"

const char statusNOTFOUND[] = {"HTTP/1.1 404 Not Found\r\n"};

char request[512];
char answer[512];
uint8_t linkID;
uint8_t TCPServerFlag = 0;

void ESPInit()
{
	 MX_USART1_UART_Init();
}

void ESP_Resset()
{
	USART1_Reset();
}

static void requestFlush()
{
	memset(request, '0', 512);
}

static void answerFlush()
{
	memset(answer, '0', 512);
}

static bool waitCallBack(uint8_t ms)
{
	uint32_t time = get_sys_tick();
	while(time + ms > get_sys_tick())
	{
		if(charCallBack("OK"))
		{
			return 1;
		}
	}
	return 0;
}

uint8_t ESP_SetMode(int mode)
{
	requestFlush();
	sprintf(request, "AT+CWMODE=%d\r\n", mode);
	USART_SendData(request, strlen(request));

	if(waitCallBack(20))
	{
		USART_SendData("AT+RST\r\n", 8);
		delay(1000);

		return 1;
	}

	return 0;
}

uint8_t ESP_SetModeStation()
{
	return ESP_SetMode(1);
}

uint8_t ESP_SetModeSoftAP()
{
	return ESP_SetMode(2);
}

uint8_t ESP_SetParamsSoftAP(char * ssid, char * password)
{
	requestFlush();
	sprintf(request, "AT+CWSAP=\"%s\",\"%s\",5,3\r\n", ssid, password);
	charCallBack("");
	USART_SendData(request, strlen(request));

	if(waitCallBack(20))
	{
		USART_SendData("AT+RST\r\n", 8);
		delay(1000);
		return 1;
	}

	return 0;
}

uint8_t ESP_StartTCPServer(uint16_t port)
{
	USART_SendData("AT+CIPMUX=1\r\n", 13);
	delay(100);

	requestFlush();
	sprintf(request, "AT+CIPSERVER=1,%d\r\n", port);
	charCallBack("");
	USART_SendData(request, strlen(request));

	if(waitCallBack(20))
	{
		return 1;
	}

	return 0;
}

uint8_t ESP_StopTCPServer(uint16_t port)
{
	if(TCPServerFlag)
	{
		requestFlush();
		sprintf(request, "AT+CIPSERVER=0,%d\r\n", port);
		USART_SendData(request, strlen(request));

		if(waitCallBack(20))
		{
			return 1;
		}
	}

	return 1;
}

uint8_t requestRefresh()
{
	answerFlush();
	int i = 0;
	while(!(RingBuff_IsEmpty()) && i < 512)
	{
		answer[i++] = RingBuff_Pop();
	}

	char * search;
	search = strstr(answer, "+IPD,");
	if(search != NULL)
	{
		search+=5;
		uint8_t ID = strtol(search, NULL, 10);
		//search += 2;
		//answerLength = strtol(search, NULL, 10); // get answer length

		return ID;
	}
	return 100;
}

uint8_t requestFind(char * key)
{
	if(strstr(answer, key) != NULL)
	{
		return 1;
	}
	return 0;
}

uint8_t requestConstFind(const char * key)
{
	if(strstr(answer, key) != NULL)
	{
		return 1;
	}
	return 0;
}

char * ESP_GetRequest()
{
	return answer;
}

uint8_t charCallBack(char * key)
{
	answerFlush();
	uint16_t i = 0;
	while(!(RingBuff_IsEmpty()) && i < 512)
	{
		answer[i++] = RingBuff_Pop();
	}

	if(strlen(answer) >= strlen(key))
	{
		if(strstr(answer, key) != NULL)
		{
			return 1;
		}
	}

	return 0;
}

uint8_t ESP_SendData(char *data, uint16_t dataLength, uint8_t flagRN)
{
	if(flagRN)
	{
		dataLength += 2;
	}
	requestFlush();
	sprintf(request, "AT+CIPSEND=%d,%d\r\n", linkID, dataLength);
	USART_SendData(request, strlen(request));
	delay(200);

	if(flagRN)
	{
		dataLength -= 2;
	}

	if(charCallBack(">"))
	{
		for(int i = 0; i < dataLength; i++)
		{
			USART_SendData_byte(data[i]);
		}
		if(flagRN)
		{
			USART_SendData("\r\n", 2);
		}
	}
	else return 0;

	delay(100);

	return 1;
}

uint8_t ESP_SendConstData(const char *data, uint16_t dataLength, uint8_t flagRN)
{
	if(flagRN)
	{
		dataLength += 2;
	}
	requestFlush();
	sprintf(request, "AT+CIPSEND=%d,%d\r\n", linkID, dataLength);
	USART_SendData(request, strlen(request));
	delay(200);

	if(flagRN)
	{
		dataLength -= 2;
	}

	if(charCallBack(">"))
	{
		for(int i = 0; i < dataLength; i++)
		{
			USART_SendData_byte(data[i]);
		}
		if(flagRN)
		{
			USART_SendData("\r\n", 2);
		}
	}
	else return 0;
	delay(100);

	return 1;
}

void ESP_Request(const char ** pages, const foo * functions, uint8_t number)
{
	linkID = requestRefresh();
	if(linkID >= 0 && linkID < 5)
	{
		for(int i = 0; i < number; i++)
		{
			if(requestConstFind(pages[i]))
			{
				functions[i]();
				return;
			}
		}
		ESP_SendConstData(statusNOTFOUND, strlen(statusNOTFOUND), 1);
	}
}
