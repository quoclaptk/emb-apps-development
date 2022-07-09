################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/mbed/dtostrf.c \
../Libraries/mbed/itoa.c 

CPP_SRCS += \
../Libraries/mbed/CccCcC.cpp \
../Libraries/mbed/IPAddress.cpp \
../Libraries/mbed/Print.cpp \
../Libraries/mbed/WString.cpp \
../Libraries/mbed/millis.cpp 

OBJS += \
./Libraries/mbed/CccCcC.o \
./Libraries/mbed/IPAddress.o \
./Libraries/mbed/Print.o \
./Libraries/mbed/WString.o \
./Libraries/mbed/dtostrf.o \
./Libraries/mbed/itoa.o \
./Libraries/mbed/millis.o 

C_DEPS += \
./Libraries/mbed/dtostrf.d \
./Libraries/mbed/itoa.d 

CPP_DEPS += \
./Libraries/mbed/CccCcC.d \
./Libraries/mbed/IPAddress.d \
./Libraries/mbed/Print.d \
./Libraries/mbed/WString.d \
./Libraries/mbed/millis.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/mbed/%.o: ../Libraries/mbed/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_ARDUINO -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Libraries\LiquidCrystal_I2C-1.1.2" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Libraries" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Libraries\RTC" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Source" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Libraries\mbed" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Device" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Drivers" -std=gnu++11 -fabi-version=0 -O0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Libraries/mbed/%.o: ../Libraries/mbed/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_ARDUINO -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Libraries\LiquidCrystal_I2C-1.1.2" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Libraries" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Libraries\RTC" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Source" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Libraries\mbed" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Device" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Drivers" -std=gnu11 -O0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


