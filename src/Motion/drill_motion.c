#include "stm32f103.h"
#include <stdbool.h>
#include <stdlib.h>
#include "drill_motion.h"
#include "drill_utils.h"
#include "motion.h"


#define STEP_PIN     GPIO_ODR_ODR0
#define DIR_PIN      GPIO_ODR_ODR1

// ---- State Machine ----
typedef enum {
    STATE_IDLE,
    STATE_PREPARING,
    STATE_ACCEL,
    STATE_CRUISE,
    STATE_DEACCEL,
    STATE_COMEBACK,
    STATE_DONE
} MotionState;

volatile MotionState motion_state = STATE_IDLE;

// ---- Motion Control Variables ----
volatile uint32_t step_index = 0;
volatile bool update_needed = false;
volatile bool step_state = false;
volatile bool comeback_flag = false;

uint8_t back_index = 0;
uint8_t back_num = 0;
volatile uint32_t peck_depth_q = 0;

// ---- Hardware Init ----
void TIM1_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    TIM1->PSC = Prescaler - 1;
    TIM1->ARR = 1000;
    TIM1->CR1 |= TIM_CR1_ARPE; // preload
    TIM1->DIER |= TIM_DIER_UIE;
    TIM1->CR1 |= TIM_CR1_CEN;
    NVIC_EnableIRQ(TIM1_UP_IRQn);
}

void GPIOC_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    GPIOC->CRL &= ~((0xF << (0*4)) | (0xF << (1*4))); 
    GPIOC->CRL |=  (0x3 << (0*4)) | (0x3 << (1*4));    // Output 50MHz push-pull
}

// ---- ISR: Generate Step Pulse ----
void TIM1_UP_IRQHandler(void) {
    if (TIM1->SR & TIM_SR_UIF) {
        TIM1->SR &= ~TIM_SR_UIF;

        if (!step_state) {  
            GPIOC->ODR |= STEP_PIN;   // Set high  
            step_state = true;  
        } else {  
            GPIOC->ODR &= ~STEP_PIN;  // Set low  
            step_state = false;  
            step_index++;  
            update_needed = true;  
        }  
    }
}

// ---- Motion Update  ----
void Update_DrillMotion(void) {
    if (!update_needed) return;
    update_needed = false;

    switch(motion_state) {
        case STATE_ACCEL:
            if (step_index <= first_phstep_z) {
                TIM1->ARR = Delay_to_counter(Calc_StepDelay(step_index, 0));
            } else {
                motion_state = STATE_CRUISE;
            }
            break;

        case STATE_CRUISE:    
            if (step_index <= Stepz_required * 0.6) {    
                TIM1->ARR = Delay_to_counter(Calc_StepDelay(step_index, 1));    
            } else {    
                motion_state = STATE_DEACCEL;    
            }    
            break;    

        case STATE_DEACCEL:    
            if (step_index <= Stepz_required) {    
                TIM1->ARR = Delay_to_counter(Calc_StepDelay(step_index, 2));    
            } else {    
                motion_state = STATE_COMEBACK;    
                step_index = 0;    // prepare for comeback    
                GPIOC->ODR ^= DIR_PIN; // reverse direction    
            }    
            break;

        case STATE_COMEBACK:
            if (step_index < Stepz_required) {
                TIM1->ARR = Delay_to_counter(Calc_StepDelay(step_index, 1));  // cruise  
            } else {    
                step_index = 0;    
                back_index++;    

                if (back_index >= back_num) {  
                    motion_state = STATE_DONE;  
                } else {  
                    uint32_t current_depth = (back_index + 1) * peck_depth_q;  
                    Stepz_required_calculate(current_depth);  

                    GPIOC->ODR ^= DIR_PIN;    
                    motion_state = STATE_ACCEL;    
                }  
            }  
            break;   

        case STATE_DONE:  
            return;   
            break;  

        default:    
            break;
    }
}

// ---- Example Drill Start ----
void Drill_In(int x2 , int y2 ,int dz, int Feedrate, int q) {
    if (motion_state != STATE_IDLE) return;

    move_to(x2, y2, 1500);

    if(q > 0) {
        peck_depth_q = q;
        Stepz_required_calculate(q);
        back_num = (abs(dz) + q - 1) / q;  //  ceil(dz/q) 
    } else {
        peck_depth_q = abs(dz);
        Stepz_required_calculate(abs(dz));
        back_num = 1;  
    }

    Target_Delay = feedrate_to_delay(Feedrate);
    step_index = 0;
    back_index = 0;
    comeback_flag = false;

    GPIOC->ODR &= ~DIR_PIN; // Direction Down
    motion_state = STATE_ACCEL;
}
