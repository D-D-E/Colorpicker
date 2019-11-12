#include "crc.h"

void MX_CRC_Init(void)
{

}

uint32_t CRC_calc(uint32_t * data, uint32_t data_length)
{
    uint32_t res = 0;
    for(int i = 0; i < data_length; i++)
    {
        res += data[i];
    }
    return res;
}
