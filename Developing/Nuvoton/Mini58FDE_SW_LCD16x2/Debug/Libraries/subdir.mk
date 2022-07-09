################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/swI2C.c 

CPP_SRCS += \
../Libraries/RTC.cpp \
../Libraries/lcd16x2.cpp 

OBJS += \
./Libraries/RTC.o \
./Libraries/lcd16x2.o \
./Libraries/swI2C.o 

C_DEPS += \
./Libraries/swI2C.d 

CPP_DEPS += \
./Libraries/RTC.d \
./Libraries/lcd16x2.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/%.o: ../Libraries/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"../Library/CMSIS/Include" -I"../Library/Device/Nuvoton/Mini58Series/Include" -I"../Library/StdDriver/inc" -I"D:\NuEclipWorkspace\Mini58FDE_SW_LCD16x2\Libraries" -I"D:\NuEclipWorkspace\Mini58FDE_SW_LCD16x2\User" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Libraries/%.o: ../Libraries/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"../Library/CMSIS/Include" -I"../Library/Device/Nuvoton/Mini58Series/Include" -I"../Library/StdDriver/inc" -I"D:\NuEclipWorkspace\Mini58FDE_SW_LCD16x2\Libraries" -I"D:\NuEclipWorkspace\Mini58FDE_SW_LCD16x2\User" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


