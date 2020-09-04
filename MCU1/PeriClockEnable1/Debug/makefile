################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
PeriClockEnable1.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
PeriClockEnable1.list \

OBJCOPY_BIN += \
PeriClockEnable1.bin \


# All Target
all: PeriClockEnable1.elf secondary-outputs

# Tool invocations
PeriClockEnable1.elf: $(OBJS) $(USER_OBJS) D:\Summer\ 2020\Embedded\ Software\Wrokspace\MCU1\PeriClockEnable1\STM32F446RETX_FLASH.ld
	arm-none-eabi-gcc -o "PeriClockEnable1.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\Summer 2020\Embedded Software\Wrokspace\MCU1\PeriClockEnable1\STM32F446RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="PeriClockEnable1.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

PeriClockEnable1.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "PeriClockEnable1.list"
	@echo 'Finished building: $@'
	@echo ' '

PeriClockEnable1.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "PeriClockEnable1.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
