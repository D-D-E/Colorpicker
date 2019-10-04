#include "ldr_queue.h"
#include "cmsis_os.h"

xQueueHandle ldr_queue;

void LDRQueueInit(void)
{
	  ldr_queue = xQueueCreate(2, sizeof(uint16_t));
}

void LDRQueue_Send(uint16_t value)
{
	const portTickType xTicksToWait = 100 / portTICK_RATE_MS;
	xQueueSendToBack(ldr_queue, &value, xTicksToWait);
}

uint16_t LDRQueue_Receive(void)
{
	uint16_t value;
	xQueueReceive(ldr_queue, &value, 0);
	return value;
}

bool LDRQueue_IsElements(void)
{
	if(uxQueueMessagesWaiting(ldr_queue) > 0)
	{
		return true;
	}
	return false;
}
