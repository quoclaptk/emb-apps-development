################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Libraries/LCD16X2.cpp 

OBJS += \
./Libraries/LCD16X2.o 

CPP_DEPS += \
./Libraries/LCD16X2.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/%.o: ../Libraries/%.cpp Libraries/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"D:/PROJECTS_2022/MyProjects/Delivered/SamsungProject/LedBufferDemo/SourceCode/STM32F103C8T6-DTH11/Libraries" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Libraries

clean-Libraries:
	-$(RM) ./Libraries/LCD16X2.d ./Libraries/LCD16X2.o

.PHONY: clean-Libraries
