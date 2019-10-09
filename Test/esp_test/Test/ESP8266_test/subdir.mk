################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Test/ESP8266_test/ESP8266_test.c 

OBJS += \
./Test/ESP8266_test/ESP8266_test.o 

C_DEPS += \
./Test/ESP8266_test/ESP8266_test.d 


# Each subdirectory must supply rules for building sources it contributes
Test/ESP8266_test/%.o: ../Test/ESP8266_test/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"C:\Users\dashk\OneDrive\Documents\CubeMx\blink\rtos_usart_ll\Test\Test" -I"C:\Users\dashk\OneDrive\Documents\CubeMx\blink\rtos_usart_ll\Test\cmocka" -I"C:\Users\dashk\OneDrive\Documents\CubeMx\blink\rtos_usart_ll\Test\Test\ldr_test" -I"C:\Users\dashk\OneDrive\Documents\CubeMx\blink\rtos_usart_ll\Test\Test\mock_obj\ldr_driver" -I"C:\Users\dashk\OneDrive\Documents\CubeMx\blink\rtos_usart_ll\Aplication\ldr" -I"C:\Users\dashk\OneDrive\Documents\CubeMx\blink\rtos_usart_ll\Test\Test\mock_obj\encoder_driver" -I"C:\Users\dashk\OneDrive\Documents\CubeMx\blink\rtos_usart_ll\Test\Test\mock_obj\led_driver" -I"C:\Users\dashk\OneDrive\Documents\CubeMx\blink\rtos_usart_ll\Test\Test\mock_obj\status_led" -I"C:\Users\dashk\OneDrive\Documents\CubeMx\blink\rtos_usart_ll\Test\Test\mock_obj\usart" -I"C:\Users\dashk\OneDrive\Documents\CubeMx\blink\rtos_usart_ll\Aplication\ESP8266" -I"C:\Users\dashk\OneDrive\Documents\CubeMx\blink\rtos_usart_ll\Aplication\encoder" -I"C:\Users\dashk\OneDrive\Documents\CubeMx\blink\rtos_usart_ll\Aplication\led" -I"C:\Users\dashk\OneDrive\Documents\CubeMx\blink\rtos_usart_ll\Aplication\request" -I"C:\Users\dashk\OneDrive\Documents\CubeMx\blink\rtos_usart_ll\Aplication\ring_buffer" -I"C:\Users\dashk\OneDrive\Documents\CubeMx\blink\rtos_usart_ll\Test\Test\mock_obj\delay" -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


