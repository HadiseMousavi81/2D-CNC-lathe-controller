#ifndef ERROR_INTERRUPTION_H
#define ERROR_INTERRUPTION_H

#include "stm32f10x.h" 
#include "error_handler.h" 
#include <stdint.h>

// راه‌اندازی وقفه‌های لیمیت‌سوییچ روی PA5، PA6، PA7
void Limit_Switch_InterruptInit(void);

void EXTI9_5_IRQHandler(void) ;

void Emergency_Stop_InterruptInit(void);

// تابع وقفه مربوط به EXTI3 (Emergency Stop)
void EXTI3_IRQHandler(void);

#endif // ERROR_INTERRUPTION_H