#include "i2c.h"
#include "delay.h"
#include "string.h"

uint8_t data_buff[4096];

void MX_I2C2_Init(void)
{
    memset(data_buff, 0, 4096);
}

bool I2C2_SendData(uint16_t addr, uint8_t * data, uint32_t data_length)
{
    for(int i = 0; i < data_length; i++)
    {
        data_buff[addr + i] = data[i];
    }
    return 1;
}

bool I2C2_ReadData(uint16_t addr, uint8_t * data, uint32_t data_length)
{
    for(int i = 0; i < data_length; i++)
    {
        data[i] = data_buff[addr + i];
    }
	return 1;
}
