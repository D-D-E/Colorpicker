#ifndef ESP8266_ESP8266_H_
#define ESP8266_ESP8266_H_
#include "main.h"
#include "stdint.h"

typedef void (*foo)();


void ESPInit();
void ESP_Resset();

uint8_t ESP_SetModeStation();
uint8_t ESP_SetModeSoftAP();

uint8_t ESP_SetParamsSoftAP(char * ssid, char * password);

uint8_t ESP_StartTCPServer(uint16_t port);
uint8_t ESP_StopTCPServer(uint16_t port);

uint8_t requestFind(char * key);
uint8_t requestConstFind(const char * key);
uint8_t charCallBack(char * key);
uint8_t ESP_SendData(char *data, uint16_t dataLength, uint8_t flagRN);
uint8_t ESP_SendConstData(const char *data, uint16_t dataLength, uint8_t flagRN);
char * ESP_GetRequest();

void ESP_Request(const char ** pages, const foo * functions, uint8_t number);

#endif
