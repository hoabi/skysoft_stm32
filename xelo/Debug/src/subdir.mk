################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/EEprom.c \
../src/HC05.c \
../src/IRsensor.c \
../src/command.c \
../src/delay.c \
../src/main.c \
../src/mainboot.c \
../src/printf-stdarg.c \
../src/queue.c \
../src/stm32f10x_it.c \
../src/syscalls.c \
../src/system_stm32f10x.c \
../src/xprintf.c 

S_UPPER_SRCS += \
../src/startup_stm32f10x_hd.S 

OBJS += \
./src/EEprom.o \
./src/HC05.o \
./src/IRsensor.o \
./src/command.o \
./src/delay.o \
./src/main.o \
./src/mainboot.o \
./src/printf-stdarg.o \
./src/queue.o \
./src/startup_stm32f10x_hd.o \
./src/stm32f10x_it.o \
./src/syscalls.o \
./src/system_stm32f10x.o \
./src/xprintf.o 

S_UPPER_DEPS += \
./src/startup_stm32f10x_hd.d 

C_DEPS += \
./src/EEprom.d \
./src/HC05.d \
./src/IRsensor.d \
./src/command.d \
./src/delay.d \
./src/main.d \
./src/mainboot.d \
./src/printf-stdarg.d \
./src/queue.d \
./src/stm32f10x_it.d \
./src/syscalls.d \
./src/system_stm32f10x.d \
./src/xprintf.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -DUSE_STDPERIPH_DRIVER -DSTM32F10X_HD -I"D:\EclipseIndigo\workspace\xelo\Libraries\CMSIS\Include" -I"D:\EclipseIndigo\workspace\xelo\Libraries\CMSIS\Device\ST\STM32F10x\Include" -I"D:\EclipseIndigo\workspace\xelo\Libraries\STM32F10x_StdPeriph_Driver\inc" -I"D:\EclipseIndigo\workspace\xelo\src" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -DUSE_STDPERIPH_DRIVER -DSTM32F10X_MD -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


