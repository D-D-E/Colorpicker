#ifndef MOCK_OBJ_ESP_MOCK_ESP8266_H_
#define MOCK_OBJ_ESP_MOCK_ESP8266_H_
#include "stdint.h"

uint8_t ESP_SendData(char *data, uint16_t dataLength, uint8_t flagRN);
uint8_t ESP_SendConstData(const char *data, uint16_t dataLength, uint8_t flagRN);

uint8_t requestRefresh();
void SetLinkID(uint8_t ID);

char * ESP_GetAnswer(void);
void SetAnswer(char * param, int size);

char * GetSendESPData(void);
void ClearSendESPData(void);

#endif /* MOCK_OBJ_ESP_MOCK_ESP8266_H_ */
