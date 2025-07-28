// Drivers/timer.c
#include "timer.h"

void TIM2_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    TIM2->PSC = Prescaler - 1;
    TIM2->ARR = 1000;
    TIM2->CR1 |= TIM_CR1_CEN;
    TIM2->DIER |= TIM_DIER_CC1IE;
    NVIC_EnableIRQ(TIM2_IRQn);
}

void TIM3_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    TIM3->PSC = Prescaler - 1;
    TIM3->ARR = 1000;
    TIM3->CR1 |= TIM_CR1_CEN;
    TIM3->DIER |= TIM_DIER_CC1IE;
    NVIC_EnableIRQ(TIM3_IRQn);
}
