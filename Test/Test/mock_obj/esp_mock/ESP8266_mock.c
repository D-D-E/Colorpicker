#include "ESP8266.h"
#include "ring_buffer.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"
#include "delay.h"
#include "uart.h"

char request[1025];
char answer[1025];

char ssid[32], paswd[32];
char ip[15];

uint8_t linkID;
uint8_t TCPServerFlag = 0;

static bool waitCallBack(char * aim, uint16_t ms)
{
    uint32_t time_end = getSysTick() + ms;
    uint32_t time = getSysTick();
    while(time_end > time)
    {
        time++;
        if(charCallBack(aim))
        {
            return 1;
        }
        else asm("NOP");

        delay(1);
    }
    return 0;
}

void ESPInit()
{
     MX_USART1_UART_Init();
     RingBuff_Init();
}

void ESP_Resset()
{
    USART1_Device_Reset();
    if(waitCallBack("ready", 2000))
    {
        return;
    }
}

static void requestFlush()
{
    memset(request, 0, sizeof(request));
    //request[1023] = 0;
}

static void answerFlush()
{
    memset(answer, 0, sizeof(answer));
    //answer[1023] = 0;
}

uint8_t ESP_SetMode(int mode)
{
    requestFlush();

    if(mode == 1 || mode == 3)
    {
        USART_SendData("AT+SLEEP=0\r\n", 12);
    }

    sprintf(request, "AT+CWMODE=%d\r\n", mode);
    RingBuff_Clear();
    USART_SendData(request, strlen(request));

    if(waitCallBack("OK", 20))
    {
        USART_SendData("AT+RST\r\n", 8); //restart to apply settings
        //delay(1000);

        if(waitCallBack("ready", 2000))
        {
            return 1;
        }
        else asm("NOP");
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

uint8_t ESP_SetModeBoth()
{
    return ESP_SetMode(3);
}

void ESP_CloseConnection(uint8_t id)
{
    requestFlush();
    sprintf(request, "AT+CIPCLOSEMODE=%u,1", id);
    RingBuff_Clear();
    USART_SendData(request, strlen(request));
}

uint8_t ESP_SetParamsSoftAP(char * ssid, char * password)
{
    if(ssid != NULL && password != NULL)
    {
        requestFlush();
        sprintf(request, "AT+CWSAP=\"%s\",\"%s\",5,3\r\n", ssid, password);
        RingBuff_Clear();
        USART_SendData(request, strlen(request));

        if(waitCallBack("OK", 20))
        {
            USART_SendData("AT+RST\r\n", 8); //restart to apply settings

            if(waitCallBack("ready", 2000))
            {
                return 1;
            }
            else asm("NOP");
        }
    }

    return 0;
}

uint8_t ESP_SetParamsStation(char * ssid, char * password)
{
    if(ssid != NULL && password != NULL)
    {
        requestFlush();
        sprintf(request, "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, password);
        RingBuff_Clear();
        //charCallBack("");   //clear ring buffer after restart
        USART_SendData(request, strlen(request));

        if(waitCallBack("OK", 10000))
        {
            return 1;
        }
    }

    return 0;
}

uint8_t ESP_SetParamsDNS(char * name)
{
    if(name != NULL)
    {
        requestFlush();
        sprintf(request, "AT+CIPDNS_CUR=1,\"%s\"\r\n", name);
        //sprintf(request, "AT+MDNS=1,\"%s\",\"iot\",8080\r\n", name);
        RingBuff_Clear();
        //charCallBack("");   //clear ring buffer after restart
        USART_SendData(request, strlen(request));

        if(waitCallBack("OK", 20))
        {
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
        if(!waitCallBack("OK", 100))
        {
            return 0;
        }

        requestFlush();
        sprintf(request, "AT+CIPSERVER=1,%d\r\n", port);

        RingBuff_Clear();
        USART_SendData(request, strlen(request));
        //USART_SendData("AT+MDNS=1,\"espressif\",\"iot\",80\r\n", 32);
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
        RingBuff_Clear();
        USART_SendData(request, strlen(request));
        TCPServerFlag = 0;

        if(waitCallBack("OK", 20))
        {
            return 1;
        }
    }
    return 0;
}

uint8_t requestRefresh()
{
    answerFlush();
    int i = 0;
    while(!(RingBuff_IsEmpty()) && i < 1024)
    {
        answer[i++] = RingBuff_Pop();
        delay(1);
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

uint16_t charCallBack(char * key)
{
    answerFlush();
    uint16_t i = 0;
    while(!(RingBuff_IsEmpty()) && i < 1024)
    {
        answer[i] = RingBuff_Pop();

        if(answer[i] == 0)
        {
            answer[i] = '0';
        }
        i++;
    }
    answer[1024] = 0;

    if(key != NULL && strlen(answer) >= strlen(key))
    {
        if(strstr(answer, key) != NULL)
        {
            return 1;
        }
    }

    return 0;
}

uint8_t charCallBackNoFlush(char * key, uint16_t bias)
{
    char * temp = (char *)answer + bias;
    if(key != NULL && strlen(temp) >= strlen(key))
    {
        if(strstr(temp, key) != NULL)
        {
            return 1;
        }
    }

    return 0;
}

uint8_t ESP_SendConstData(const char *data, uint16_t dataLength, uint8_t flagRN)
{
    requestFlush();
    sprintf(request, "AT+CIPSEND=%d,%d\r\n", linkID, flagRN ? (dataLength + 2) : dataLength);
    USART_SendData(request, strlen(request));
    //delay(200);

    if(waitCallBack(">", 200) && data != NULL)
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
//  if(waitCallBack("Recv", 200))
//  {
//      return 1;
//  }

    return 0;
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

void SetSSID(char * name)
{
    memcpy(ssid, name, 32);
}

char * GetSSID()
{
    return ssid;
}

void SetPASWD(char * passwd)
{
    memcpy(paswd, passwd, 32);
}

char *  GetPasw()
{
    return paswd;
}

void GetStationIP(void)
{
    char * search;
    requestFlush();
    sprintf(request, "AT+CIPSTA_CUR?\r\n");
    RingBuff_Clear();
    USART_SendData(request, strlen(request));

    uint16_t i = 0;
    while(!(RingBuff_IsEmpty()) && i < 1024)
    {
        answer[i] = RingBuff_Pop();
        if(answer[i] == 0)
        {
            answer[i] = '0';
        }
        i++;
    }
    search = strstr(answer, "ip:");
    if(search != NULL)
    {
        memcpy(ip, search + 4, 15);
    }
    //else memcpy(ip, "000.000.000.000", 15);
}

char * GetIP(void)
{
    return ip;
}
