#include "uart.h"
#include "ring_buffer.h"
#include <string.h>

char send_data[512];

void USART_SendData(char * data, uint32_t data_length)
{
    memset(send_data, 0, 512);
    for(int i = 0; i < data_length; i++)
    {
        send_data[i] = data[i];
    }
}

void USART_SendData_byte(char data)
{
    memset(send_data, 0, 512);
    send_data[0] = data;
}

void USART_CharReception_Callback(void){}
void Error_Callback(void){}
void USART1_IRQHandler(void){}
void MX_USART1_UART_Init(void){}
void USART1_Reset(void){}


char * GetSendData(void)
{
    return send_data;
}

void SetReceiveData(char * data)
{
    RingBuff_Clear();
    for(int i = 0; i < strlen(data); i++)
    {
        RingBuff_Push(data[i]);
    }
}

