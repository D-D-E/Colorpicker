#include "ring_buffer.h"

uint16_t index_in, index_out;
char buffer[BUF_SIZE]; // not __IO, mb not work with optimization

void RingBuff_Init()
{
	index_in = index_out = 0;
}

void RingBuff_Push(char element)
{
	buffer[index_in++] = element;
	index_in &= BUF_MASK;
}

char RingBuff_Pop()
{
	char element = buffer[index_out++];
	index_out &= BUF_MASK;
	return element;
}

uint8_t RingBuff_IsEmpty()
{
	if (index_in == index_out)
		return 1;
	return 0;
}

void RingBuff_Clear()
{
	index_out = index_in = 0;
}
