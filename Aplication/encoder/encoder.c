#include "encoder.h"
#include "stdbool.h"
#include "stdint.h"
#include "encoder_driver.h"

void EncoderInit(void)
{
	GPIO_Init();
}

eState Encoder_State(void)
{
	eState res = eNone;
    if(GetButton())
    {
      res = eButton;
      ClearButton();
      return res;
    }
    if(GetRotateStatus())
    {
		if(GetRotatePinA() == GetRotatePinB())
		{
			res = eRight;
		}
		else
		{
			res = eLeft;
		}
	}
	ClearRotateStatus();
    return res;
}

