################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Platform/usart/uart.c 

OBJS += \
./Platform/usart/uart.o 

C_DEPS += \
./Platform/usart/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Platform/usart/%.o: ../Platform/usart/%.c
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

