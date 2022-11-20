#define BUFFERSIZE 10
#include <string.h>
#include "st_basic.h"

char receiveBuffer[BUFFERSIZE] = { };
int bufferIndex = 0;

void Decode(void);

int main(void)
{
	ClockInit();
	USART2_Init();
	GPIO_Init(GPIOB, 2, GPIO_OUTPUT);
	GPIO_Init(GPIOE, 8, GPIO_OUTPUT);
	
	while (1)
	{
		if (bufferIndex + 1 == BUFFERSIZE) Decode();
		else
		{
			char received = USART2_RX();
			if (received == '\r' || received == '\n') Decode();
			else receiveBuffer[bufferIndex++] = received;
		}
	}
}

void Decode(void)
{
	receiveBuffer[bufferIndex] = '\0';
	if (!strcmp(receiveBuffer, "Left")) GPIOB->BSRR = GPIO_BSRR_BS2;
	else if (!strcmp(receiveBuffer, "Right")) GPIOE->BSRR = GPIO_BSRR_BS8;
	else if (!strcmp(receiveBuffer, "Up")) GPIOB->BSRR = GPIO_BSRR_BR2;
	else if (!strcmp(receiveBuffer, "Down")) GPIOE->BSRR = GPIO_BSRR_BR8;
	else if (!strcmp(receiveBuffer, "Center"))
	{
		GPIOB->BSRR = GPIO_BSRR_BR2;
		GPIOE->BSRR = GPIO_BSRR_BR8;
	}
	else USART2_TX_String("Wrong Input!\n");
	
	bufferIndex = 0;
}
