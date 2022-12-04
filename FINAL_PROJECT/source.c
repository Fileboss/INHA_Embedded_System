// This is the first iteration of the final project for the course of Embedded Systems
// In this version, the system is Idle. When a button of the joystick is pressed, 
// the system will start the engine for 10 seconds. After that, the system will be idle again.
// We will use an interrupt to start the engine and a timer to stop it after 10 seconds.

#include "st_basic.h"

void Step(int step); // Function to move the stepper motor

int main(void)
{
    const int stepperPin[4] = { 2, 3, 6, 7 }; // Pins for the stepper motor
    const unsigned int stepperFullState[4][4] ={{ 1, 1, 0, 0 },
												{ 0, 1, 1, 0 },
												{ 0, 0, 1, 1 },
												{ 1, 0, 0, 1 } }; // Full step states

    int currentStep = 0;
    void Step(int step);


    //Initialize the clock
	ClockInit();
    //Initialize the USART2 to communicate with the PC
	USART2_Init();
    //Initialize the GPIOA
	GPIO_Init(GPIOA, 0, GPIO_INPUT_PULLDOWN); 
    GPIO_Init(GPIOA, 1, GPIO_INPUT_PULLDOWN);
	GPIO_Init(GPIOA, 2, GPIO_INPUT_PULLDOWN);
	for (int i = 0; i < 4; i++)
        GPIO_Init(GPIOB, stepperPin[i], GPIO_OUTPUT);
	
	NVIC->ISER[EXTI0_IRQn / 32] = (1 << (EXTI0_IRQn % 32)); //Enable the interrupt
	EXTI->IMR1 |= EXTI_IMR1_IM0; 
	EXTI->RTSR1 |= EXTI_RTSR1_RT0; 
	
	while (1)
	{
		USART2_TX_String("The system is idle\n");
		Delay(2000);
	}
}

void EXTI0_IRQHandler(void)
{
	USART2_TX_String("I got a button input. Starting the fan\n");
    //Start the engine for 10 seconds
    Step(1); // Move the stepper motor
    Delay(10000); // Wait 10 seconds
    Step(0); // Stop the stepper motor
    //Stop the engine

	EXTI->PR1 |= EXTI_PR1_PIF0;
}

void Step(int step)
{
	int direction = (step > 0) ? 1 : -1;
	while (step != 0)
	{
		#ifdef FULL_STEP
		currentStep = (currentStep + direction + 4) % 4;
		#elif defined HALF_STEP
		currentStep = (currentStep + direction + 8) % 8;
		#endif
		
		for (int i = 0; i < 4; i++)
		{
			#ifdef FULL_STEP
			GPIOB->BSRR = (stepperFullState[currentStep][i] << stepperPin[i]);
			GPIOB->BSRR = (!stepperFullState[currentStep][i] << (stepperPin[i] + 16));
			#elif defined HALF_STEP
			GPIOB->BSRR = (stepperHalfState[currentStep][i] << stepperPin[i]);
			GPIOB->BSRR = (!stepperHalfState[currentStep][i] << (stepperPin[i] + 16));
			#endif
		}
		
		step -= direction;
		Delay(2);
	}