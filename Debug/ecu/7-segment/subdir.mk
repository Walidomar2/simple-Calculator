################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ecu/7-segment/ecu_7segment.c 

OBJS += \
./ecu/7-segment/ecu_7segment.o 

C_DEPS += \
./ecu/7-segment/ecu_7segment.d 


# Each subdirectory must supply rules for building sources it contributes
ecu/7-segment/%.o: ../ecu/7-segment/%.c ecu/7-segment/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


