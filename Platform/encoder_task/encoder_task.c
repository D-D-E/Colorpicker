#include "encoder_task.h"
#include "encoder_queue.h"
#include "encoder.h"
#include "cmsis_os.h"

static void pxEncoder(void * arg)
{
	EncoderInit();
	static uint8_t encoder_button_step = 0;

	while(1)
	{
		switch(Encoder_State())
		{
			case eNone: break;
			case eButton:
			{
				encoder_button_step++;
				if(encoder_button_step > 4)
				{
					encoder_button_step = 0;
				}
				break;
			}
			case eLeft:
			{
				EncoderQueue_Send(-100, encoder_button_step);
				break;
			}
			case eRight:
			{
				EncoderQueue_Send(100, encoder_button_step);
				break;
			}
			default: break;
		}
		osDelay(5);
	}
}

void EncoderTaskInit(void)
{
	xTaskCreate(pxEncoder, "Encoder", configMINIMAL_STACK_SIZE, NULL, osPriorityNormal, NULL);
}
