// Based on the previous Lab sessions, write a program that will
// turn on the motor for 5 sec when the sensor detects an object

// The 

#include "st_basic.h"

int main(void)
{
    ClockInit();
    GPIO_Init(GPIOA, 0, GPIO_INPUT_PULLDOWN);
    GPIO_Init(GPIOB, 0, GPIO_OUTPUT);
    
    while (1)
    {
        if (GPIOA->IDR & (1 << 0))
        {
            GPIOB->BSRR = GPIO_BSRR_BS0;
            Delay(5000);
            GPIOB->BSRR = GPIO_BSRR_BR0;
        }
    }
}

