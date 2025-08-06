#ifndef DRILL_TIMER_H
#define DRILL_TIMER_H

#include "stm32f103.h"
#include <stdbool.h>

#define Timer_Clock 72000000UL
#define Prescaler    72

extern volatile bool update_needed;
extern volatile uint32_t step_index;

void TIM1_Init(void);

#endif
