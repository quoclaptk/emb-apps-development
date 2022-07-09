################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Device/_syscalls.c \
../Device/system_NUC100Series.c 

S_UPPER_SRCS += \
../Device/startup_NUC100Series.S 

OBJS += \
./Device/_syscalls.o \
./Device/startup_NUC100Series.o \
./Device/system_NUC100Series.o 

S_UPPER_DEPS += \
./Device/startup_NUC100Series.d 

C_DEPS += \
./Device/_syscalls.d \
./Device/system_NUC100Series.d 


# Each subdirectory must supply rules for building sources it contributes
Device/%.o: ../Device/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_ARDUINO -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Libraries\LiquidCrystal_I2C-1.1.2" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Libraries" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Libraries\RTC" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Source" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Libraries\mbed" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Device" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Drivers" -std=gnu11 -O0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Device/%.o: ../Device/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


