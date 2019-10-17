#include "led_task.h"
#include "led.h"
#include "encoder_queue.h"
#include "ldr_queue.h"
#include "cmsis_os.h"

static uint16_t constrain(int32_t value)
{
	if(value > 4095) value = 4095;
	if(value < 0) value = 0;
	return value;
}

static void pxLed(void * arg)
{
	LedInit();

	uint16_t ldr_value = 4095;
	EncoderRotateInfo xEncoder_info;

	while(1)
	{
		if(EncoderQueue_IsElements())
		{
			xEncoder_info = EncoderQueue_Receive();
			int16_t red = Led_Get_Color(eRed), green = Led_Get_Color(eGreen), blue = Led_Get_Color(eBlue);

			switch(xEncoder_info.button)
			{
				case 0: break;
				case 1:
					{
						Led_Set_Color(eRed, constrain(red + xEncoder_info.state));
						break;
					}
				case 2:
					{
						Led_Set_Color(eGreen, constrain(green + xEncoder_info.state));
						break;
					}
				case 3:
					{
						Led_Set_Color(eBlue, constrain(blue + xEncoder_info.state));
						break;
					}
				case 4:
					{
						Led_Set(constrain(red + xEncoder_info.state), constrain(green + xEncoder_info.state), constrain(blue + xEncoder_info.state));
						break;
					}
				default: break;
			}
		}
		if(LDRQueue_IsElements())
		{
			 ldr_value = LDRQueue_Receive();
		}

		Led_Refresh(ldr_value);
		osDelay(10);
	}
}

void LedTaskInit(void)
{
	xTaskCreate(pxLed, "Led", configMINIMAL_STACK_SIZE, NULL, osPriorityNormal, NULL);
}
