################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/utility/uip.c \
../Libraries/utility/uip_arp.c 

CPP_SRCS += \
../Libraries/utility/Enc28J60Network.cpp \
../Libraries/utility/mempool.cpp 

OBJS += \
./Libraries/utility/Enc28J60Network.o \
./Libraries/utility/mempool.o \
./Libraries/utility/uip.o \
./Libraries/utility/uip_arp.o 

C_DEPS += \
./Libraries/utility/uip.d \
./Libraries/utility/uip_arp.d 

CPP_DEPS += \
./Libraries/utility/Enc28J60Network.d \
./Libraries/utility/mempool.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/utility/%.o: ../Libraries/utility/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -D__MBED__ -I"../Library/CMSIS/Include" -I"D:\NuEclipWorkspace\Mini58FDE_UIPEthernet\Libraries\mbed" -I"D:\NuEclipWorkspace\Mini58FDE_UIPEthernet\Libraries\utility" -I"D:\NuEclipWorkspace\Mini58FDE_UIPEthernet\User" -I"D:\NuEclipWorkspace\Mini58FDE_UIPEthernet\Libraries" -I"../Library/Device/Nuvoton/Mini58Series/Include" -I"../Library/StdDriver/inc" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Libraries/utility/%.o: ../Libraries/utility/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"D:\NuEclipWorkspace\Mini58FDE_UIPEthernet\Libraries" -I"D:\NuEclipWorkspace\Mini58FDE_UIPEthernet\Libraries\mbed" -I"D:\NuEclipWorkspace\Mini58FDE_UIPEthernet\Libraries\utility" -I"../Library/CMSIS/Include" -I"../Library/Device/Nuvoton/Mini58Series/Include" -I"../Library/StdDriver/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


