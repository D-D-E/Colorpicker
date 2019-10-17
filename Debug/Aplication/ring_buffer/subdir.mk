################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Aplication/ring_buffer/ring_buffer.c 

OBJS += \
./Aplication/ring_buffer/ring_buffer.o 

C_DEPS += \
./Aplication/ring_buffer/ring_buffer.d 


# Each subdirectory must supply rules for building sources it contributes
Aplication/ring_buffer/%.o: ../Aplication/ring_buffer/%.c
	arm-atollic-eabi-gcc -c "$<" -mthumb -mcpu=cortex-m3 -std=gnu11 -DUSE_FULL_LL_DRIVER -D__weak=__attribute__((weak)) -D__packed=__attribute__((__packed__)) -DUSE_HAL_DRIVER -DSTM32F103xB -I../Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Aplication/encoder -I../Aplication/ESP8266 -I../Aplication/ldr -I../Aplication/led -I../Aplication/request -I../Aplication/ring_buffer -I../Platform/encoder_driver -I../Platform/ldr_driver -I../Platform/led_driver -I../Platform/status_led -I../Platform/usart -I../Platform/ldr_queue -I../Platform/encoder_queue -I../Platform/led_task -I../Platform/ldr_task -I../Platform/esp_task -I../Platform/encoder_task -I../Platform/delay -Os -ffunction-sections -fdata-sections -g -fstack-usage -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -specs=nano.specs -o "$@"

