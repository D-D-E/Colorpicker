#include "uart.h"
#include "ring_buffer.h"
#include <string.h>

char send_data[512];
int counter = 0;

void ClearSendData(void)
{
    memset(send_data, 0, 512);
    counter = 0;
}

void USART_SendData(char * data, uint32_t data_length)
{
    for(int i = 0; i < data_length; i++)
    {
        send_data[counter++] = data[i];
    }
}

void USART_SendData_byte(char data)
{
    if(counter < 512)
    {
        send_data[counter++] = data;
    }
}

void USART_CharReception_Callback(void){}
void Error_Callback(void){}
void USART1_IRQHandler(void){}
void MX_USART1_UART_Init(void){}
void USART1_Device_Reset(void){}


char * GetSendData(void)
{
    return send_data;
}

void SetReceiveData(char * data, uint16_t data_length)
{
    RingBuff_Clear();
    for(int i = 0; i < data_length; i++)
    {
        RingBuff_Push(data[i]);
    }
}

