################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/STM32_EVAL/STM32303C_EVAL/stm32303c_eval.c 

OBJS += \
./Utilities/STM32_EVAL/STM32303C_EVAL/stm32303c_eval.o 

C_DEPS += \
./Utilities/STM32_EVAL/STM32303C_EVAL/stm32303c_eval.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/STM32_EVAL/STM32303C_EVAL/%.o: ../Utilities/STM32_EVAL/STM32303C_EVAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -DSTM32F303xE -DUSE_STDPERIPH_DRIVER -DUSE_STM3210E_EVAL -I"D:\EclipseIndigo\workspace\SKSBOOT\Utilities\STM32_EVAL\STM32303C_EVAL" -I"D:\EclipseIndigo\workspace\SKSBOOT\Libraries\CMSIS\Include" -I"D:\EclipseIndigo\workspace\SKSBOOT\Libraries\STM32F30x_StdPeriph_Driver\inc" -I"D:\EclipseIndigo\workspace\SKSBOOT\Source" -I"D:\EclipseIndigo\workspace\SKSBOOT\Utilities\STM32_EVAL" -Os -ffunction-sections -fdata-sections -Wall -std=gnu99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m4 -mthumb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


