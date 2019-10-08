################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Aplication/encoder/encoder.c 

OBJS += \
./Aplication/encoder/encoder.o 

C_DEPS += \
./Aplication/encoder/encoder.d 


# Each subdirectory must supply rules for building sources it contributes
Aplication/encoder/%.o: ../Aplication/encoder/%.c
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

