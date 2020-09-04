################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/Src/stm32f446xx_gpio_driver.c \
../drivers/Src/stm32f446xx_spi_driver.c 

OBJS += \
./drivers/Src/stm32f446xx_gpio_driver.o \
./drivers/Src/stm32f446xx_spi_driver.o 

C_DEPS += \
./drivers/Src/stm32f446xx_gpio_driver.d \
./drivers/Src/stm32f446xx_spi_driver.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/Src/stm32f446xx_gpio_driver.o: ../drivers/Src/stm32f446xx_gpio_driver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -c -I"D:/Summer 2020/Embedded Software/Wrokspace/MCU1/stm32f4xx_drivers/drivers/Inc" -I../Inc -I"D:/Summer 2020/Embedded Software/Wrokspace/MCU1/stm32f4xx_drivers/drivers/Inc" -O0 -Wall -fstack-usage -MMD -MP -MF"drivers/Src/stm32f446xx_gpio_driver.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=soft -mthumb -o "$@"
drivers/Src/stm32f446xx_spi_driver.o: ../drivers/Src/stm32f446xx_spi_driver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -c -I"D:/Summer 2020/Embedded Software/Wrokspace/MCU1/stm32f4xx_drivers/drivers/Inc" -I../Inc -I"D:/Summer 2020/Embedded Software/Wrokspace/MCU1/stm32f4xx_drivers/drivers/Inc" -O0 -Wall -fstack-usage -MMD -MP -MF"drivers/Src/stm32f446xx_spi_driver.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=soft -mthumb -o "$@"

