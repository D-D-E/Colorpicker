#ifndef USART_UART_H_
#define USART_UART_H_
#include "stdint.h"


void USART_SendData(char * data, uint32_t data_length);
void USART_SendData_byte(char data);

void USART_CharReception_Callback(void);
void Error_Callback(void);
void USART1_IRQHandler(void);
void MX_USART1_UART_Init(void);
void USART1_Device_Reset(void);


char * GetSendData(void);
void SetReceiveData(char * data, uint16_t data_length);
void ClearSendData(void);

#endif /* USART_UART_H_ */
