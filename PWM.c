#include "PWM.h"

// [TODO] done?
void LED_Pin_Init(void){
  
	// Enable GPIO Clocks
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; // Enable the clock of GPIO Port A in RCC
	
	// Initialize Green LED
	GPIOA->MODER &= ~GPIO_MODER_MODE5; //clear MODER5
	GPIOA->MODER |= GPIO_MODER_MODE5_1; //set mode to alternative function (10)
	//GPIOA->OTYPER &=~(1UL<<5); //set output type to push pull (0)
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED5; //set I/O output speed to very high output speed (11)
	GPIOA->PUPDR &=~GPIO_PUPDR_PUPD5; //set to no PUPD (00)
	//configure and select the alternative function for PA5
	GPIOA->AFR[0] &=~GPIO_AFRL_AFRL5; //clear the bits
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL5_0; //setting AF of PA5 to TIM2_CH1 is AF1
		
}

void TIM2_CH1_Init(void){
	// Enable the timer clock
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN; // Enable the clock of timer 2 in RCC_APB1ENR1
	TIM2 -> CR1 &= ~TIM_CR1_DIR; // Counting direction: 0 = up-counting, 1 = down-counting
  
	// Prescaler
	TIM2 -> PSC &=~TIM_PSC_PSC; //clear prescaler
	TIM2 -> PSC = 15; // set prescaler value
	
	// Auto-reload
	TIM2 -> ARR &=~TIM_ARR_ARR; // clear auto-reload
	TIM2 -> ARR = 4096; // set auto-reload value for 12 bit range
	
	// Disable output compare mode
	TIM2 -> CCMR1 &=~TIM_CCMR1_OC1M; //clearing the output compare mode bits
	TIM2 -> CCMR1 |= (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2); //setting output compare mode bits to PWM mode 1 which is 0110
	// Output 1 preload enable
	TIM2 -> CCMR1 |= TIM_CCMR1_OC1PE; //since enabling can just or
	// Select output polarity: active high
	TIM2 -> CCER &= ~TIM_CCER_CC1P; //clear bits and setting output polarity to active high (0: OCL1)
  // Enable output for ch1
	TIM2 -> CCER |= TIM_CCER_CC1E; //since enabling can just or
	// Output Compare Register for channel 1
	TIM2 -> CCR1 &=~TIM_CCR1_CCR1; //clear bits
	TIM2 -> CCR1 = 0; //starting at 0
	// Enable counter
	TIM2 -> CR1 |= TIM_CR1_CEN; //enabling the bit so can just or
}
