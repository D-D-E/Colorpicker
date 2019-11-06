/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "ldr_queue.h"
#include "encoder_queue.h"
#include "led_task.h"
#include "ldr_task.h"
#include "esp_task.h"
#include "encoder_task.h"

osThreadId defaultTaskHandle;

void StartDefaultTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */

//#pragma GCC push_options
//#pragma GCC optimize ("O0") //__attribute__((optimize("O0")))
//void TakeStackSize()
//{
//	//UBaseType_t uxHighWaterMarkIdle = uxTaskGetStackHighWaterMark( xTaskGetIdleTaskHandle() );
//	UBaseType_t uxHighWaterMarkESP = uxTaskGetStackHighWaterMark(  xTaskGetHandle("ESP")  );
//	UBaseType_t uxHighWaterMarkLed = uxTaskGetStackHighWaterMark( xTaskGetHandle("Led") );
//	UBaseType_t uxHighWaterMarkLDR = uxTaskGetStackHighWaterMark(  xTaskGetHandle("LDR") );
//	UBaseType_t uxHighWaterMarkEncoder = uxTaskGetStackHighWaterMark( xTaskGetHandle("Encoder") );
//
//	int free_heap = xPortGetFreeHeapSize();
//}
//#pragma GCC pop_options

void __attribute__((optimize("O0"))) MX_FREERTOS_Init(void) {

  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 256);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  EncoderQueueInit();
  LDRQueueInit();

  LedTaskInit();
  LDRTaskInit();
  EncoderTaskInit();
  ESPTaskInit();
}

void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
