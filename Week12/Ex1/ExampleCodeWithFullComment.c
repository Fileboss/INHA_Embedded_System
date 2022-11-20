#include <stm32l4xx.h>

int main(void)
{
    //Enable the clock of GPIOB and GPIOE
	RCC->AHB2ENR = RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOEEN;
    //Set the mode of PB2 and PE8 to output by clearing MODEx_1
	GPIOB->MODER &= ~GPIO_MODER_MODE2_1;
	GPIOE->MODER &= ~GPIO_MODER_MODE8_1;
	
	while (1)
	{
        //Atomic set of PB2 and PE8
		GPIOB->BSRR = GPIO_BSRR_BS2;
		GPIOE->BSRR = GPIO_BSRR_BS8;
		
        //Delay for a little
		for (int i = 0; i < 1000000; i++);
		
        //Atomic reset of PB2 and PE8
		GPIOB->BSRR = GPIO_BSRR_BR2;
		GPIOE->BSRR = GPIO_BSRR_BR8;
		
        //Delay for a little
		for (int i = 0; i < 1000000; i++);
	}
}
