################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Aplication/request/request.c 

OBJS += \
./Aplication/request/request.o 

C_DEPS += \
./Aplication/request/request.d 


# Each subdirectory must supply rules for building sources it contributes
Aplication/request/%.o: ../Aplication/request/%.c
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

