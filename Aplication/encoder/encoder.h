#ifndef ENCODER_ENCODER_H_
#define ENCODER_ENCODER_H_
#include "stdint.h"

typedef enum {eNone, eLeft, eRight, eButton}  eState;

void EncoderInit(void);
eState Encoder_State(void);

#endif /* ENCODER_ENCODER_H_ */
