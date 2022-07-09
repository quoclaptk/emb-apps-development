################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Libraries/RTClib-2.0.2/RTC_DS1307.cpp \
../Libraries/RTClib-2.0.2/RTC_DS3231.cpp \
../Libraries/RTClib-2.0.2/RTC_Micros.cpp \
../Libraries/RTClib-2.0.2/RTC_Millis.cpp \
../Libraries/RTClib-2.0.2/RTC_PCF8523.cpp \
../Libraries/RTClib-2.0.2/RTC_PCF8563.cpp \
../Libraries/RTClib-2.0.2/RTClib.cpp 

OBJS += \
./Libraries/RTClib-2.0.2/RTC_DS1307.o \
./Libraries/RTClib-2.0.2/RTC_DS3231.o \
./Libraries/RTClib-2.0.2/RTC_Micros.o \
./Libraries/RTClib-2.0.2/RTC_Millis.o \
./Libraries/RTClib-2.0.2/RTC_PCF8523.o \
./Libraries/RTClib-2.0.2/RTC_PCF8563.o \
./Libraries/RTClib-2.0.2/RTClib.o 

CPP_DEPS += \
./Libraries/RTClib-2.0.2/RTC_DS1307.d \
./Libraries/RTClib-2.0.2/RTC_DS3231.d \
./Libraries/RTClib-2.0.2/RTC_Micros.d \
./Libraries/RTClib-2.0.2/RTC_Millis.d \
./Libraries/RTClib-2.0.2/RTC_PCF8523.d \
./Libraries/RTClib-2.0.2/RTC_PCF8563.d \
./Libraries/RTClib-2.0.2/RTClib.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/RTClib-2.0.2/%.o: ../Libraries/RTClib-2.0.2/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -D__MBED__ -I"D:\NuEclipWorkspace\WP01\NUC100_HOTEL_LAMPS_V1\Source" -I"D:\NuEclipWorkspace\WP01\NUC100_HOTEL_LAMPS_V1\Libraries\mbed" -I"D:\NuEclipWorkspace\WP01\NUC100_HOTEL_LAMPS_V1\Libraries\Adafruit_BusIO" -I"D:\NuEclipWorkspace\WP01\NUC100_HOTEL_LAMPS_V1\Libraries\RTClib-2.0.2" -I"D:\NuEclipWorkspace\WP01\NUC100_HOTEL_LAMPS_V1\Device" -I"D:\NuEclipWorkspace\WP01\NUC100_HOTEL_LAMPS_V1\Drivers" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


