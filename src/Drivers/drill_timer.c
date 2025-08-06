#include "drill_timer.h"
#include "drill_gpio.h"

volatile bool step_state = false;

void TIM1_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    TIM1->PSC = Prescaler - 1;
    TIM1->ARR = 1000;
    TIM1->CR1 |= TIM_CR1_ARPE; 
    TIM1->DIER |= TIM_DIER_UIE;
    TIM1->CR1 |= TIM_CR1_CEN;
    NVIC_EnableIRQ(TIM1_UP_IRQn);
}

void TIM1_UP_IRQHandler(void) {
    if (TIM1->SR & TIM_SR_UIF) {
        TIM1->SR &= ~TIM_SR_UIF;

        if (!step_state) {  
            GPIOC->ODR |= STEP_PIN;  
            step_state = true;  
        } else {  
            GPIOC->ODR &= ~STEP_PIN;  
            step_state = false;  
            step_index++;  
            update_needed = true;  
        }  
    }
}
