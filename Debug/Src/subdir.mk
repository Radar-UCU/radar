################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Src/sh_cmd.s 

C_SRCS += \
../Src/MicroServo.c \
../Src/echo_locator.c \
../Src/gpio.c \
../Src/lcd5110.c \
../Src/lcd5110_hal.c \
../Src/lcd5110_ll.c \
../Src/main.c \
../Src/screen.c \
../Src/semihosting.c \
../Src/spi.c \
../Src/stm32f3xx_hal_msp.c \
../Src/stm32f3xx_it.c \
../Src/syscalls.c \
../Src/system_stm32f3xx.c \
../Src/tim.c 

OBJS += \
./Src/MicroServo.o \
./Src/echo_locator.o \
./Src/gpio.o \
./Src/lcd5110.o \
./Src/lcd5110_hal.o \
./Src/lcd5110_ll.o \
./Src/main.o \
./Src/screen.o \
./Src/semihosting.o \
./Src/sh_cmd.o \
./Src/spi.o \
./Src/stm32f3xx_hal_msp.o \
./Src/stm32f3xx_it.o \
./Src/syscalls.o \
./Src/system_stm32f3xx.o \
./Src/tim.o 

C_DEPS += \
./Src/MicroServo.d \
./Src/echo_locator.d \
./Src/gpio.d \
./Src/lcd5110.d \
./Src/lcd5110_hal.d \
./Src/lcd5110_ll.d \
./Src/main.d \
./Src/screen.d \
./Src/semihosting.d \
./Src/spi.d \
./Src/stm32f3xx_hal_msp.d \
./Src/stm32f3xx_it.d \
./Src/syscalls.d \
./Src/system_stm32f3xx.d \
./Src/tim.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F303xC '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -I"/home/inkognita/STMProjects/SemesterProject/Inc" -I"/home/inkognita/STMProjects/SemesterProject/Drivers/STM32F3xx_HAL_Driver/Inc" -I"/home/inkognita/STMProjects/SemesterProject/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"/home/inkognita/STMProjects/SemesterProject/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"/home/inkognita/STMProjects/SemesterProject/Drivers/CMSIS/Include" -I"/home/inkognita/STMProjects/SemesterProject/Inc" -I"/home/inkognita/STMProjects/SemesterProject/Drivers/CMSIS/Include" -I"/home/inkognita/STMProjects/SemesterProject/Drivers/CMSIS/Include" -I"/home/inkognita/STMProjects/SemesterProject/Drivers/CMSIS/Include" -I"/home/inkognita/STMProjects/SemesterProject/Drivers/CMSIS/Include" -I"/home/inkognita/STMProjects/SemesterProject/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Src/%.o: ../Src/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


