################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library/clk.c \
../Library/gpio.c \
../Library/retarget.c \
../Library/spi.c \
../Library/sys.c \
../Library/timer.c \
../Library/uart.c 

OBJS += \
./Library/clk.o \
./Library/gpio.o \
./Library/retarget.o \
./Library/spi.o \
./Library/sys.o \
./Library/timer.o \
./Library/uart.o 

C_DEPS += \
./Library/clk.d \
./Library/gpio.d \
./Library/retarget.d \
./Library/spi.d \
./Library/sys.d \
./Library/timer.d \
./Library/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Library/%.o: ../Library/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"D:\NuEclipWorkspace\Mini58FDE_UIPEthernet\Libraries" -I"D:\NuEclipWorkspace\Mini58FDE_UIPEthernet\Libraries\mbed" -I"D:\NuEclipWorkspace\Mini58FDE_UIPEthernet\Libraries\utility" -I"../Library/CMSIS/Include" -I"../Library/Device/Nuvoton/Mini58Series/Include" -I"../Library/StdDriver/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

