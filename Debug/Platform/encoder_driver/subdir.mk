################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Platform/encoder_driver/encoder_driver.c 

OBJS += \
./Platform/encoder_driver/encoder_driver.o 

C_DEPS += \
./Platform/encoder_driver/encoder_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Platform/encoder_driver/%.o: ../Platform/encoder_driver/%.c
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

