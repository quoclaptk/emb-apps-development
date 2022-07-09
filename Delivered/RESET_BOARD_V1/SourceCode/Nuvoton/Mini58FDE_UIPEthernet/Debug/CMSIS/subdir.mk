################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CMSIS/system_Mini58Series.c 

OBJS += \
./CMSIS/system_Mini58Series.o 

C_DEPS += \
./CMSIS/system_Mini58Series.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/%.o: ../CMSIS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"D:\NuEclipWorkspace\Mini58FDE_UIPEthernet\Libraries" -I"D:\NuEclipWorkspace\Mini58FDE_UIPEthernet\Libraries\mbed" -I"D:\NuEclipWorkspace\Mini58FDE_UIPEthernet\Libraries\utility" -I"../Library/CMSIS/Include" -I"../Library/Device/Nuvoton/Mini58Series/Include" -I"../Library/StdDriver/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


