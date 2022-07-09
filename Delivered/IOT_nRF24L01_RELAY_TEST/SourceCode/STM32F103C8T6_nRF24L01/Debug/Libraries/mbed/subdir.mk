################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/mbed/dtostrf.c \
../Libraries/mbed/itoa.c 

CPP_SRCS += \
../Libraries/mbed/IPAddress.cpp \
../Libraries/mbed/Print.cpp \
../Libraries/mbed/WString.cpp 

C_DEPS += \
./Libraries/mbed/dtostrf.d \
./Libraries/mbed/itoa.d 

OBJS += \
./Libraries/mbed/IPAddress.o \
./Libraries/mbed/Print.o \
./Libraries/mbed/WString.o \
./Libraries/mbed/dtostrf.o \
./Libraries/mbed/itoa.o 

CPP_DEPS += \
./Libraries/mbed/IPAddress.d \
./Libraries/mbed/Print.d \
./Libraries/mbed/WString.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/mbed/%.o: ../Libraries/mbed/%.cpp Libraries/mbed/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/PROJECTS_2022/MyProjects/Delivered/NXP_RESET_BOARD/SourceCode/STM32/STM32F103C8T6_nRF24L01/Libraries/mbed" -I"D:/PROJECTS_2022/MyProjects/Delivered/NXP_RESET_BOARD/SourceCode/STM32/STM32F103C8T6_nRF24L01/Libraries/nRF24L01P" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Libraries/mbed/%.o: ../Libraries/mbed/%.c Libraries/mbed/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/PROJECTS_2022/MyProjects/Delivered/NXP_RESET_BOARD/SourceCode/STM32/STM32F103C8T6_nRF24L01/Libraries/mbed" -I"D:/PROJECTS_2022/MyProjects/Delivered/NXP_RESET_BOARD/SourceCode/STM32/STM32F103C8T6_nRF24L01/Libraries/nRF24L01P" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Libraries-2f-mbed

clean-Libraries-2f-mbed:
	-$(RM) ./Libraries/mbed/IPAddress.d ./Libraries/mbed/IPAddress.o ./Libraries/mbed/Print.d ./Libraries/mbed/Print.o ./Libraries/mbed/WString.d ./Libraries/mbed/WString.o ./Libraries/mbed/dtostrf.d ./Libraries/mbed/dtostrf.o ./Libraries/mbed/itoa.d ./Libraries/mbed/itoa.o

.PHONY: clean-Libraries-2f-mbed

