################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Libraries/Adafruit_BusIO/Adafruit_I2CDevice.cpp 

OBJS += \
./Libraries/Adafruit_BusIO/Adafruit_I2CDevice.o 

CPP_DEPS += \
./Libraries/Adafruit_BusIO/Adafruit_I2CDevice.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/Adafruit_BusIO/%.o: ../Libraries/Adafruit_BusIO/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -D__MBED__ -I"D:\NuEclipWorkspace\WP01\NUC100_HOTEL_LAMPS_V1\Source" -I"D:\NuEclipWorkspace\WP01\NUC100_HOTEL_LAMPS_V1\Libraries\mbed" -I"D:\NuEclipWorkspace\WP01\NUC100_HOTEL_LAMPS_V1\Libraries\Adafruit_BusIO" -I"D:\NuEclipWorkspace\WP01\NUC100_HOTEL_LAMPS_V1\Libraries\RTClib-2.0.2" -I"D:\NuEclipWorkspace\WP01\NUC100_HOTEL_LAMPS_V1\Device" -I"D:\NuEclipWorkspace\WP01\NUC100_HOTEL_LAMPS_V1\Drivers" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


