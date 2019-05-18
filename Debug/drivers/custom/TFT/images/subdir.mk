################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/custom/TFT/images/Background.c \
../drivers/custom/TFT/images/Background_1.c \
../drivers/custom/TFT/images/Background_2.c \
../drivers/custom/TFT/images/BirdOne.c \
../drivers/custom/TFT/images/BirdThree.c \
../drivers/custom/TFT/images/BirdTwo.c \
../drivers/custom/TFT/images/BlockOne.c \
../drivers/custom/TFT/images/BlockThree.c \
../drivers/custom/TFT/images/BlockTwo.c \
../drivers/custom/TFT/images/Caratula1.c \
../drivers/custom/TFT/images/Caratula2.c \
../drivers/custom/TFT/images/Caratula3.c \
../drivers/custom/TFT/images/DustFour.c \
../drivers/custom/TFT/images/DustOne.c \
../drivers/custom/TFT/images/DustThree.c \
../drivers/custom/TFT/images/DustTwo.c \
../drivers/custom/TFT/images/PigOne.c \
../drivers/custom/TFT/images/PigThree.c \
../drivers/custom/TFT/images/PigTwo.c \
../drivers/custom/TFT/images/white.c 

OBJS += \
./drivers/custom/TFT/images/Background.o \
./drivers/custom/TFT/images/Background_1.o \
./drivers/custom/TFT/images/Background_2.o \
./drivers/custom/TFT/images/BirdOne.o \
./drivers/custom/TFT/images/BirdThree.o \
./drivers/custom/TFT/images/BirdTwo.o \
./drivers/custom/TFT/images/BlockOne.o \
./drivers/custom/TFT/images/BlockThree.o \
./drivers/custom/TFT/images/BlockTwo.o \
./drivers/custom/TFT/images/Caratula1.o \
./drivers/custom/TFT/images/Caratula2.o \
./drivers/custom/TFT/images/Caratula3.o \
./drivers/custom/TFT/images/DustFour.o \
./drivers/custom/TFT/images/DustOne.o \
./drivers/custom/TFT/images/DustThree.o \
./drivers/custom/TFT/images/DustTwo.o \
./drivers/custom/TFT/images/PigOne.o \
./drivers/custom/TFT/images/PigThree.o \
./drivers/custom/TFT/images/PigTwo.o \
./drivers/custom/TFT/images/white.o 

C_DEPS += \
./drivers/custom/TFT/images/Background.d \
./drivers/custom/TFT/images/Background_1.d \
./drivers/custom/TFT/images/Background_2.d \
./drivers/custom/TFT/images/BirdOne.d \
./drivers/custom/TFT/images/BirdThree.d \
./drivers/custom/TFT/images/BirdTwo.d \
./drivers/custom/TFT/images/BlockOne.d \
./drivers/custom/TFT/images/BlockThree.d \
./drivers/custom/TFT/images/BlockTwo.d \
./drivers/custom/TFT/images/Caratula1.d \
./drivers/custom/TFT/images/Caratula2.d \
./drivers/custom/TFT/images/Caratula3.d \
./drivers/custom/TFT/images/DustFour.d \
./drivers/custom/TFT/images/DustOne.d \
./drivers/custom/TFT/images/DustThree.d \
./drivers/custom/TFT/images/DustTwo.d \
./drivers/custom/TFT/images/PigOne.d \
./drivers/custom/TFT/images/PigThree.d \
./drivers/custom/TFT/images/PigTwo.d \
./drivers/custom/TFT/images/white.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/custom/TFT/images/%.o: ../drivers/custom/TFT/images/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DCPU_MK64FN1M0VDC12 -DCPU_MK64FN1M0VDC12_cm4 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I../component/serial_manager -I../drivers/custom -I../drivers/custom/TFT -I../drivers -I../device -I../CMSIS -I../CMSIS_driver -I../board -I../component/uart -I../utilities -I../source -I../ -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


