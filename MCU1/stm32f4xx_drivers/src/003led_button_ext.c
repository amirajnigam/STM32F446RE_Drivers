#include "stm32f446xx.h"
#include "stm32f446xx_gpio_driver.h"

/*
 * Connect External Push button to PB12
 * Connrect external LED to PA14
 */


#define		LOW			0
#define		BTN_PRESSED LOW

void delay(void)
{
	for(uint32_t i = 0; i < 900000/2; i++);
}

int main(void)
{
	GPIO_Handle_t GpioLed, GPIOBtn;

	//this is led gpio configuration
	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8;
	GpioLed.GPIO_PinConfig.GPIO_PinMode =   GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed  = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl= GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOA, ENABLE);

	GPIO_Init(&GpioLed);
	/*
	 * Note: No Open drain or Push pull pin configuration because push button already has pull up resistor.
	 */

	//this is btn gpio configuration
	GPIOBtn.pGPIOx = GPIOB;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode =   GPIO_MODE_IN;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed  = GPIO_SPEED_FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl= GPIO_PIN_PU; //using internal pull up

	GPIO_PeriClockControl(GPIOB, ENABLE);

	GPIO_Init(&GPIOBtn);
	//GPIO_WriteToOutputPort(GPIOA,1);

	while(1)
	{
		if(GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_12) == BTN_PRESSED)
		{
			delay();	//When button is pressed, it will wait until the debouncing of button gets over.Otherwise loop will execute multiple times.
			GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_8);
		}
	}
	return 0;
}


