################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/interrupt/external_interrupt.c 

OBJS += \
./MCAL/interrupt/external_interrupt.o 

C_DEPS += \
./MCAL/interrupt/external_interrupt.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/interrupt/%.o: ../MCAL/interrupt/%.c MCAL/interrupt/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


