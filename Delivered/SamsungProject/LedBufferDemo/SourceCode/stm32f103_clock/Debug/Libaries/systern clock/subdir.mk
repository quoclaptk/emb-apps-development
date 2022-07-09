################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libaries/systern\ clock/Clock.c 

OBJS += \
./Libaries/systern\ clock/Clock.o 

C_DEPS += \
./Libaries/systern\ clock/Clock.d 


# Each subdirectory must supply rules for building sources it contributes
Libaries/systern\ clock/Clock.o: ../Libaries/systern\ clock/Clock.c Libaries/systern\ clock/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"D:/PROJECTS_2022/MyProjects/Delivered/SamsungProject/LedBufferDemo/SourceCode/stm32f103_clock/Libaries/TIMER" -I"D:/PROJECTS_2022/MyProjects/Delivered/SamsungProject/LedBufferDemo/SourceCode/stm32f103_clock/Libaries/GPIO" -I"D:/PROJECTS_2022/MyProjects/Delivered/SamsungProject/LedBufferDemo/SourceCode/stm32f103_clock/Libaries/systern clock" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Libaries/systern clock/Clock.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Libaries-2f-systern-20-clock

clean-Libaries-2f-systern-20-clock:
	-$(RM) ./Libaries/systern\ clock/Clock.d ./Libaries/systern\ clock/Clock.o

.PHONY: clean-Libaries-2f-systern-20-clock

