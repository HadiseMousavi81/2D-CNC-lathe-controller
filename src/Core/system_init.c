#include "gpio.h"
#include "timer.h"

void System_Init(void) {
    GPIOA_Init();
    GPIOB_Init();
    TIM2_Init();
    TIM3_Init();
}
