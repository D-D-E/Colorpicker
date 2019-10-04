#ifndef RING_BUFFER_RING_BUFFER_H_
#define RING_BUFFER_RING_BUFFER_H_
#include "stdint.h"

#define BUF_SIZE 512
#define BUF_MASK (BUF_SIZE-1)

extern char buffer[BUF_SIZE];

void RingBuff_Init();

void RingBuff_Push(char element);
char RingBuff_Pop();

uint8_t RingBuff_IsEmpty();
void RingBuff_Clear();


#endif
