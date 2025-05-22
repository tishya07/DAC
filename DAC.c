#include "stm32l476xx.h"

static void DAC_Pin_Init(void) {
	// [TODO] -> Done, need to check
	// Enable the clock of GPIO Port A in RCC
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	GPIOA->MODER &= ~(GPIO_MODER_MODE4);
	GPIOA->MODER |= GPIO_MODER_MODE4;		//analog mode
	
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD1);		//no pull up, no pull down
}


void DAC_Write_Value(uint32_t value) {
   // [TODO] Write DAC1Ch1 right-aligned 12-bit value -> Done, need to test
	DAC->DHR12R1 &=~ DAC_DHR12R1_DACC1DHR; // lower bits clear
	DAC->DHR12R1 |= value; // since bits 0-11 are allocated
	DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG1;
}

void DAC_Init(void) {
    DAC_Pin_Init();

    // [TODO] Enable DAC clock
		RCC->APB1ENR1 |= RCC_APB1ENR1_DAC1EN;
		DAC->CR &=~DAC_CR_EN1; // 0 is channel 1 disabled

    // [TODO] Enable software trigger mode
		DAC->CR |= DAC_CR_TSEL1; // (111) = software trigger 
	
		// [TODO] Disable trigger
		DAC->CR |= DAC_CR_TEN1; // 1 is enabled

		// [TODO] DAC1 connected in normal mode to external pin only with buffer enabled
		DAC->MCR &=~ DAC_MCR_MODE1; // (000) = normal mode to external pin w/ buffer enabled 

		// [TODO] Enable DAC channel 1
		DAC->CR |= DAC_CR_EN1; // 1 is channel 1 enabled 

    DAC_Write_Value(0);
}
