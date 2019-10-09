################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include cmocka/subdir.mk
-include Test/request_test/subdir.mk
-include Test/mock_obj/usart/subdir.mk
-include Test/mock_obj/led_driver/subdir.mk
-include Test/mock_obj/ldr_driver/subdir.mk
-include Test/mock_obj/esp_mock/subdir.mk
-include Test/mock_obj/encoder_driver/subdir.mk
-include Test/mock_obj/delay/subdir.mk
-include Aplication/ring_buffer/subdir.mk
-include Aplication/request/subdir.mk
-include Aplication/led/subdir.mk
-include Aplication/ldr/subdir.mk
-include Aplication/encoder/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Test.exe

# Tool invocations
Test.exe: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MinGW C Linker'
	gcc -ftest-coverage -fprofile-arcs -o "Test.exe" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) Test.exe
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
