################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Aplication/led/led.c 

OBJS += \
./Aplication/led/led.o 

C_DEPS += \
./Aplication/led/led.d 


# Each subdirectory must supply rules for building sources it contributes
Aplication/led/%.o: ../Aplication/led/%.c
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

