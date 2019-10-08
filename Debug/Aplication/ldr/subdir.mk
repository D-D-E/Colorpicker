################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Aplication/ldr/ldr.c 

OBJS += \
./Aplication/ldr/ldr.o 

C_DEPS += \
./Aplication/ldr/ldr.d 


# Each subdirectory must supply rules for building sources it contributes
Aplication/ldr/%.o: ../Aplication/ldr/%.c
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

