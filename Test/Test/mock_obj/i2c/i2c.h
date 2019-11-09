#ifndef I2C_I2C_H_
#define I2C_I2C_H_
#include "stdint.h"
#include "stdbool.h"

void MX_I2C2_Init(void);
bool I2C2_SendData(uint16_t addr, uint8_t * data, uint32_t data_length);
bool I2C2_ReadData(uint16_t addr, uint8_t * data, uint32_t data_length);

#endif /* I2C_I2C_H_ */
