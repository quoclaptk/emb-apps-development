################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/mbed/dtostrf.c \
../Libraries/mbed/itoa.c 

CPP_SRCS += \
../Libraries/mbed/IPAddress.cpp \
../Libraries/mbed/Print.cpp \
../Libraries/mbed/WString.cpp 

OBJS += \
./Libraries/mbed/IPAddress.o \
./Libraries/mbed/Print.o \
./Libraries/mbed/WString.o \
./Libraries/mbed/dtostrf.o \
./Libraries/mbed/itoa.o 

C_DEPS += \
./Libraries/mbed/dtostrf.d \
./Libraries/mbed/itoa.d 

CPP_DEPS += \
./Libraries/mbed/IPAddress.d \
./Libraries/mbed/Print.d \
./Libraries/mbed/WString.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/mbed/%.o: ../Libraries/mbed/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"../Library/CMSIS/Include" -I"../Library/Device/Nuvoton/Mini58Series/Include" -I"../Library/StdDriver/inc" -I"D:\NuEclipWorkspace\Mini58FDE_nRF24L01\User" -I"D:\NuEclipWorkspace\Mini58FDE_nRF24L01\Libraries\mbed" -I"D:\NuEclipWorkspace\Mini58FDE_nRF24L01\Libraries\nRF24L01P" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Libraries/mbed/%.o: ../Libraries/mbed/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"../Library/CMSIS/Include" -I"../Library/Device/Nuvoton/Mini58Series/Include" -I"../Library/StdDriver/inc" -I"D:\NuEclipWorkspace\Mini58FDE_nRF24L01\User" -I"D:\NuEclipWorkspace\Mini58FDE_nRF24L01\Libraries\mbed" -I"D:\NuEclipWorkspace\Mini58FDE_nRF24L01\Libraries\nRF24L01P" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


