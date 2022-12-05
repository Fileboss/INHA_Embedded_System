// This is the second iteration of the final project for the course of Embedded Systems
// In this version, the system is Idle. When a user's hand is detected by the sensor,
// the system will start the engine for 10 seconds. After that, the system will be idle again.

#include "st_basic.h"

//Motor
void Step(int step); // Function to move the stepper motor
const int stepperPin[4] = { 2, 3, 6, 7 }; // Pins for the stepper motor
    const unsigned int stepperFullState[4][4] ={{ 1, 1, 0, 0 },
												{ 0, 1, 1, 0 },
												{ 0, 0, 1, 1 },
												{ 1, 0, 0, 1 } }; // Full step states
const int blowingDurantion = 10000; // Duration of the blowing in milliseconds
void Blow(void) ;
int currentStep = 0;

//sensor
unsigned int InputCapture(void); // input capture function for the ultrasonic sensor
unsigned char flagCaptureMiss = 0; // flag to indicate ths state of the sensor

int main(void)
{
    
    //Initialize the clock
	ClockInit();
    //Initialize the USART2 to communicate with the PC
	USART2_Init();
    
    //Initialize the GPIOA for the stepper motor
	for (int i = 0; i < 4; i++)
        GPIO_Init(GPIOB, stepperPin[i], GPIO_OUTPUT);

	//Ultrasonic GPIO initialization
	GPIO_Init(GPIOC, 14, GPIO_OUTPUT);

	//Initialize the normal distance of the sensor
	unsigned int initialDistance = InputCapture();
	
	while (1)
	{
		USART2_TX_String("The system is idle\n");
		Delay(200);
		// check if the distance has been significantly changed (20% of the initial distance)
		if (InputCapture() < (initialDistance - (initialDistance * 0.2)) || InputCapture() > (initialDistance + (initialDistance * 0.2)))
		{
			Blow();
		}
	}
}

void Blow()
{
	USART2_TX_String("I detected a hand. Starting the fan\n");
    //Start the engine for 10 seconds
	unsigned int prevMillis = getSysMillis();
	while (getSysMillis() - prevMillis <= blowingDurantion)
	{
		Step(1);
	}
	return;
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
}
	unsigned int InputCapture(void)
{
	//Check flagCaptureMiss
	switch (flagCaptureMiss)
	{
		//1 when the capture is timed out and waiting for the rising edge
		case 1:
			//Check if the rising edge has occured
			//In that case, clear the input capture flag and set the state to 2
			if (TIM2->SR & TIM_SR_CC1IF)
			{
				TIM2->SR &= ~TIM_SR_CC1IF;
				flagCaptureMiss = 2;
			}
			
			//After that, return the value as there is no obstacle
			return 500 * 80 * 58;
			
		//2 when the input is high and waiting for the falling edge
		case 2:
			//Check if the falling edge has occured
			//In that case, reset all the flag and get ready for the next input capture
			if (TIM2->SR & TIM_SR_CC1IF)
			{
				TIM2->SR &= ~TIM_SR_CC1IF;
				flagCaptureMiss = 0;
			}
			
			//If not, just return the value as there is no obstacle
			else return 500 * 80 * 58;
			break;
			
		//0 when the capturing is ready
		//In that case, do nothing and proceed the input capture
		default: break;
	}
	
	//Send a pulse to the ultrasonic sensor to get a distance value
	GPIOC->BSRR = GPIO_BSRR_BS14;
	Delay(1);
	GPIOC->BSRR = GPIO_BSRR_BR14;
	
	//Reset the counter value and wait for the rising edge
	//If the rising edge does not appear until 20ms, abort the input capture
	//That is regarded as there is no obstacle
	TIM2->CNT = 0;
	while (!(TIM2->SR & TIM_SR_CC1IF)) if (TIM2->CNT >= 20 * 80 * 1000)
	{
		flagCaptureMiss = 1;
		return 500 * 80 * 58;
	}
	//Ignore the rising edge by clearing the flag
	TIM2->SR &= ~TIM_SR_CC1IF;
	
	//Reset the counter value and wait for the falling edge
	TIM2->CNT = 0;
	while (!(TIM2->SR & TIM_SR_CC1IF));
	
	//Read and return the captured value
	return TIM2->CCR1;
}
