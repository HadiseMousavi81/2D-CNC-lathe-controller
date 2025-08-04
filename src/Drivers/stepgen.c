// Drivers/stepgen.c
#include "drivers/stepgen.h"
#include "config.h"
#include "Drivers/gpio.h"




volatile uint32_t step_index = 0;
bool update_neededx = false;
bool update_neededy = false;




// ---- ISR: Generate Step X Pulse ----
volatile bool step_statex = false;

void TIM2_UP_IRQHandler(void) {
    if (TIM2->SR & TIM_SR_UIF) {
        TIM2->SR &= ~TIM_SR_UIF;

        if (!step_state) {
            GPIOA->ODR |= STEP_PIN;   // Set high
            step_statex = true;
        } else {
            GPIOA->ODR &= ~STEP_PIN;  // Set low
            step_statex = false;
            step_index++;
            update_neededx = true;
        }
    }
}


// ---- ISR: Generate Step Y Pulse ----
volatile bool step_statey = false;

void TIM3_UP_IRQHandler(void) {
    if (TIM3->SR & TIM_SR_UIF) {
        TIM3->SR &= ~TIM_SR_UIF;

        if (!step_statey) {
            GPIOB->ODR |= STEP_PIN;   // Set high
            step_state = true;
        } else {
            GPIOB->ODR &= ~STEP_PIN;  // Set low
            step_statey = false;
            step_index++;
            update_neededy = true;
        }
    }
}}