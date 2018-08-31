################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := cs-rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Utilities/STM32_EVAL/STM32303C_EVAL/subdir.mk
-include Source/subdir.mk
-include Libraries/STM32F30x_StdPeriph_Driver/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
SKSBOOT.hex \

SECONDARY_LIST += \
SKSBOOT.lst \

SECONDARY_SIZE += \
SKSBOOT.siz \


# All Target
all: SKSBOOT.elf secondary-outputs

# Tool invocations
SKSBOOT.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Sourcery Windows GCC C Linker'
	arm-none-eabi-gcc -T"D:\EclipseIndigo\workspace\SKSBOOT\STM32F303VE_FLASH.ld" -Xlinker --gc-sections -Wl,-Map,SKSBOOT.map -mcpu=cortex-m4 -mthumb -o "SKSBOOT.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

SKSBOOT.hex: SKSBOOT.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex SKSBOOT.elf  "SKSBOOT.hex"
	@echo 'Finished building: $@'
	@echo ' '

SKSBOOT.lst: SKSBOOT.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Listing'
	arm-none-eabi-objdump -h -S SKSBOOT.elf > "SKSBOOT.lst"
	@echo 'Finished building: $@'
	@echo ' '

SKSBOOT.siz: SKSBOOT.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Print Size'
	arm-none-eabi-size  --format=berkeley SKSBOOT.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) SKSBOOT.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
