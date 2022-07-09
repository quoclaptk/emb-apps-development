################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Libraries/Dhcp.cpp \
../Libraries/Dns.cpp \
../Libraries/UIPClient.cpp \
../Libraries/UIPEthernet.cpp \
../Libraries/UIPServer.cpp \
../Libraries/UIPUdp.cpp 

OBJS += \
./Libraries/Dhcp.o \
./Libraries/Dns.o \
./Libraries/UIPClient.o \
./Libraries/UIPEthernet.o \
./Libraries/UIPServer.o \
./Libraries/UIPUdp.o 

CPP_DEPS += \
./Libraries/Dhcp.d \
./Libraries/Dns.d \
./Libraries/UIPClient.d \
./Libraries/UIPEthernet.d \
./Libraries/UIPServer.d \
./Libraries/UIPUdp.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/%.o: ../Libraries/%.cpp Libraries/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -D__MBED__ -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/PROJECTS_2022/MyProjects/Delivered/NXP_RESET_BOARD/SourceCode/STM32/STM32F103C8T6_UIPEthernet/Libraries/utility" -I"D:/PROJECTS_2022/MyProjects/Delivered/NXP_RESET_BOARD/SourceCode/STM32/STM32F103C8T6_UIPEthernet/Libraries" -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Libraries

clean-Libraries:
	-$(RM) ./Libraries/Dhcp.d ./Libraries/Dhcp.o ./Libraries/Dns.d ./Libraries/Dns.o ./Libraries/UIPClient.d ./Libraries/UIPClient.o ./Libraries/UIPEthernet.d ./Libraries/UIPEthernet.o ./Libraries/UIPServer.d ./Libraries/UIPServer.o ./Libraries/UIPUdp.d ./Libraries/UIPUdp.o

.PHONY: clean-Libraries

