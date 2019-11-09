#ifndef SPI_SPI_H_
#define SPI_SPI_H_
#include "stdint.h"

void MX_SPI1_Init(void);
void SPI1_SendData(uint8_t * data, uint32_t data_length);
void SPI1_SendByte(uint8_t data);
void SetDC(void);
void ClearDC(void);
void Reset(void);

#endif /* SPI_SPI_H_ */
