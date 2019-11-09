#include "i2c.h"
#include "delay.h"

#define I2C_REQUEST_WRITE                       0x00
#define I2C_REQUEST_READ                        0x01
#define SLAVE_OWN_ADDRESS                       0xA0
#define TIMEOUT									100

void MX_I2C2_Init(void)
{

}

bool I2C2_SendData(uint16_t addr, uint8_t * data, uint32_t data_length)
{
    return 1;
}

bool I2C2_ReadData(uint16_t addr, uint8_t * data, uint32_t data_length)
{

	return 1;
}
