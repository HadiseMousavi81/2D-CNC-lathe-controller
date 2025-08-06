#include "error_manager.h"
#include "Error_interruption.h"
#include "motion.h"
#include "Error_gpioconfig.h"
#include <string.h>
#include <stdio.h>
#include "stm32f103.h"  

#define MAX_WORD_LEN     100 
#define MAX_FEEDRATE     2000
#define PARAM_MAX        260 
#define PARAM_MIN        75

typedef enum {
    ERR_NONE = 0,
    ERR_UNSUPPORTED_MCODE,
    ERR_UNSUPPORTED_GCODE,
    ERR_INVALID_FEEDRATE,
    ERR_OUT_OF_BOUND,
    ERR_EMERGENCY_STOP,
    ERR_NULL_POINTER,
    ERR_BUFFER_OVERFLOW
} CNC_ErrorStates;

/* --- متغیر وضعیت خطا و خارجی‌ها --- */
CNC_ErrorStates currentError = ERR_NONE;

extern uint16_t feedrate;
extern volatile uint16_t step_index;
extern volatile uint16_t word_index;
extern char wordBuf[MAX_WORD_LEN];    // بافر فرمان‌ها
extern uint8_t motion_state;          // از motion.h

/* --- توابع سخت‌افزاری --- */
void Pause_Timers(void){
    TIM1->CR1 &= ~TIM_CR1_CEN;
    TIM2->CR1 &= ~TIM_CR1_CEN;
    TIM3->CR1 &= ~TIM_CR1_CEN;
}

void Disable_Driver(void){
    // فرض: پین‌ها قبلاً در GPIO_Config کانفیگ شده‌اند
    GPIOB->ODR |= (1 << 5);  // PB5 = ENABLE موتور X (active low)
    GPIOB->ODR |= (1 << 6);  // PB6 = ENABLE موتور Y
    GPIOB->ODR |= (1 << 7);  // PB7 = ENABLE موتور Z
}

bool userPressedResetButton(void){
    return ((GPIOC->IDR & (1 << 5)) == 0); // Low = فشرده
}

void ResetBuffer(void){
    word_index = 0;                       // مرحله ۱: صفر کردن ایندکس
    memset((void*)wordBuf, 0, MAX_WORD_LEN);  // مرحله ۲: پاک کردن داده‌ها
}

void ClearError(void){
    currentError = ERR_NONE;
}

/* --- هندلر اصلی خطا --- */
void ErrorHandler(CNC_ErrorStates err){
    currentError = err;

    switch(err) {
        case ERR_UNSUPPORTED_MCODE:
        case ERR_UNSUPPORTED_GCODE:
            Pause_Timers();
            Disable_Driver();
            motion_state = STATE_ERROR;
            break;

        case ERR_INVALID_FEEDRATE:
            Pause_Timers();
            Disable_Driver();
            motion_state = STATE_ERROR;
            break;

        case ERR_OUT_OF_BOUND:
            Pause_Timers();
            Disable_Driver();
            step_index = 0;
            motion_state = STATE_ERROR;
            break;

        case ERR_EMERGENCY_STOP:
            Pause_Timers();
            Disable_Driver();
            motion_state = STATE_ERROR;
            break;

        case ERR_NULL_POINTER:
            Pause_Timers();
            Disable_Driver();
            motion_state = STATE_ERROR;
            // اگر لاگ سریال داری، پیام بده
            printf("Error: NULL pointer detected in G-code\n");
            break;

        case ERR_BUFFER_OVERFLOW:
            Pause_Timers();
            Disable_Driver();
            ResetBuffer();
            motion_state = STATE_ERROR;
            break;

        case ERR_NONE:
            motion_state = STATE_PREPARING;
            break;
    }

    /* --- رفتار صنعتی: تا زمانی که کاربر Reset نزده، در حالت ایمن بمان --- */
    while(currentError != ERR_NONE){
        if(userPressedResetButton()){
            ClearError();
            ResetBuffer();
            motion_state = STATE_IDLE; // بازگشت به حالت امن
        }
    }
}
