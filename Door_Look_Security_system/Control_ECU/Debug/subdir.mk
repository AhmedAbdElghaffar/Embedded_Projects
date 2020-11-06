################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Control_Application.c \
../Control_main.c \
../EEPROM.c \
../Motor.c \
../TWI.c \
../Timer1.c \
../UART.c 

OBJS += \
./Control_Application.o \
./Control_main.o \
./EEPROM.o \
./Motor.o \
./TWI.o \
./Timer1.o \
./UART.o 

C_DEPS += \
./Control_Application.d \
./Control_main.d \
./EEPROM.d \
./Motor.d \
./TWI.d \
./Timer1.d \
./UART.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


