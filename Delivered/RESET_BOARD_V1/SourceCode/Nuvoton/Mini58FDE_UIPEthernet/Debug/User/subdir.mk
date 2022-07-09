################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../User/main.cpp 

OBJS += \
./User/main.o 

CPP_DEPS += \
./User/main.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -D__MBED__ -I"../Library/CMSIS/Include" -I"D:\NuEclipWorkspace\Mini58FDE_UIPEthernet\Libraries\mbed" -I"D:\NuEclipWorkspace\Mini58FDE_UIPEthernet\Libraries\utility" -I"D:\NuEclipWorkspace\Mini58FDE_UIPEthernet\User" -I"D:\NuEclipWorkspace\Mini58FDE_UIPEthernet\Libraries" -I"../Library/Device/Nuvoton/Mini58Series/Include" -I"../Library/StdDriver/inc" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


