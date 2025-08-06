// Drivers/stepgen.c
#include "drivers/stepgen.h"
#include "config.h"
#include "Drivers/gpio.h"




volatile uint32_t step_index = 0;
bool update_neededed = false;
volatile bool step_state_x = false;
volatile bool step_state_y = false;



// ---- ISR: Generate Step  Pulse 

void TIM3_UP_IRQHandler(void) {
    if (!(TIM3->SR & TIM_SR_UIF)) return;
    TIM3->SR &= ~TIM_SR_UIF;

    // --- تولید پالس برای محور X ---
    if (step_state_x) {
        GPIOA->ODR &= ~STEP_X_PIN;   // Falling edge
        step_state_x = false;
    } else {
        GPIOA->ODR |= STEP_X_PIN;    // Rising edge
        step_state_x = true;
    }

    // --- تولید پالس برای محور Y ---
    if (step_state_y) {
        GPIOB->ODR &= ~STEP_Y_PIN;   // Falling edge
        step_state_y = false;
    } else {
        GPIOB->ODR |= STEP_Y_PIN;    // Rising edge
        step_state_y = true;
    }

    // --- الگوریتم Bresenham ---
    if (x_is_primary) {
        if (err <= 0) {
            // فقط X Step می‌زند
            err += 2 * dy;
            step_state_x = false;  // آماده پالس بعدی
            step_state_y = true;   // Y غیر فعال
        } else {
            // X و Y هر دو Step می‌زنند
            err -= 2 * dx;
            step_state_x = false;  // آماده پالس بعدی
            step_state_y = false;  // آماده پالس بعدی
        }
    } else {
        if (err <= 0) {
            // فقط Y Step می‌زند
            err += 2 * dx;
            step_state_x = true;   // X غیر فعال
            step_state_y = false;  // آماده پالس بعدی
        } else {
            // Y و X هر دو Step می‌زنند
            err -= 2 * dy;
            step_state_x = false;  // آماده پالس بعدی
            step_state_y = false;  // آماده پالس بعدی
        }
    }

    step_index++;
    update_needed = true;
}