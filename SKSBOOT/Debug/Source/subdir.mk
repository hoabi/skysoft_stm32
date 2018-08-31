################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/common.c \
../Source/download.c \
../Source/main.c \
../Source/mainboot.c \
../Source/stm32f30x_it.c \
../Source/syscalls.c \
../Source/system_stm32f30x.c \
../Source/xprintf.c \
../Source/ymodem.c 

S_UPPER_SRCS += \
../Source/startup_stm32f30x.S 

OBJS += \
./Source/common.o \
./Source/download.o \
./Source/main.o \
./Source/mainboot.o \
./Source/startup_stm32f30x.o \
./Source/stm32f30x_it.o \
./Source/syscalls.o \
./Source/system_stm32f30x.o \
./Source/xprintf.o \
./Source/ymodem.o 

S_UPPER_DEPS += \
./Source/startup_stm32f30x.d 

C_DEPS += \
./Source/common.d \
./Source/download.d \
./Source/main.d \
./Source/mainboot.d \
./Source/stm32f30x_it.d \
./Source/syscalls.d \
./Source/system_stm32f30x.d \
./Source/xprintf.d \
./Source/ymodem.d 


# Each subdirectory must supply rules for building sources it contributes
Source/%.o: ../Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -DSTM32F303xE -DUSE_STDPERIPH_DRIVER -DUSE_STM3210E_EVAL -I"D:\EclipseIndigo\workspace\SKSBOOT\Utilities\STM32_EVAL\STM32303C_EVAL" -I"D:\EclipseIndigo\workspace\SKSBOOT\Libraries\CMSIS\Include" -I"D:\EclipseIndigo\workspace\SKSBOOT\Libraries\STM32F30x_StdPeriph_Driver\inc" -I"D:\EclipseIndigo\workspace\SKSBOOT\Source" -I"D:\EclipseIndigo\workspace\SKSBOOT\Utilities\STM32_EVAL" -Os -ffunction-sections -fdata-sections -Wall -std=gnu99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m4 -mthumb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/%.o: ../Source/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m4 -mthumb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


