################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../scr/CAM_0706.c \
../scr/Util.c \
../scr/alarm.c \
../scr/command.c \
../scr/main.c \
../scr/mainboot.c \
../scr/stm32f0xx_it.c \
../scr/syscalls.c \
../scr/system_stm32f0xx.c \
../scr/xprintf.c 

S_UPPER_SRCS += \
../scr/startup_stm32f091.S 

OBJS += \
./scr/CAM_0706.o \
./scr/Util.o \
./scr/alarm.o \
./scr/command.o \
./scr/main.o \
./scr/mainboot.o \
./scr/startup_stm32f091.o \
./scr/stm32f0xx_it.o \
./scr/syscalls.o \
./scr/system_stm32f0xx.o \
./scr/xprintf.o 

S_UPPER_DEPS += \
./scr/startup_stm32f091.d 

C_DEPS += \
./scr/CAM_0706.d \
./scr/Util.d \
./scr/alarm.d \
./scr/command.d \
./scr/main.d \
./scr/mainboot.d \
./scr/stm32f0xx_it.d \
./scr/syscalls.d \
./scr/system_stm32f0xx.d \
./scr/xprintf.d 


# Each subdirectory must supply rules for building sources it contributes
scr/%.o: ../scr/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -DUSE_STDPERIPH_DRIVER -DSTM32F091 -I"D:\EclipseIndigo\workspace\cam_hub\Libraries\CMSIS\Include" -I"D:\EclipseIndigo\workspace\cam_hub\Libraries\CMSIS\Device\ST\STM32F0xx\Include" -I"D:\EclipseIndigo\workspace\cam_hub\Libraries\STM32F0xx_StdPeriph_Driver\inc" -I"D:\EclipseIndigo\workspace\cam_hub\scr" -Os -ffunction-sections -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m0 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

scr/%.o: ../scr/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -DSTM32F0XX_HD -I"D:\EclipseIndigo\CodeSourcery\Sourcery_CodeBench_Lite_for_ARM_EABI\arm-none-eabi\include" -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m0 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


