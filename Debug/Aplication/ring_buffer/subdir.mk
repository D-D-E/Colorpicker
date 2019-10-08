################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Aplication/ring_buffer/ring_buffer.c 

OBJS += \
./Aplication/ring_buffer/ring_buffer.o 

C_DEPS += \
./Aplication/ring_buffer/ring_buffer.d 


# Each subdirectory must supply rules for building sources it contributes
Aplication/ring_buffer/%.o: ../Aplication/ring_buffer/%.c
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

