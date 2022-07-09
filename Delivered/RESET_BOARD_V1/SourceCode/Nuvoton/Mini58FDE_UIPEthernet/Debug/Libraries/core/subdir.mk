################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/core/dtostrf.c \
../Libraries/core/itoa.c 

CPP_SRCS += \
../Libraries/core/Print.cpp \
../Libraries/core/WString.cpp 

OBJS += \
./Libraries/core/Print.o \
./Libraries/core/WString.o \
./Libraries/core/dtostrf.o \
./Libraries/core/itoa.o 

C_DEPS += \
./Libraries/core/dtostrf.d \
./Libraries/core/itoa.d 

CPP_DEPS += \
./Libraries/core/Print.d \
./Libraries/core/WString.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/core/%.o: ../Libraries/core/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -D__MBED__ -I"../Library/CMSIS/Include" -I"D:\NuEclipWorkspace\Mini58FDE_UIPEthernet\Libraries\core" -I"D:\NuEclipWorkspace\Mini58FDE_UIPEthernet\User" -I"D:\NuEclipWorkspace\Mini58FDE_UIPEthernet\Libraries" -I"../Library/Device/Nuvoton/Mini58Series/Include" -I"../Library/StdDriver/inc" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Libraries/core/%.o: ../Libraries/core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"../Library/CMSIS/Include" -I"../Library/Device/Nuvoton/Mini58Series/Include" -I"../Library/StdDriver/inc" -I"D:\NuEclipWorkspace\Mini58FDE_UIPEthernet\Libraries\core" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


