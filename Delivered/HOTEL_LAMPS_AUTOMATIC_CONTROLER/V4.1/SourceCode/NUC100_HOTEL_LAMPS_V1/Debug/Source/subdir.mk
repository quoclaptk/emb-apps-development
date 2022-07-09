################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/main.cpp 

OBJS += \
./Source/main.o 

CPP_DEPS += \
./Source/main.d 


# Each subdirectory must supply rules for building sources it contributes
Source/%.o: ../Source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_ARDUINO -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Libraries\LiquidCrystal_I2C-1.1.2" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Libraries" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Libraries\RTC" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Source" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Libraries\mbed" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Device" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Drivers" -std=gnu++11 -fabi-version=0 -O0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


