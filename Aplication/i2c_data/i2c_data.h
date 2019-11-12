#ifndef I2C_DATA_I2C_DATA_H_
#define I2C_DATA_I2C_DATA_H_
#include "stdint.h"

void I2C_Init();
void ColorToEEPROM();
void ColorFromEEPROM();

void WifiToEEPROM();
void WifiFromEEPROM(uint8_t * ssid, uint8_t * paswd);

#endif /* I2C_DATA_I2C_DATA_H_ */
