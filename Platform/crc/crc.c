#include "crc.h"
#include "main.h"

void MX_CRC_Init(void)
{
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_CRC);
}

uint32_t CRC_calc(uint32_t * data, uint32_t data_length)
{
	LL_CRC_ResetCRCCalculationUnit(CRC);

	for(uint32_t i = 0; i < data_length; i++)
	{
		LL_CRC_FeedData32(CRC, __REV(data[i]));
	}

	return __REV(LL_CRC_ReadData32(CRC))^0xFFFFFFFF;
}
