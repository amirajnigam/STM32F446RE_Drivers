#include "stm32f446xx_spi_driver.h"

/******************************************************************************
 * @fn              - SPI_PeriClockControl
 *
 * @brief           -
 *
 * @param[in]       -
 * @param[in]       -
 *
 *
 * @return          -
 *
 *
 * @Note            -
 *
 */



void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}
		else if(pSPIx == SPI2)
		{
			SPI2_PCLK_EN();
		}
		else if(pSPIx == SPI3)
		{
			SPI3_PCLK_EN();
		}
	}
	else
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_DI();
		}
		else if(pSPIx == SPI2)
		{
			SPI2_PCLK_DI();
		}
		else if(pSPIx == SPI3)
		{
			SPI3_PCLK_DI();
		}
	}
}


/*Init and De-init*/
/******************************************************************************
 * @fn              - SPI_Init
 *
 * @brief           - need to configure the CR1 register
 *
 * @param[in]       -
 * @param[in]       -
 *
 *
 * @return          -
 *
 *
 * @Note            -
 *
 */
void SPI_Init(SPI_Handle_t *pSPIHandle)
{

	//peripheral clock enable
	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);

	//first lets configure the SPI_CR1 register
	uint32_t tempreg = 0;

	//1. configure the device mode
	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode << 2;   //Shift to 2nd bit position

	//2. configure the bus config
	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		//bidi mode should be cleared
		tempreg &= ~(1<<15);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		//bidi mode should be set
		tempreg |= (1<<15);
	}else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY )
	{
		//BIDI mode should be cleared
		tempreg &= ~(1<<15);

		//RXONLY bit must be set
		tempreg |= (1<<10);
	}

	//3. Configure the SPI serial clock speed(baud rate)
	tempreg |= pSPIHandle->SPIConfig.SPI_SclkSpeed << 3;

	//4. Configure the DFF

	tempreg |= pSPIHandle->SPIConfig.SPI_DFF <<11;

	//5. Configure the CPOL

	tempreg |= pSPIHandle->SPIConfig.SPI_CPOL << 2;

	//6. Configure the CPHA

	tempreg |= pSPIHandle->SPIConfig.SPI_CPHA << 0;
}

/******************************************************************************
 * @fn              - SPI_DeInit
 *
 * @brief           -
 *
 * @param[in]       -
 * @param[in]       -
 *
 *
 * @return          -
 *
 *
 * @Note            -
 *
 */

void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
	if(pSPIx == SPI1)
	{
		SPI1_REG_RESET();
	}else if(pSPIx == SPI2)
	{
		SPI2_REG_RESET();
	}else if(pSPIx == SPI3)
	{
		SPI3_REG_RESET();
	}
}



uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx,uint32_t FlagName)
{
	if(pSPIx->SR & FlagName) // if flag is set then if condition will be true
	{
		return FLAG_SET; // In this function we are testing the SR register AND WE ARE TESTING THE BIT POSITION OF THE FLAG WE RECIEVE HERE.
	}
	return FLAG_RESET;
}

/******************************************************************************
 * @fn              - SPI_SendData
 *
 * @brief           -
 *
 * @param[in]       - Base address of the SPI peripheral
 * @param[in]       - Pointer to data
 * @param[in]       - No of bytes transferred
 *
 * @return          -
 *
 *
 * @Note            - This is a blocking Call, because we can see here until all the bytes have been transferred,
 * 					  this function will block. There are 2 while loops. Eg lets say length is 1000 bytes so until all the
 * 					  100 bytes are transferred this function will not return.
 * @Note			- This is also called polling based code, polling tpe API function
 *
 *
 */

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
	while(Len > 0)
	{
		//1. Wait until TXE is set
		while(SPI_GetFlagStatus(pSPIx,SPI_TXE_FLAG) == FLAG_RESET); //while(0) loop will not hang here it means Tx buffer is empty and it can recieve data and we will go to 2nd step

		//2. Check the DFF bit in CR1
		if((pSPIx->CR1 & (1 << SPI_CR1_DFF)))
		{
			//16 bit data
			//Load the data in to the DR
			pSPIx->DR = *((uint16_t*)pTxBuffer);			// type casted into 16 bit buffer and the dereferenced it.
			Len--;
			Len--;
			(uint16_t*)pTxBuffer++;						//We have to increment Tx buffer in order to make it point to the next data item
		}else
		{
			//8 bit data
			//Load the data into the DR
			pSPIx-> DR = *pTxBuffer;				    //dereferencing the pointer to 8 bit of data buffer
			Len--;
			pTxBuffer++;							   //We have to increment Tx buffer in order to make it point to the next data item
		}

	}
}

/******************************************************************************
 * @fn              - SPI_RecieveData
 *
 * @brief           -
 *
 * @param[in]       -
 * @param[in]       -
 *
 *
 * @return          -
 *
 *
 * @Note            -
 *
 */
void SPI_RecieveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len)
{

}

/******************************************************************************
 * @fn              - SPI_PeripheralControl
 *
 * @brief           -
 *
 * @param[in]       -
 * @param[in]       -
 *
 *
 * @return          -
 *
 *
 * @Note            -
 *
 */


void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);//Enable the peripheral
	}else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);//Disable the peripheral
	}
}

/******************************************************************************
 * @fn              - SPI_SSIConfig
 *
 * @brief           -
 *
 * @param[in]       -
 * @param[in]       -
 *
 *
 * @return          -
 *
 *
 * @Note            -
 *
 */
void SPI_SSIConfig(SPI_RegDef_t *pSPIx,uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SSI);
	}else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
	}
}



/******************************************************************************
 * @fn              - SPI_SSOEConfig
 *
 * @brief           -
 *
 * @param[in]       -
 * @param[in]       -
 *
 *
 * @return          -
 *
 *
 * @Note            -
 *
 */
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx,uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pSPIx->CR2 |= (1 << SPI_CR2_SSOE);
	}else
	{
		pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE);
	}
}




/* IRQ Configuration and ISR handling*/
/******************************************************************************
 * @fn              - SPI_IRQInterruptConfig
 *
 * @brief           -
 *
 * @param[in]       -
 * @param[in]       -
 *
 *
 * @return          -
 *
 *
 * @Note            -
 *
 */

void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{

}
/******************************************************************************
 * @fn              - SPI_IRQPriorityConfig
 *
 * @brief           -
 *
 * @param[in]       -
 * @param[in]       -
 *
 *
 * @return          -
 *
 *
 * @Note            -
 *
 */
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){

}
/******************************************************************************
 * @fn              - SPI_IRQHandling
 *
 * @brief           -
 *
 * @param[in]       -
 * @param[in]       -
 *
 *
 * @return          -
 *
 *
 * @Note            -
 *
 */
void SPI_IRQHandling(SPI_Handle_t *pHandle){

}
