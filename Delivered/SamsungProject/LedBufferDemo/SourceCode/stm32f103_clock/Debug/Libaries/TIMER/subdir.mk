################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libaries/TIMER/Timer.c 

OBJS += \
./Libaries/TIMER/Timer.o 

C_DEPS += \
./Libaries/TIMER/Timer.d 


# Each subdirectory must supply rules for building sources it contributes
Libaries/TIMER/%.o: ../Libaries/TIMER/%.c Libaries/TIMER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"D:/PROJECTS_2022/MyProjects/Delivered/SamsungProject/LedBufferDemo/SourceCode/stm32f103_clock/Libaries/TIMER" -I"D:/PROJECTS_2022/MyProjects/Delivered/SamsungProject/LedBufferDemo/SourceCode/stm32f103_clock/Libaries/GPIO" -I"D:/PROJECTS_2022/MyProjects/Delivered/SamsungProject/LedBufferDemo/SourceCode/stm32f103_clock/Libaries/systern clock" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Libaries-2f-TIMER

clean-Libaries-2f-TIMER:
	-$(RM) ./Libaries/TIMER/Timer.d ./Libaries/TIMER/Timer.o

.PHONY: clean-Libaries-2f-TIMER

