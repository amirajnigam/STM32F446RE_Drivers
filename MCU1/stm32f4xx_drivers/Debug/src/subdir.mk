################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/006_spi1_tx_testing.c 

OBJS += \
./src/006_spi1_tx_testing.o 

C_DEPS += \
./src/006_spi1_tx_testing.d 


# Each subdirectory must supply rules for building sources it contributes
src/006_spi1_tx_testing.o: ../src/006_spi1_tx_testing.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -c -I"D:/Summer 2020/Embedded Software/Wrokspace/MCU1/stm32f4xx_drivers/drivers/Inc" -I../Inc -I"D:/Summer 2020/Embedded Software/Wrokspace/MCU1/stm32f4xx_drivers/drivers/Inc" -O0 -Wall -fstack-usage -MMD -MP -MF"src/006_spi1_tx_testing.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=soft -mthumb -o "$@"

