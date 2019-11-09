#include "led_task.h"
#include "led.h"
#include "i2c_data.h"
#include "display.h"
#include "delay.h"
#include "encoder_queue.h"
#include "ldr_queue.h"
#include "ESP8266.h"
#include "cmsis_os.h"
#include <string.h>

static uint16_t constrain(int32_t value)
{
	if(value > 4096) value = 4096;
	if(value < 0) value = 0;
	return value;
}

static void pxLed(void * arg)
{
	LedInit();

	Display_ON();
	Display_Contrast(0xFF);
	display(); // refrash display

	uint16_t ldr_value = 4096, ldr_value_old = 4096;
	EncoderRotateInfo xEncoder_info;

	setLedI2C(); // load led from EEPROM

	while(1)
	{
		if(EncoderQueue_IsElements()) // get data from encoder
		{
			xEncoder_info = EncoderQueue_Receive();
			int16_t red = Led_Get_Color(eRed), green = Led_Get_Color(eGreen), blue = Led_Get_Color(eBlue);

			switch(xEncoder_info.button) // refresh led and display
			{
				case 0: break;
				case 1:
					{
						Led_Set_Color(eRed, constrain(red + xEncoder_info.state));
						display();
						break;
					}
				case 2:
					{
						Led_Set_Color(eGreen, constrain(green + xEncoder_info.state));
						display();
						break;
					}
				case 3:
					{
						Led_Set_Color(eBlue, constrain(blue + xEncoder_info.state));
						display();
						break;
					}
				case 4:
					{
						Led_Set(constrain(red + xEncoder_info.state), constrain(green + xEncoder_info.state), constrain(blue + xEncoder_info.state));
						display();
						break;
					}
				default: break;
			}
		}
		if(LDRQueue_IsElements())
		{
			 ldr_value = LDRQueue_Receive(); // get ldr value
		}

		while(!(ldr_value_old == ldr_value))
		{
			if(ldr_value_old > ldr_value)
			{
				Led_Refresh(ldr_value_old--);
			}
			else Led_Refresh(ldr_value_old++);

			osDelay(1);
		}
		ldr_value_old = ldr_value;

		static uint16_t update_display = 1000;
		if(update_display == 0)
		{
			GetStationIP();
			update_display = 1000;
			display();
		}
		else update_display--;

		osDelay(10);
	}
}

void LedTaskInit(void)
{
	xTaskCreate(pxLed, "Led", configMINIMAL_STACK_SIZE, NULL, osPriorityNormal, NULL);
	I2C_Init();
}
