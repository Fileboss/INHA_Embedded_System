/*
#include "st_basic.h"

const char keypad[16] = { '1', '2', '3', 'A',
	                        '4', '5', '6', 'B',
	                        '7', '8', '9', 'C',
	                        '*', '0', '#', 'D' };

unsigned char isPushed[16] = { };

int main(void)
{
	ClockInit();
	USART2_Init();
	
	for (int i = 0; i <= 3; i++) GPIO_Init(GPIOA, i, GPIO_INPUT_PULLDOWN);
	
	while (1)
	{
		for (int i = 0; i < 4; i++)
		{
			GPIOE->BSRR |= (1 << ((i - 1 + 4) % 4 + 12 + 16));
			Delay(1);
			GPIO_Init(GPIOE, (i - 1 + 4) % 4 + 12, GPIO_ANALOG);
			
			GPIO_Init(GPIOE, i + 12, GPIO_OUTPUT);
			GPIOE->BSRR |= (1 << (i + 12));
			Delay(1);
			
			for (int j = 0; j < 4; j++)
			{
				if (GPIOA->IDR & (1 << j))
				{
					if (!isPushed[4 * i + j])
					{
						USART2_TX(keypad[4 * i + j]);
						USART2_TX('\n');
						isPushed[4 * i + j] = 1;
					}
				}
				
				else isPushed[4 * i + j] = 0;
			}
		}
	}
}
*/
