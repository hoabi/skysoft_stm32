################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/STM32_EVAL/stm32_eval.c 

OBJS += \
./Utilities/STM32_EVAL/stm32_eval.o 

C_DEPS += \
./Utilities/STM32_EVAL/stm32_eval.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/STM32_EVAL/%.o: ../Utilities/STM32_EVAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -DSTM32F10X_HD -DUSE_STDPERIPH_DRIVER -DUSE_STM3210E_EVAL -I"E:\EclipseIndigo\workspace\SKSBOOT\Libraries\CMSIS\CM3\CoreSupport" -I"E:\EclipseIndigo\workspace\SKSBOOT\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x" -I"E:\EclipseIndigo\workspace\SKSBOOT\Libraries\STM32F10x_StdPeriph_Driver\inc" -I"E:\EclipseIndigo\workspace\SKSBOOT\Source" -I"E:\EclipseIndigo\workspace\SKSBOOT\Utilities\STM32_EVAL" -Os -ffunction-sections -fdata-sections -Wall -std=gnu99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


