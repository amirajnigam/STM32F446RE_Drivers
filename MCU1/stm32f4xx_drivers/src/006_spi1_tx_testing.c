/*
 * 006_spi1_tx_testing.c
 *
 *  Created on: Aug 12, 2020
 *      Author: amira
 */


/*
 * 006spi_tx_testing.c
 *
 *  Created on: Jul 28, 2020
 *      Author: amira
 */

#include "stm32f446xx.h"
#include<string.h>
#include<stdio.h>

/*
 * PA6- SPI1_MISO
 * PA7- SPI1_MOSI
 * PA5- SPI1_SCLK
 * PA4- SPI1_NSS
 * ALT function mode : 5
 * GPIO Port A
 */

void SPI1_GPIOInits(void)
{
	GPIO_Handle_t SPIPins;

	SPIPins.pGPIOx = GPIOA;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig. GPIO_PinSpeed = GPIO_SPEED_FAST;


	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
	GPIO_Init(&SPIPins); //Pass pointer address of the handle

	//SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GPIO_Init(&SPIPins);

/*
* Note: For this application we don't want to use MISO and NSS because there is no slave.
* 		 So, don't configure those pins and they are free for other users.
*/

//	//MISO
//	SPIPins.GPIO_PinConfig.GPIO_PinNUmber = GPIO_PIN_NO_14;
//	GPIO_Init(&SPIPins);

//	//NSS
//	SPIPins.GPIO_PinConfig.GPIO_PinNUmber = GPIO_PIN_NO_12;
//	GPIO_Init(&SPIPins);

}

void SPI1_Inits(void)
{
	SPI_Handle_t SPI1handle;

	SPI1handle.pSPIx = SPI1;
	SPI1handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI1handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI1handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2; //Generates SCLK of 8MHz
	SPI1handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI1handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI1handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI1handle.SPIConfig.SPI_SSM = SPI_SSM_EN; //Software Slave management Enable for NSS Pin, bcoz we dont have any slave

	SPI_Init(&SPI1handle); //Call SPI init and we have to pass the address of handle
}

int main(void)
{
	char user_data[] = "Hello world";

	//printf("Hello3");
	//This function is used to initialize the GPIO pins to behave as SPI1 pins
	SPI1_GPIOInits();
	//printf("Hello4");
	//This function is used to initialize the SPI1 peripheral parameters
	SPI1_Inits();

	//This makes NSS signal internally high and avoids MODF error
	SPI_SSIConfig(SPI1,ENABLE);

	//enable the SPI1 peripheral
	SPI_PeripheralControl(SPI1,ENABLE);

	SPI_SendData(SPI1,(uint8_t*)user_data, strlen(user_data));

	//lets confirm SPI is not busy, 0 is not busy and 1 is busy
	//while(SPI_GetFlagStatus(SPI1,SPI_BSY_FLAG));

	//disable the SPI1 peripheral
	SPI_PeripheralControl(SPI1,DISABLE);

	while(1); //Infinite while loop to hang the application
	return 0;
}



/* Note: Remember Here we used NSS enable(software slave management is enabled). For master the NSS signal should
 * be tied to +Vcc when not used to avoid MODF error which happens in multi master situation.
 * So, let's make SSI = 1 to tie NSS to +Vcc internally
 *
 * Remember: SSI bit influence NSS state when SSM =1
 *
 * By default SSI = 0, So NSS will be pulled low which is not acceptable for master when working in non multi master situation
 *
 */

