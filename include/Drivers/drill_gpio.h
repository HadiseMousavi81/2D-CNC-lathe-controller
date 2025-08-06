#ifndef DRIIL_GPIO_H
#define DRILL_GPIO_H

#include "stm32f103.h"

#define STEP_PIN     GPIO_ODR_ODR0
#define DIR_PIN      GPIO_ODR_ODR1

void GPIOC_Init(void);

#endif
