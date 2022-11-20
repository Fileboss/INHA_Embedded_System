/*
#include "st_basic.h"

int main(void)
{
	ClockInit();
	USART2_Init();
	GPIO_Init(GPIOB, 2, GPIO_OUTPUT);
	
	while (1)
	{
		USART2_TX(USART2_RX());
		
		GPIOB->BSRR = GPIO_BSRR_BS2;
		Delay(1000);
		GPIOB->BSRR = GPIO_BSRR_BR2;
		Delay(1000);
	}
}
*/