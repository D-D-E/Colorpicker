################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Platform/status_led/status_led.c 

OBJS += \
./Platform/status_led/status_led.o 

C_DEPS += \
./Platform/status_led/status_led.d 


# Each subdirectory must supply rules for building sources it contributes
Platform/status_led/%.o: ../Platform/status_led/%.c
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

