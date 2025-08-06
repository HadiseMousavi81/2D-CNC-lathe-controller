#include "drill_gpio.h"

void GPIOC_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    GPIOC->CRL &= ~((0xF << 0) | (0xF << 4)); 
    GPIOC->CRL |=  (0x3 << 0) | (0x3 << 4);    // Output 50MHz push-pull
}
