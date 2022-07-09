################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Source/subdir.mk
-include Libraries/mbed/subdir.mk
-include Libraries/RTC/subdir.mk
-include Libraries/LiquidCrystal_I2C-1.1.2/subdir.mk
-include Libraries/subdir.mk
-include Drivers/subdir.mk
-include Device/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
NUC100_HOTEL_LAMPS_V1.hex \

SECONDARY_SIZE += \
NUC100_HOTEL_LAMPS_V1.siz \


# All Target
all: NUC100_HOTEL_LAMPS_V1.elf secondary-outputs

# Tool invocations
NUC100_HOTEL_LAMPS_V1.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM GNU C++ Linker'
	arm-none-eabi-g++ -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -T "D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Device\gcc_arm.ld" -Xlinker --gc-sections -Wl,-Map,"NUC100_HOTEL_LAMPS_V1.map" --specs=nano.specs -o "NUC100_HOTEL_LAMPS_V1.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

NUC100_HOTEL_LAMPS_V1.hex: NUC100_HOTEL_LAMPS_V1.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex "NUC100_HOTEL_LAMPS_V1.elf"  "NUC100_HOTEL_LAMPS_V1.hex"
	@echo 'Finished building: $@'
	@echo ' '

NUC100_HOTEL_LAMPS_V1.siz: NUC100_HOTEL_LAMPS_V1.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "NUC100_HOTEL_LAMPS_V1.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS)$(CPP_DEPS) NUC100_HOTEL_LAMPS_V1.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
