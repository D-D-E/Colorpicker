################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Platform/encoder_queue/encoder_queue.c 

OBJS += \
./Platform/encoder_queue/encoder_queue.o 

C_DEPS += \
./Platform/encoder_queue/encoder_queue.d 


# Each subdirectory must supply rules for building sources it contributes
Platform/encoder_queue/%.o: ../Platform/encoder_queue/%.c
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

