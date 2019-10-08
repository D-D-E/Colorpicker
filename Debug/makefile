################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Test/led_test/cmocka/subdir.mk
-include Test/led_test/Test/mock_obj/usart/subdir.mk
-include Test/led_test/Test/mock_obj/led_driver/subdir.mk
-include Test/led_test/Test/mock_obj/ldr_driver/subdir.mk
-include Test/led_test/Test/mock_obj/encoder_driver/subdir.mk
-include Test/led_test/Test/led_test/subdir.mk
-include Test/led_test/Test/ldr_test/subdir.mk
-include Test/led_test/Aplication/ring_buffer/subdir.mk
-include Test/led_test/Aplication/request/subdir.mk
-include Test/led_test/Aplication/led/subdir.mk
-include Test/led_test/Aplication/ldr/subdir.mk
-include Test/led_test/Aplication/encoder/subdir.mk
-include Test/led_test/Aplication/ESP8266/subdir.mk
-include Test/ldr_test/cmocka/subdir.mk
-include Test/ldr_test/Test/mock_obj/usart/subdir.mk
-include Test/ldr_test/Test/mock_obj/led_driver/subdir.mk
-include Test/ldr_test/Test/mock_obj/ldr_driver/subdir.mk
-include Test/ldr_test/Test/mock_obj/encoder_driver/subdir.mk
-include Test/ldr_test/Test/led_test/subdir.mk
-include Test/ldr_test/Test/ldr_test/subdir.mk
-include Test/ldr_test/Aplication/ring_buffer/subdir.mk
-include Test/ldr_test/Aplication/request/subdir.mk
-include Test/ldr_test/Aplication/led/subdir.mk
-include Test/ldr_test/Aplication/ldr/subdir.mk
-include Test/ldr_test/Aplication/encoder/subdir.mk
-include Test/ldr_test/Aplication/ESP8266/subdir.mk
-include Test/cmocka/subdir.mk
-include Test/Test/mock_obj/usart/subdir.mk
-include Test/Test/mock_obj/led_driver/subdir.mk
-include Test/Test/mock_obj/ldr_driver/subdir.mk
-include Test/Test/mock_obj/encoder_driver/subdir.mk
-include Test/Test/led_test/subdir.mk
-include Test/Test/ldr_test/subdir.mk
-include Test/Debug/cmocka/subdir.mk
-include Test/Debug/Test/mock_obj/usart/subdir.mk
-include Test/Debug/Test/mock_obj/led_driver/subdir.mk
-include Test/Debug/Test/mock_obj/ldr_driver/subdir.mk
-include Test/Debug/Test/mock_obj/encoder_driver/subdir.mk
-include Test/Debug/Test/led_test/subdir.mk
-include Test/Debug/Test/ldr_test/subdir.mk
-include Test/Debug/Test/subdir.mk
-include Test/Debug/Aplication_test/subdir.mk
-include Test/Debug/Aplication/ring_buffer/subdir.mk
-include Test/Debug/Aplication/request/subdir.mk
-include Test/Debug/Aplication/led/subdir.mk
-include Test/Debug/Aplication/ldr/subdir.mk
-include Test/Debug/Aplication/encoder/subdir.mk
-include Test/Debug/Aplication/ESP8266/subdir.mk
-include Src/subdir.mk
-include Platform/usart/subdir.mk
-include Platform/status_led/subdir.mk
-include Platform/led_task/subdir.mk
-include Platform/led_driver/subdir.mk
-include Platform/ldr_task/subdir.mk
-include Platform/ldr_queue/subdir.mk
-include Platform/ldr_driver/subdir.mk
-include Platform/esp_task/subdir.mk
-include Platform/encoder_task/subdir.mk
-include Platform/encoder_queue/subdir.mk
-include Platform/encoder_driver/subdir.mk
-include Platform/delay/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Aplication/ring_buffer/subdir.mk
-include Aplication/request/subdir.mk
-include Aplication/led/subdir.mk
-include Aplication/ldr/subdir.mk
-include Aplication/encoder/subdir.mk
-include Aplication/ESP8266/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECOUTPUTBUILDVAR += \
EXECUTABLES \

EXECUTABLES += \
USER_OBJS \


# All Target
all: rtos_usart_ll.elf

# Tool invocations
	@echo 'No tool found that can build the extension specified with the build artifact name $@'
EXECUTABLES: rtos_usart_ll.elf $(EXECUTABLES)
	"C:\Program Files (x86)\Atollic\TrueSTUDIO for STM32 9.3.0\ide\jre\bin\java" -jar "C:\Program Files (x86)\Atollic\TrueSTUDIO for STM32 9.3.0\Tools\arm-atollic-reports.jar" sizeinfo list rtos_usart_ll.elf

USER_OBJS: $(OBJS) $(USER_OBJS)
	gcc  -o "USER_OBJS" $(OBJS) $(USER_OBJS) $(LIBS)

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(SECOUTPUTBUILDVAR)$(OBJS)$(C_DEPS) rtos_usart_ll.elf
	-@echo ' '

post-build:
	-arm-atollic-eabi-objcopy.exe -O ihex "rtos_usart_ll.elf" "rtos_usart_ll.hex"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
