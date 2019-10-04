#ifndef LDR_QUEUE_LDR_QUEUE_H_
#define LDR_QUEUE_LDR_QUEUE_H_
#include "stdint.h"
#include "stdbool.h"

void LDRQueueInit(void);

void LDRQueue_Send(uint16_t value);

uint16_t LDRQueue_Receive(void);
bool LDRQueue_IsElements(void);

#endif /* LDR_QUEUE_LDR_QUEUE_H_ */
