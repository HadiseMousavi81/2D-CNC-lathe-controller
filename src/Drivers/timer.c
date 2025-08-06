// Drivers/timer.c
#include "Drivers/timer.h"





void TIM3_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    TIM3->PSC = Prescaler - 1;
    TIM3->ARR = 1000;
    TIM3->CR1 |= TIM_CR1_ARPE; // preload
    TIM3->CR1 |= TIM_CR1_CEN;
    TIM3->DIER |= TIM_DIER_CC1IE;
    NVIC_EnableIRQ(TIM3_IRQn);
}
