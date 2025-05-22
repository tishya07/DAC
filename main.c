#include "ADC.h"
#include "DAC.h"
#include "EXTI.h"
#include "PWM.h"
#include "SysClock.h"
#include "stm32l476xx.h"
#include <stdio.h>
volatile uint32_t duty;
volatile uint32_t adc_value;

int main(void) {
    // Initialization
    System_Clock_Init(); // Switch System Clock = 8 MHz

    ADC_Init();
		DAC_Init();
		EXTI_Init();
	
    // [TODO] Initialize PWM
		LED_Pin_Init();
		TIM2_CH1_Init();
	
		


    while (1) {
			// [TODO] Trigger ADC and get result done
			ADC1->CR |= ADC_CR_ADSTART;
			while(!(ADC123_COMMON-> CSR & ADC_CSR_EOC_MST)); // this flag was wrong
			
			adc_value = ADC1->DR;

			// [TODO] LED behavior based on ADC result
			duty = adc_value; // conversion that needs to be done
			
			TIM2->CCR1 = duty;
			
    }
}
