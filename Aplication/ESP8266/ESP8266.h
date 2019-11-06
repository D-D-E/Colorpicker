#ifndef ESP8266_ESP8266_H_
#define ESP8266_ESP8266_H_
#include "stdint.h"

void ESPInit();
void ESP_Resset();

uint8_t ESP_SetModeStation();
uint8_t ESP_SetModeSoftAP();
uint8_t ESP_SetModeBoth();

uint8_t ESP_SetParamsSoftAP(char * ssid, char * password);
uint8_t ESP_SetParamsStation(char * ssid, char * password);
uint8_t ESP_SetParamsDNS(char * name);

uint8_t ESP_StartTCPServer(uint16_t port);
uint8_t ESP_StopTCPServer(uint16_t port);

void ESP_CloseConnection(uint8_t id);

uint8_t requestFind(char * key);
uint8_t requestRefresh();
uint16_t charCallBack(char * key);
uint8_t charCallBackNoFlush(char * key, uint16_t bias);
uint8_t ESP_SendConstData(const char *data, uint16_t dataLength, uint8_t flagRN);

void SetLinkID(uint8_t ID);
uint8_t GetLinkID(void);
char * ESP_GetAnswer(void);

void SetSSID(char * name);
char * GetSSID();
void SetPASWD(char * passwd);
char *  GetPasw();

#endif
