#include "stm32f446xx.h"

int main()
{
	return 0;
}

void EXTI0_IRQHandler(void)//ISR implenmentation
{
	//handle the interrupt
	GPIO_IRQHandling(0);
}
