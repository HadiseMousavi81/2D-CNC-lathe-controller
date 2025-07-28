// Drivers/stepgen.c
#include "stepgen.h"
#include "config.h"

volatile uint32_t step_index = 0;
bool update_needed = false;
int step_state = 0;
int step_statey = 0;

void Step_x() {
    GPIOA->ODR |= GPIO_ODR_ODR0;
    step_state = 0;
}

void Step_y() {
    GPIOB->ODR |= GPIO_ODR_ODR0;
    step_statey = 0;
}

void TIM2_IRQHandler(void) {
    if (TIM2->SR & TIM_SR_CC1IF) {
        TIM2->SR &= ~TIM_SR_CC1IF;
        if (step_state == 0) {
            GPIOA->ODR &= ~GPIO_ODR_ODR0;
            step_index++;
            update_needed = true;
        }
    }
}

void TIM3_IRQHandler(void) {
    if (TIM3->SR & TIM_SR_CC1IF) {
        TIM3->SR &= ~TIM_SR_CC1IF;
        if (step_statey == 0) {
            GPIOB->ODR &= ~GPIO_ODR_ODR0;
            step_index++;
            update_needed = true;
        }
    }
}