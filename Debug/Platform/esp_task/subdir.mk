################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Platform/esp_task/esp_task.c 

OBJS += \
./Platform/esp_task/esp_task.o 

C_DEPS += \
./Platform/esp_task/esp_task.d 


# Each subdirectory must supply rules for building sources it contributes
Platform/esp_task/%.o: ../Platform/esp_task/%.c
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

