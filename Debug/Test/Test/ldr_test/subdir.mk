################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Test/Test/ldr_test/ldr_test.c 

OBJS += \
./Test/Test/ldr_test/ldr_test.o 

C_DEPS += \
./Test/Test/ldr_test/ldr_test.d 


# Each subdirectory must supply rules for building sources it contributes
Test/Test/ldr_test/%.o: ../Test/Test/ldr_test/%.c
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

