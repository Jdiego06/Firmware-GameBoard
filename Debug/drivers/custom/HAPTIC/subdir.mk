################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/custom/HAPTIC/BUTTON.c 

OBJS += \
./drivers/custom/HAPTIC/BUTTON.o 

C_DEPS += \
./drivers/custom/HAPTIC/BUTTON.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/custom/HAPTIC/%.o: ../drivers/custom/HAPTIC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DCPU_MK64FN1M0VDC12 -DCPU_MK64FN1M0VDC12_cm4 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I../component/serial_manager -I../drivers/custom -I../drivers/custom/TFT -I../drivers -I../device -I../CMSIS -I../CMSIS_driver -I../board -I../component/uart -I../utilities -I../source -I../ -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

