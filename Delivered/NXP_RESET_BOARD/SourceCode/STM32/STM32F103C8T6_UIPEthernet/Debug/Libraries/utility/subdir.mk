################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/utility/uip.c \
../Libraries/utility/uip_arp.c 

CPP_SRCS += \
../Libraries/utility/Enc28J60Network.cpp \
../Libraries/utility/mempool.cpp 

C_DEPS += \
./Libraries/utility/uip.d \
./Libraries/utility/uip_arp.d 

OBJS += \
./Libraries/utility/Enc28J60Network.o \
./Libraries/utility/mempool.o \
./Libraries/utility/uip.o \
./Libraries/utility/uip_arp.o 

CPP_DEPS += \
./Libraries/utility/Enc28J60Network.d \
./Libraries/utility/mempool.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/utility/%.o: ../Libraries/utility/%.cpp Libraries/utility/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -D__MBED__ -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/PROJECTS_2022/MyProjects/Delivered/NXP_RESET_BOARD/SourceCode/STM32/STM32F103C8T6_UIPEthernet/Libraries/utility" -I"D:/PROJECTS_2022/MyProjects/Delivered/NXP_RESET_BOARD/SourceCode/STM32/STM32F103C8T6_UIPEthernet/Libraries" -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Libraries/utility/%.o: ../Libraries/utility/%.c Libraries/utility/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -D__MBED__ -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/PROJECTS_2022/MyProjects/Delivered/NXP_RESET_BOARD/SourceCode/STM32/STM32F103C8T6_UIPEthernet/Libraries/utility" -I"D:/PROJECTS_2022/MyProjects/Delivered/NXP_RESET_BOARD/SourceCode/STM32/STM32F103C8T6_UIPEthernet/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Libraries-2f-utility

clean-Libraries-2f-utility:
	-$(RM) ./Libraries/utility/Enc28J60Network.d ./Libraries/utility/Enc28J60Network.o ./Libraries/utility/mempool.d ./Libraries/utility/mempool.o ./Libraries/utility/uip.d ./Libraries/utility/uip.o ./Libraries/utility/uip_arp.d ./Libraries/utility/uip_arp.o

.PHONY: clean-Libraries-2f-utility

