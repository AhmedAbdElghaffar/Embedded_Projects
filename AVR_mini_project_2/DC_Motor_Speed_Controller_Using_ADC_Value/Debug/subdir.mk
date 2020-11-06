################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../External_Interrupts.c \
../LCD.c \
../Main_Dc_speed_controller.c \
../Timer0.c 

OBJS += \
./ADC.o \
./External_Interrupts.o \
./LCD.o \
./Main_Dc_speed_controller.o \
./Timer0.o 

C_DEPS += \
./ADC.d \
./External_Interrupts.d \
./LCD.d \
./Main_Dc_speed_controller.d \
./Timer0.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


