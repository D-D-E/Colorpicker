################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Platform/ldr_task/ldr_task.c 

OBJS += \
./Platform/ldr_task/ldr_task.o 

C_DEPS += \
./Platform/ldr_task/ldr_task.d 


# Each subdirectory must supply rules for building sources it contributes
Platform/ldr_task/%.o: ../Platform/ldr_task/%.c
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

