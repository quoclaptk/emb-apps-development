################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Libraries/LiquidCrystal_I2C-1.1.2/LiquidCrystal_I2C.cpp 

OBJS += \
./Libraries/LiquidCrystal_I2C-1.1.2/LiquidCrystal_I2C.o 

CPP_DEPS += \
./Libraries/LiquidCrystal_I2C-1.1.2/LiquidCrystal_I2C.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/LiquidCrystal_I2C-1.1.2/%.o: ../Libraries/LiquidCrystal_I2C-1.1.2/%.cpp Libraries/LiquidCrystal_I2C-1.1.2/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"../Library/CMSIS/Include" -I"../Library/Device/Nuvoton/Mini58Series/Include" -I"../Library/StdDriver/inc" -I"D:\emb-apps-development\Delivered\HOTEL_LAMPS_AUTOMATIC_CONTROLER\V4\SourceCode\Mini58FDE_HOTEL_LAMPS_V1\Libraries" -I"D:\emb-apps-development\Delivered\HOTEL_LAMPS_AUTOMATIC_CONTROLER\V4\SourceCode\Mini58FDE_HOTEL_LAMPS_V1\Libraries\LiquidCrystal_I2C-1.1.2" -I"D:\emb-apps-development\Delivered\HOTEL_LAMPS_AUTOMATIC_CONTROLER\V4\SourceCode\Mini58FDE_HOTEL_LAMPS_V1\Libraries\mbed" -I"D:\emb-apps-development\Delivered\HOTEL_LAMPS_AUTOMATIC_CONTROLER\V4\SourceCode\Mini58FDE_HOTEL_LAMPS_V1\Libraries\RTC" -I"D:\emb-apps-development\Delivered\HOTEL_LAMPS_AUTOMATIC_CONTROLER\V4\SourceCode\Mini58FDE_HOTEL_LAMPS_V1\User" -std=gnu++11 -fabi-version=0 -O0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


