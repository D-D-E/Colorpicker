################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Platform/encoder_task/encoder_task.c 

OBJS += \
./Platform/encoder_task/encoder_task.o 

C_DEPS += \
./Platform/encoder_task/encoder_task.d 


# Each subdirectory must supply rules for building sources it contributes
Platform/encoder_task/%.o: ../Platform/encoder_task/%.c
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

