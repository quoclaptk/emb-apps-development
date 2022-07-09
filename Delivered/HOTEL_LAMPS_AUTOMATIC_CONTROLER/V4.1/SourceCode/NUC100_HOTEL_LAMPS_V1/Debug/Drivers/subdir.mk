################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/acmp.c \
../Drivers/adc.c \
../Drivers/clk.c \
../Drivers/crc.c \
../Drivers/fmc.c \
../Drivers/gpio.c \
../Drivers/i2c.c \
../Drivers/i2s.c \
../Drivers/pdma.c \
../Drivers/ps2.c \
../Drivers/pwm.c \
../Drivers/retarget.c \
../Drivers/rtc.c \
../Drivers/sc.c \
../Drivers/spi.c \
../Drivers/sys.c \
../Drivers/timer.c \
../Drivers/uart.c \
../Drivers/usbd.c \
../Drivers/wdt.c \
../Drivers/wwdt.c 

OBJS += \
./Drivers/acmp.o \
./Drivers/adc.o \
./Drivers/clk.o \
./Drivers/crc.o \
./Drivers/fmc.o \
./Drivers/gpio.o \
./Drivers/i2c.o \
./Drivers/i2s.o \
./Drivers/pdma.o \
./Drivers/ps2.o \
./Drivers/pwm.o \
./Drivers/retarget.o \
./Drivers/rtc.o \
./Drivers/sc.o \
./Drivers/spi.o \
./Drivers/sys.o \
./Drivers/timer.o \
./Drivers/uart.o \
./Drivers/usbd.o \
./Drivers/wdt.o \
./Drivers/wwdt.o 

C_DEPS += \
./Drivers/acmp.d \
./Drivers/adc.d \
./Drivers/clk.d \
./Drivers/crc.d \
./Drivers/fmc.d \
./Drivers/gpio.d \
./Drivers/i2c.d \
./Drivers/i2s.d \
./Drivers/pdma.d \
./Drivers/ps2.d \
./Drivers/pwm.d \
./Drivers/retarget.d \
./Drivers/rtc.d \
./Drivers/sc.d \
./Drivers/spi.d \
./Drivers/sys.d \
./Drivers/timer.d \
./Drivers/uart.d \
./Drivers/usbd.d \
./Drivers/wdt.d \
./Drivers/wwdt.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/%.o: ../Drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_ARDUINO -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Libraries\LiquidCrystal_I2C-1.1.2" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Libraries" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Libraries\RTC" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Source" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Libraries\mbed" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Device" -I"D:\NuEclipWorkspace\NUC100_HOTEL_LAMPS_V1\Drivers" -std=gnu11 -O0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


