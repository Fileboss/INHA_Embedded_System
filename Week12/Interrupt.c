#include "st_basic.h"

int main(void)
{
	ClockInit();
	USART2_Init();
	GPIO_Init(GPIOA, 0, GPIO_INPUT_PULLDOWN);
	
	NVIC->ISER[EXTI0_IRQn / 32] = (1 << (EXTI0_IRQn % 32));
	EXTI->IMR1 |= EXTI_IMR1_IM0;
	EXTI->RTSR1 |= EXTI_RTSR1_RT0;
	
	while (1)
	{
		USART2_TX_String("I am doing nothing!!!\n");
		Delay(200);
	}
}

void EXTI0_IRQHandler(void)
{
	USART2_TX_String("I got a button input!!!\n");
	EXTI->PR1 |= EXTI_PR1_PIF0;
}
