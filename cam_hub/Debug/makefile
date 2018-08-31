################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := cs-rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include scr/subdir.mk
-include Libraries/STM32F0xx_StdPeriph_Driver/src/subdir.mk
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
cam_hub.hex \

SECONDARY_LIST += \
cam_hub.lst \

SECONDARY_SIZE += \
cam_hub.siz \


# All Target
all: cam_hub.elf secondary-outputs

# Tool invocations
cam_hub.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Sourcery Windows GCC C Linker'
	arm-none-eabi-gcc -T"D:\EclipseIndigo\workspace\cam_hub\scr\STM32F091CC_FLASH.ld" -Xlinker --gc-sections -Wl,-Map,cam_hub.map -mcpu=cortex-m0 -mthumb -g3 -gdwarf-2 -o "cam_hub.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

cam_hub.hex: cam_hub.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex cam_hub.elf  "cam_hub.hex"
	@echo 'Finished building: $@'
	@echo ' '

cam_hub.lst: cam_hub.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Listing'
	arm-none-eabi-objdump -h -S cam_hub.elf > "cam_hub.lst"
	@echo 'Finished building: $@'
	@echo ' '

cam_hub.siz: cam_hub.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Print Size'
	arm-none-eabi-size  --format=berkeley -x cam_hub.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) cam_hub.elf
	-@echo ' '

post-build:
	-@echo 'Create Binary'
	-arm-none-eabi-objcopy -S  -O binary "cam_hub.elf" "cam_hub.bin"
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
