#include <ESP8266.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char answer[512], send_data[512];

uint8_t ESP_SendData(char *data, uint16_t dataLength, uint8_t flagRN)
{
    for(int i = 0; i < dataLength; i++)
    {
        send_data[i] = data[i];
    }
    return 1;
}

uint8_t ESP_SendConstData(const char *data, uint16_t dataLength, uint8_t flagRN)
{
    for(int i = 0; i < dataLength; i++)
    {
        send_data[i] = data[i];
    }
    return 1;
}

uint8_t requestRefresh()
{
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

void SetLinkID(uint8_t ID){}

char * ESP_GetAnswer(void)
{
    return answer;
}

void SetAnswer(char * param, int size)
{
    for(int i = 0; i < size; i++)
    {
        answer[i] = param[i];
    }
}

char * GetSendESPData(void)
{
    return send_data;
}

void ClearSendESPData(void)
{
    memset(send_data, 0, 512);
}
