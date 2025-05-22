#include "EXTI.h"

#include "DAC.h"

void EXTI_Init(void) {
    // [TODO] Configure EXTI for button
	// initialize port c clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN; 
	
	// initialize user button
	GPIOC->MODER &=~(GPIO_MODER_MODE13); //clear bits, set to input
	GPIOC->PUPDR &=~ GPIO_PUPDR_PUPD13; // clear
	GPIOC->PUPDR |= GPIO_PUPDR_PUPD13_1; // set to (10) pull down

	//config SYSCFG EXTI
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; // enable system config controller
	
	SYSCFG->EXTICR[3] &=~SYSCFG_EXTICR4_EXTI13;
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;
	
	// config EXTI trigger
	EXTI->FTSR1 |= EXTI_FTSR1_FT13; // falling edge trigger
	
	// enable EXTI
	EXTI->IMR1 |= EXTI_IMR1_IM13;
	
	// config and enable in NVIC 
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	NVIC_SetPriority(EXTI15_10_IRQn, 0);
}


#define DAC_MIN 0
#define DAC_MAX 4095
#define DAC_INCREMENT 256

static uint32_t dac_value = 0;
static enum {
    DOWN,
    UP,
} direction = UP;

// [TODO] Interrupt handler

void EXTI15_10_IRQHandler(void){
	if((EXTI->PR1 & EXTI_PR1_PIF13) != 0){ // per button press
		if (((dac_value+DAC_INCREMENT)<DAC_MAX) && (direction == UP)){
			dac_value += DAC_INCREMENT;
			DAC_Write_Value(dac_value);
		}
		else if (((dac_value-DAC_INCREMENT)> DAC_MIN) && (direction == DOWN)){
			dac_value -= DAC_INCREMENT;
			DAC_Write_Value(dac_value);
		}


		else if ((dac_value+DAC_INCREMENT)>=DAC_MAX){
			direction = DOWN;
			dac_value -= DAC_INCREMENT;
			DAC_Write_Value(DAC_MAX);
			
		}
		else if ((dac_value-DAC_INCREMENT)<= DAC_MIN){
			direction = UP;
			dac_value += DAC_INCREMENT;
			DAC_Write_Value(DAC_MIN);
		}
		EXTI->PR1 |= EXTI_PR1_PIF13; // clearing interrupt pending bit
	}
}

