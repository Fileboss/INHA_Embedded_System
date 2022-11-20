/*
#include "st_basic.h"

unsigned char isPushed = 0;

int main(void)
{
	ClockInit();
	USART2_Init();
	
	GPIO_Init(GPIOA, 0, GPIO_INPUT_PULLDOWN);
	GPIO_Init(GPIOA, 1, GPIO_INPUT_PULLDOWN);
	GPIO_Init(GPIOA, 2, GPIO_INPUT_PULLDOWN);
	GPIO_Init(GPIOA, 3, GPIO_INPUT_PULLDOWN);
	GPIO_Init(GPIOA, 5, GPIO_INPUT_PULLDOWN);
	
	while (1)
	{
		if (GPIOA->IDR & GPIO_IDR_ID1) {
			if (!isPushed) {
				USART2_TX_String("Left Button Pushed!\n");
				isPushed = 1;
			}
		}
		else if (GPIOA->IDR & GPIO_IDR_ID2) {
			if (!isPushed) {
				USART2_TX_String("Right Button Pushed!\n");
				isPushed = 1;
			}
		}
		else if (GPIOA->IDR & GPIO_IDR_ID3) {
			if (!isPushed) {
				USART2_TX_String("Up Button Pushed!\n");
				isPushed = 1;
			}
		}
		else if (GPIOA->IDR & GPIO_IDR_ID5) {
			if (!isPushed) {
				USART2_TX_String("Down Button Pushed!\n");
				isPushed = 1;
			}
		}
		else if (GPIOA->IDR & GPIO_IDR_ID0) {
			if (!isPushed) {
				USART2_TX_String("Center Button Pushed!\n");
				isPushed = 1;
			}
		}
		else isPushed = 0;
	}
}
*/
