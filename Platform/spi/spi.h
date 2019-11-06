#ifndef SPI_SPI_H_
#define SPI_SPI_H_
#include "stdint.h"

void MX_SPI1_Init(void);
void SPI1_SendData(uint8_t * data, uint32_t data_length);

#endif /* SPI_SPI_H_ */
