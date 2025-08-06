#include "Error_gpioconfig.h"

void Reset_ButtonError_GPIO(void){
// فعال‌سازی کلاک GPIOC (برای PC5)
RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

// تنظیم PC5 به عنوان ورودی (Input floating یا Pull-up)
GPIOC->CRL &= ~(0xF << (5 * 4));         // پاک کردن CNF و MODE
GPIOC->CRL |=  (0x8 << (5 * 4));         // CNF=10 (input with pull-up), MODE=00

// فعال‌سازی Pull-up داخلی (ODR=1 برای ورودی با pull-up)
GPIOC->ODR |= (1 << 5);

}

void LimitSwitch_GPIO_Init(void){
// فعال‌سازی کلاک GPIOA
RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

// پیکربندی PA5, PA6, PA7 به عنوان ورودی با Pull-up
GPIOA->CRL &= ~((0xF << (5 * 4)) | (0xF << (6 * 4)) | (0xF << (7 * 4)));
GPIOA->CRL |=  ((0x8 << (5 * 4)) | (0x8 << (6 * 4)) | (0x8 << (7 * 4)));  // CNF=10, MODE=00

GPIOA->ODR |= (1 << 5) | (1 << 6) | (1 << 7);  // Pull-up فعال

}

void EmergencyStop_GPIO_Init(void) {
// فعال‌سازی کلاک AFIO
RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

// اتصال EXTI3 به پایه PA3
AFIO->EXTICR[0] &= ~(0xF << (3 * 4)); // EXTICR[0], بیت‌های [15:12] برای EXTI3 = PA

// تنظیمات وقفه EXTI3 برای لبه پایین‌رونده (وقتی دکمه فشرده می‌شود)
EXTI->IMR  |= (1 << 3);   // فعال‌سازی ماسک وقفه
EXTI->FTSR |= (1 << 3);   // فعال‌سازی لبه پایین‌رونده
EXTI->RTSR &= ~(1 << 3);  // غیرفعال‌سازی لبه بالا‌رونده (اختیاری)

// فعال‌سازی وقفه در NVIC
NVIC_EnableIRQ(EXTI3_IRQn);

}