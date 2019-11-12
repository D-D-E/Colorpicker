#include "encoder_queue.h"
#include "cmsis_os.h"

xQueueHandle encoder_queue;
EncoderRotateInfo xEncoder_info;

void EncoderQueueInit(void)
{
	encoder_queue = xQueueCreate( 2, sizeof(EncoderRotateInfo));
}

void EncoderQueue_Send(uint16_t value, uint8_t button)
{
	const portTickType xTicksToWait = 100 / portTICK_RATE_MS;
	xEncoder_info.button = button;
	xEncoder_info.state = value;
	xQueueSendToBack(encoder_queue, &xEncoder_info, xTicksToWait);
}

void EncoderQueue_Receive(EncoderRotateInfo * value)
{
	xQueueReceive(encoder_queue, &value, 100);
}

bool EncoderQueue_IsElements(void)
{
	if(uxQueueMessagesWaiting(encoder_queue) > 0)
	{
		return true;
	}
	return false;
}
