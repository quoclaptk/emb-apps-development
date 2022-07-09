################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Libraries/nRF24L01P/RF24.cpp 

OBJS += \
./Libraries/nRF24L01P/RF24.o 

CPP_DEPS += \
./Libraries/nRF24L01P/RF24.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/nRF24L01P/%.o: ../Libraries/nRF24L01P/%.cpp Libraries/nRF24L01P/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/PROJECTS_2022/MyProjects/Delivered/NXP_RESET_BOARD/SourceCode/STM32/STM32F103C8T6_nRF24L01/Libraries/mbed" -I"D:/PROJECTS_2022/MyProjects/Delivered/NXP_RESET_BOARD/SourceCode/STM32/STM32F103C8T6_nRF24L01/Libraries/nRF24L01P" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Libraries-2f-nRF24L01P

clean-Libraries-2f-nRF24L01P:
	-$(RM) ./Libraries/nRF24L01P/RF24.d ./Libraries/nRF24L01P/RF24.o

.PHONY: clean-Libraries-2f-nRF24L01P

