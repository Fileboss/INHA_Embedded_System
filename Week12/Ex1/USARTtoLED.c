/*
#include "st_basic.h"

int main(void)
{
	ClockInit();
	USART2_Init();
	GPIO_Init(GPIOB, 2, GPIO_OUTPUT);
	GPIO_Init(GPIOE, 8, GPIO_OUTPUT);
	
	while (1)
	{
		switch (USART2_RX())
		{
			case 'a':
				GPIOB->BSRR = GPIO_BSRR_BS2;
				break;
			case 'd':
				GPIOE->BSRR = GPIO_BSRR_BS8;
				break;
			case 'w':
				GPIOB->BSRR = GPIO_BSRR_BR2;
				break;
			case 's':
				GPIOE->BSRR = GPIO_BSRR_BR8;
				break;
			case ' ':
				GPIOB->BSRR = GPIO_BSRR_BR2;
				GPIOE->BSRR = GPIO_BSRR_BR8;
				break;
		}
	}
}
*/
