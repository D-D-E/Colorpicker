#include "ESP8266.h"
#include "ring_buffer.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"
#include "delay.h"
#include "uart.h"

char request[512];
char answer[512];
uint8_t linkID;
uint8_t TCPServerFlag = 0;

void ESPInit()
{
     MX_USART1_UART_Init();
     RingBuff_Init();
}

void ESP_Resset()
{
    USART1_Device_Reset();
}

static void requestFlush()
{
    memset(request, '0', 512);
}

static void answerFlush()
{
    memset(answer, '0', 512);
}

static bool waitCallBack(char * aim, uint8_t ms)
{
    uint32_t time = get_sys_tick();
    while(time + ms > get_sys_tick())
    {
        if(charCallBack(aim))
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
    //RingBuff_Clear();
    USART_SendData(request, strlen(request));

    if(waitCallBack("OK", 20))
    {
        USART_SendData("AT+RST\r\n", 8); //restart to apply settings
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
    if(ssid != NULL && password != NULL)
    {
        requestFlush();
        sprintf(request, "AT+CWSAP=\"%s\",\"%s\",5,3\r\n", ssid, password);
        //RingBuff_Clear();
        //charCallBack("");   //clear ring buffer after restart
        USART_SendData(request, strlen(request));

        if(waitCallBack("OK", 20))
        {
            USART_SendData("AT+RST\r\n", 8); //restart to apply settings
            delay(1000);
            return 1;
        }
    }

    return 0;
}

uint8_t ESP_StartTCPServer(uint16_t port)
{
    if(!TCPServerFlag)
    {
        USART_SendData("AT+CIPMUX=1\r\n", 13);
        delay(100);

        requestFlush();
        sprintf(request, "AT+CIPSERVER=1,%d\r\n", port);
        //RingBuff_Clear();
        //charCallBack("");   //clear ring buffer after restart
        USART_SendData(request, strlen(request));

        if(waitCallBack("OK", 20))
        {
            TCPServerFlag = 1;
            return 1;
        }
    }

    return 0;
}

uint8_t ESP_StopTCPServer(uint16_t port)
{
    if(TCPServerFlag)
    {
        requestFlush();
        sprintf(request, "AT+CIPSERVER=0,%d\r\n", port);
        //RingBuff_Clear();
        USART_SendData(request, strlen(request));

        if(waitCallBack("OK", 20))
        {
            TCPServerFlag = 0;
            return 1;
        }
    }
    return 0;
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
        search += 5;
        uint8_t ID = strtol(search, NULL, 10);
        //search += 2;
        //answerLength = strtol(search, NULL, 10); // get answer length

        return ID;
    }
    return 100;
}

uint8_t charCallBack(char * key)
{
    answerFlush();
    uint16_t i = 0;
    while(!(RingBuff_IsEmpty()) && i < 512)
    {
        answer[i++] = RingBuff_Pop();
    }

    if(key != NULL && strlen(answer) >= strlen(key))
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
    requestFlush();
    sprintf(request, "AT+CIPSEND=%d,%d\r\n", linkID, flagRN ? dataLength + 2 : dataLength);
    USART_SendData(request, strlen(request));

    if(waitCallBack(">", 20) && data != NULL)
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
    requestFlush();
    sprintf(request, "AT+CIPSEND=%d,%d\r\n", linkID, flagRN ? dataLength + 2 : dataLength);
    USART_SendData(request, strlen(request));
    delay(200);

    if(waitCallBack(">", 20) && data != NULL)
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

void SetLinkID(uint8_t ID)
{
    linkID = ID;
}

uint8_t GetLinkID(void)
{
    return linkID;
}

char * ESP_GetAnswer(void)
{
    return answer;
}
