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
Libraries/mbed/IPAddress.o: ../Libraries/mbed/IPAddress.cpp Libraries/mbed/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I"C:/Users/quoclaptk/STM32CubeIDE/workspace_1.6.0/STM32F103RCT6_EXTI/Libraries/mbed" -I"C:/Users/quoclaptk/STM32CubeIDE/workspace_1.6.0/STM32F103RCT6_EXTI/Libraries/RCSwitch" -I"C:/Users/quoclaptk/STM32CubeIDE/workspace_1.6.0/STM32F103RCT6_EXTI/Libraries/utility" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/quoclaptk/STM32CubeIDE/workspace_1.6.0/STM32F103RCT6_EXTI/Libraries/flash" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Libraries/mbed/IPAddress.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Libraries/mbed/Print.o: ../Libraries/mbed/Print.cpp Libraries/mbed/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I"C:/Users/quoclaptk/STM32CubeIDE/workspace_1.6.0/STM32F103RCT6_EXTI/Libraries/mbed" -I"C:/Users/quoclaptk/STM32CubeIDE/workspace_1.6.0/STM32F103RCT6_EXTI/Libraries/RCSwitch" -I"C:/Users/quoclaptk/STM32CubeIDE/workspace_1.6.0/STM32F103RCT6_EXTI/Libraries/utility" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/quoclaptk/STM32CubeIDE/workspace_1.6.0/STM32F103RCT6_EXTI/Libraries/flash" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Libraries/mbed/Print.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Libraries/mbed/WString.o: ../Libraries/mbed/WString.cpp Libraries/mbed/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I"C:/Users/quoclaptk/STM32CubeIDE/workspace_1.6.0/STM32F103RCT6_EXTI/Libraries/mbed" -I"C:/Users/quoclaptk/STM32CubeIDE/workspace_1.6.0/STM32F103RCT6_EXTI/Libraries/RCSwitch" -I"C:/Users/quoclaptk/STM32CubeIDE/workspace_1.6.0/STM32F103RCT6_EXTI/Libraries/utility" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/quoclaptk/STM32CubeIDE/workspace_1.6.0/STM32F103RCT6_EXTI/Libraries/flash" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Libraries/mbed/WString.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Libraries/mbed/dtostrf.o: ../Libraries/mbed/dtostrf.c Libraries/mbed/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Libraries/mbed/dtostrf.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Libraries/mbed/itoa.o: ../Libraries/mbed/itoa.c Libraries/mbed/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Libraries/mbed/itoa.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

