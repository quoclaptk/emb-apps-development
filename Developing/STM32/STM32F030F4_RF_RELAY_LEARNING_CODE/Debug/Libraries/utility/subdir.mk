################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Libraries/utility/utility.cpp 

OBJS += \
./Libraries/utility/utility.o 

CPP_DEPS += \
./Libraries/utility/utility.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/utility/utility.o: ../Libraries/utility/utility.cpp Libraries/utility/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030x6 -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/quoclaptk/STM32CubeIDE/workspace_1.6.0/STM32F030F4_RF_RELAY_LEARNING_CODE/Libraries/RCSwitch" -I"C:/Users/quoclaptk/STM32CubeIDE/workspace_1.6.0/STM32F030F4_RF_RELAY_LEARNING_CODE/Libraries/utility" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Libraries/utility/utility.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

