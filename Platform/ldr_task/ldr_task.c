#include "ldr_task.h"
#include "ldr.h"
#include "ldr_queue.h"
#include "cmsis_os.h"

static void pxLDR(void * arg)
{
	LDRInit();
	while(1)
	{
		uint16_t adc_value = LDR_Get();
		LDRQueue_Send(adc_value);
		osDelay(100);
	}
}

void LDRTaskInit(void)
{
	xTaskCreate(pxLDR, "LDR", configMINIMAL_STACK_SIZE, NULL, osPriorityNormal, NULL);
}
