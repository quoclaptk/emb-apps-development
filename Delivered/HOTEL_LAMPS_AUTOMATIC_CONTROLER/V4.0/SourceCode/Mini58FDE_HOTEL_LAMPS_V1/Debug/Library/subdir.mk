################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library/clk.c \
../Library/gpio.c \
../Library/retarget.c \
../Library/sys.c \
../Library/timer.c \
../Library/uart.c 

OBJS += \
./Library/clk.o \
./Library/gpio.o \
./Library/retarget.o \
./Library/sys.o \
./Library/timer.o \
./Library/uart.o 

C_DEPS += \
./Library/clk.d \
./Library/gpio.d \
./Library/retarget.d \
./Library/sys.d \
./Library/timer.d \
./Library/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Library/%.o: ../Library/%.c Library/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"../Library/CMSIS/Include" -I"../Library/Device/Nuvoton/Mini58Series/Include" -I"../Library/StdDriver/inc" -I"D:\emb-apps-development\Delivered\HOTEL_LAMPS_AUTOMATIC_CONTROLER\V4\SourceCode\Mini58FDE_HOTEL_LAMPS_V1\Libraries" -I"D:\emb-apps-development\Delivered\HOTEL_LAMPS_AUTOMATIC_CONTROLER\V4\SourceCode\Mini58FDE_HOTEL_LAMPS_V1\Libraries\LiquidCrystal_I2C-1.1.2" -I"D:\emb-apps-development\Delivered\HOTEL_LAMPS_AUTOMATIC_CONTROLER\V4\SourceCode\Mini58FDE_HOTEL_LAMPS_V1\Libraries\mbed" -I"D:\emb-apps-development\Delivered\HOTEL_LAMPS_AUTOMATIC_CONTROLER\V4\SourceCode\Mini58FDE_HOTEL_LAMPS_V1\Libraries\RTC" -I"D:\emb-apps-development\Delivered\HOTEL_LAMPS_AUTOMATIC_CONTROLER\V4\SourceCode\Mini58FDE_HOTEL_LAMPS_V1\User" -std=gnu11 -O0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


