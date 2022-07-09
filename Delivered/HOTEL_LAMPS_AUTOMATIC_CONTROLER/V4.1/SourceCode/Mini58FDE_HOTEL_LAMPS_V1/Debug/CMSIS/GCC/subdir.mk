################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CMSIS/GCC/_syscalls.c 

S_UPPER_SRCS += \
../CMSIS/GCC/startup_Mini58Series.S 

OBJS += \
./CMSIS/GCC/_syscalls.o \
./CMSIS/GCC/startup_Mini58Series.o 

S_UPPER_DEPS += \
./CMSIS/GCC/startup_Mini58Series.d 

C_DEPS += \
./CMSIS/GCC/_syscalls.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/GCC/%.o: ../CMSIS/GCC/%.c CMSIS/GCC/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"../Library/CMSIS/Include" -I"../Library/Device/Nuvoton/Mini58Series/Include" -I"../Library/StdDriver/inc" -I"D:\emb-apps-development\Delivered\HOTEL_LAMPS_AUTOMATIC_CONTROLER\V4\SourceCode\Mini58FDE_HOTEL_LAMPS_V1\Libraries" -I"D:\emb-apps-development\Delivered\HOTEL_LAMPS_AUTOMATIC_CONTROLER\V4\SourceCode\Mini58FDE_HOTEL_LAMPS_V1\Libraries\LiquidCrystal_I2C-1.1.2" -I"D:\emb-apps-development\Delivered\HOTEL_LAMPS_AUTOMATIC_CONTROLER\V4\SourceCode\Mini58FDE_HOTEL_LAMPS_V1\Libraries\mbed" -I"D:\emb-apps-development\Delivered\HOTEL_LAMPS_AUTOMATIC_CONTROLER\V4\SourceCode\Mini58FDE_HOTEL_LAMPS_V1\Libraries\RTC" -I"D:\emb-apps-development\Delivered\HOTEL_LAMPS_AUTOMATIC_CONTROLER\V4\SourceCode\Mini58FDE_HOTEL_LAMPS_V1\User" -std=gnu11 -O0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CMSIS/GCC/%.o: ../CMSIS/GCC/%.S CMSIS/GCC/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -x assembler-with-cpp -I"../Library/CMSIS/Include" -I"../Library/Device/Nuvoton/Mini58Series/Include" -I"../Library/StdDriver/inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


