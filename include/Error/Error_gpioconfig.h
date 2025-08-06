#ifndef ERROR_GPIOCONFIG_H
#define ERROR_GPIOCONFIG_H

#include "stm32f103.h" 

// مقداردهی اولیه GPIO برای دکمه ریست خطا
void Reset_ButtonError_GPIO(void);

// مقداردهی اولیه لیمیت‌سوییچ‌ها
void LimitSwitch_GPIO_Init(void);

// تابع راه‌اندازی وقفه دکمه اضطراری (Emergency Stop)
void EmergencyStop_GPIO_Init(void) ;

#endif // ERROR_GPIOCONFIG_H