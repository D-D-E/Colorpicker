################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Aplication_test/Foo.c 

OBJS += \
./Aplication_test/Foo.o 

C_DEPS += \
./Aplication_test/Foo.d 


# Each subdirectory must supply rules for building sources it contributes
Aplication_test/%.o: ../Aplication_test/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -I"C:\Users\dashk\OneDrive\Documents\CubeMx\blink\rtos_usart_ll\Test\Aplication_test" -I"C:\Users\dashk\OneDrive\Documents\CubeMx\blink\rtos_usart_ll\Test\Test" -I"C:\Users\dashk\OneDrive\Documents\CubeMx\blink\rtos_usart_ll\Test\cmocka" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


