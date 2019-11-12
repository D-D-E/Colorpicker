#ifndef ENCODER_QUEUE_ENCODER_QUEUE_H_
#define ENCODER_QUEUE_ENCODER_QUEUE_H_
#include "stdint.h"
#include "stdbool.h"

typedef struct
{
	int16_t state;
	int8_t button;
}EncoderRotateInfo;

void EncoderQueueInit(void);

void EncoderQueue_Send(uint16_t value, uint8_t button);

void EncoderQueue_Receive(EncoderRotateInfo * value);
bool EncoderQueue_IsElements(void);

#endif /* ENCODER_QUEUE_ENCODER_QUEUE_H_ */
