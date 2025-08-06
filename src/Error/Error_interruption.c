#include "Error_interruption.h"

void Limit_Switch_InterruptInit(void) {
// فعال‌سازی کلاک AFIO (در صورت نیاز)
RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

// تنظیم EXTI5/6/7 به پورت A (AFIO_EXTICR2 برای خطوط 4 تا 7)
AFIO->EXTICR[1] &= ~((0xF << 0) | (0xF << 4) | (0xF << 8));  // پاک کردن بیت‌های EXTI5/6/7
// به‌طور پیش‌فرض به PA وصل است، اما این خط باعث اطمینان بیشتر می‌شود

// فعال‌سازی ماسک وقفه (Interrupt Mask Register)
EXTI->IMR |= (1 << 5) | (1 << 6) | (1 << 7);

// فعال‌سازی لبه بالا رونده
EXTI->RTSR |= (1 << 5) | (1 << 6) | (1 << 7);

// اطمینان از غیرفعال بودن لبه پایین‌رونده
EXTI->FTSR &= ~((1 << 5) | (1 << 6) | (1 << 7));

// فعال‌سازی وقفه EXTI خطوط 5 تا 9
NVIC_SetPriority(EXTI9_5_IRQn, 1);
NVIC_EnableIRQ(EXTI9_5_IRQn);

}

// هندلر وقفه: لیمیت‌سوییچ محورهای X, Y, Z
void EXTI9_5_IRQHandler(void) {
if (EXTI->PR & (1 << 5)) {
EXTI->PR |= (1 << 5); 
ErrorHandler(ERR_LIMIT_X); // هندل خطای محور X
}

if (EXTI->PR & (1 << 6)) {
    EXTI->PR |= (1 << 6);
    ErrorHandler(ERR_LIMIT_Y);
}

if (EXTI->PR & (1 << 7)) {
    EXTI->PR |= (1 << 7);
    ErrorHandler(ERR_LIMIT_Z);
}

}

void Emergency_Stop_InterruptInit(void) {
// فعال‌سازی کلاک AFIO
RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

// اتصال EXTI3 به PA3
AFIO->EXTICR[0] &= ~(0xF << (3 * 4)); // EXTICR[0]، بیت‌های [15:12] برای EXTI3 = PA

// تنظیمات وقفه EXTI3
EXTI->IMR  |= (1 << 3);   // فعال‌سازی ماسک وقفه
EXTI->FTSR |= (1 << 3);   // لبه پایین‌رونده
EXTI->RTSR &= ~(1 << 3);  // اختیاری: غیرفعال‌سازی لبه بالا‌رونده

// فعال‌سازی وقفه در NVIC
NVIC_EnableIRQ(EXTI3_IRQn);

}

void EXTI3_IRQHandler(void) {
if (EXTI->PR & (1 << 3)) {
EXTI->PR |= (1 << 3); // پاک کردن فلگ وقفه
ErrorHandler(ERR_EMERGENCY_STOP); // اجرای هندلر توقف اضطراری
}
}