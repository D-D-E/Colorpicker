################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
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


# All Target
all: rtos_usart_ll.elf secondary-outputs

# Tool invocations
rtos_usart_ll.elf: $(OBJS) $(USER_OBJS)
	arm-atollic-eabi-gcc -o "rtos_usart_ll.elf" $(OBJS) $(USER_OBJS) $(LIBS) -mthumb -mcpu=cortex-m3 -T"C:\Users\dashk\OneDrive\Documents\CubeMx\blink\rtos_usart_ll\STM32F103C8_FLASH.ld" -specs=nosys.specs -static "-Wl,-Map=rtos_usart_ll.map" -Wl,--gc-sections -Wl,--defsym=malloc_getpagesize_P=0x80 -Wl,--start-group -lc -lm -Wl,--end-group -specs=nano.specs
	$(MAKE) --no-print-directory post-build

EXECUTABLES: rtos_usart_ll.elf $(EXECUTABLES)
	"C:\Program Files (x86)\Atollic\TrueSTUDIO for STM32 9.3.0\ide\jre\bin\java" -jar "C:\Program Files (x86)\Atollic\TrueSTUDIO for STM32 9.3.0\Tools\arm-atollic-reports.jar" sizeinfo list rtos_usart_ll.elf

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(SECOUTPUTBUILDVAR)$(OBJS)$(C_DEPS) rtos_usart_ll.elf
	-@echo ' '

post-build:
	-arm-atollic-eabi-objcopy.exe -O ihex "rtos_usart_ll.elf" "rtos_usart_ll.hex"
	-@echo ' '

secondary-outputs: $(SECOUTPUTBUILDVAR)

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
