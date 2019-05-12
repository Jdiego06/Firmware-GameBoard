################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/game/subdir.mk
-include source/subdir.mk
-include drivers/custom/TFT/images/subdir.mk
-include drivers/custom/TFT/subdir.mk
-include drivers/custom/JOYSTICK/subdir.mk
-include drivers/custom/HAPTIC/subdir.mk
-include drivers/custom/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include component/uart/subdir.mk
-include component/serial_manager/subdir.mk
-include board/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: AngryBirdsV2.axf

# Tool invocations
AngryBirdsV2.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="AngryBirdsV2.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -T AngryBirdsV2_Debug.ld -o "AngryBirdsV2.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) AngryBirdsV2.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "AngryBirdsV2.axf"; # arm-none-eabi-objcopy -v -O binary "AngryBirdsV2.axf" "AngryBirdsV2.bin" ; # checksum -p MK64FX512xxx12 -d "AngryBirdsV2.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
