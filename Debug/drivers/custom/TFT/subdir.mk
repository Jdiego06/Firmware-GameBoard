################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/custom/TFT/Adafruit_GFX.c \
../drivers/custom/TFT/MCUFRIEND_kbv.c \
../drivers/custom/TFT/TFT_config.c \
../drivers/custom/TFT/glcdfont.c 

OBJS += \
./drivers/custom/TFT/Adafruit_GFX.o \
./drivers/custom/TFT/MCUFRIEND_kbv.o \
./drivers/custom/TFT/TFT_config.o \
./drivers/custom/TFT/glcdfont.o 

C_DEPS += \
./drivers/custom/TFT/Adafruit_GFX.d \
./drivers/custom/TFT/MCUFRIEND_kbv.d \
./drivers/custom/TFT/TFT_config.d \
./drivers/custom/TFT/glcdfont.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/custom/TFT/%.o: ../drivers/custom/TFT/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DCPU_MK64FN1M0VDC12 -DCPU_MK64FN1M0VDC12_cm4 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I../component/serial_manager -I../drivers/custom -I../drivers/custom/TFT -I../drivers -I../device -I../CMSIS -I../CMSIS_driver -I../board -I../component/uart -I../utilities -I../source -I../ -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


