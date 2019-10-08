################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Platform/led_task/led_task.c 

OBJS += \
./Platform/led_task/led_task.o 

C_DEPS += \
./Platform/led_task/led_task.d 


# Each subdirectory must supply rules for building sources it contributes
Platform/led_task/%.o: ../Platform/led_task/%.c
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

