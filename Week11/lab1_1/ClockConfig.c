#include <stm32l4xx.h>

//Initialize the clock to 80MHz and SysTick
void ClockInit(void);

int main(void)
{
	ClockInit();
	
	RCC->AHB2ENR = RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOEEN;
	GPIOB->MODER &= ~GPIO_MODER_MODE2_1;
	GPIOE->MODER &= ~GPIO_MODER_MODE8_1;
	
	while (1)
	{
		GPIOB->BSRR = GPIO_BSRR_BS2;
		GPIOE->BSRR = GPIO_BSRR_BS8;
		
		for (int i = 0; i < 1000000; i++);
		
		GPIOB->BSRR = GPIO_BSRR_BR2;
		GPIOE->BSRR = GPIO_BSRR_BR8;
		
		for (int i = 0; i < 1000000; i++);
	}
}

void ClockInit(void)
{
	//Increase the delay by 4 wait states(5 clock cycles) to read the flash
	FLASH->ACR |= FLASH_ACR_LATENCY_4WS;
	
	//Enable PLLR that can be used as the system clock
	//Divide the 16MHz input clock by 2(to 8MHz), multiply by 20(to 160MHz),
	//divide by 2(to 80MHz)
	//Set PLL input source to HSI
	RCC->PLLCFGR = RCC_PLLCFGR_PLLREN | (20 << RCC_PLLCFGR_PLLN_Pos)
							 | RCC_PLLCFGR_PLLM_0 | RCC_PLLCFGR_PLLSRC_HSI;
	
	//Turn on HSI oscillator and PLL circuit.
	RCC->CR |= RCC_CR_PLLON | RCC_CR_HSION;
	
	//Be sure that the wait state of the flash changed,
	//PLL circuit is locked, and HSI is stabilized
	while (!((FLASH->ACR & FLASH_ACR_LATENCY_4WS)
				&& (RCC->CR & RCC_CR_PLLRDY)
				&& (RCC->CR & RCC_CR_HSIRDY)));
	
	//Set the system clock source from PLL
	RCC->CFGR = RCC_CFGR_SW_PLL;
	
	//Turn off MSI to reduce power consumption
	RCC->CR &= ~RCC_CR_MSION;
}
