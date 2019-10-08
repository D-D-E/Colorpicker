################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Platform/delay/delay.c 

OBJS += \
./Platform/delay/delay.o 

C_DEPS += \
./Platform/delay/delay.d 


# Each subdirectory must supply rules for building sources it contributes
Platform/delay/%.o: ../Platform/delay/%.c
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

