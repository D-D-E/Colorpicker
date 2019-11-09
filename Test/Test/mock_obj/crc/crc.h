#ifndef CRC_CRC_H_
#define CRC_CRC_H_
#include "stdint.h"

void MX_CRC_Init(void);
uint32_t CRC_calc(uint32_t * data, uint32_t data_length);

#endif /* CRC_CRC_H_ */
