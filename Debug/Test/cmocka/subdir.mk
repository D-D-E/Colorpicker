################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Test/cmocka/cmocka.c 

OBJS += \
./Test/cmocka/cmocka.o 

C_DEPS += \
./Test/cmocka/cmocka.d 


# Each subdirectory must supply rules for building sources it contributes
Test/cmocka/%.o: ../Test/cmocka/%.c
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

