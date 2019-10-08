################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Aplication/ESP8266/ESP8266.c 

OBJS += \
./Aplication/ESP8266/ESP8266.o 

C_DEPS += \
./Aplication/ESP8266/ESP8266.d 


# Each subdirectory must supply rules for building sources it contributes
Aplication/ESP8266/%.o: ../Aplication/ESP8266/%.c
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

