################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32f103xb.s 

OBJS += \
./startup/startup_stm32f103xb.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	arm-atollic-eabi-gcc -c -mthumb -mcpu=cortex-m3 -g -Wa,--no-warn -x assembler-with-cpp -specs=nano.specs -o "$@" "$<"

