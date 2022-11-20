/*
#include "st_basic.h"

int main(void)
{
	ClockInit();
	USART2_Init();
	GPIO_Init(GPIOB, 2, GPIO_OUTPUT);
	
	NVIC->ISER[USART2_IRQn / 32] = (1 << (USART2_IRQn % 32));
	USART2->CR1 |= USART_CR1_RXNEIE;
	
	while (1)
	{
		GPIOB->BSRR = GPIO_BSRR_BS2;
		Delay(1000);
		GPIOB->BSRR = GPIO_BSRR_BR2;
		Delay(1000);
	}
}

void USART2_IRQHandler(void)
{
	USART2_TX(USART2_RX());
}
*/