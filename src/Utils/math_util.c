// Utils/math_util.c
#include "math_util.h"
#include "config.h"

uint32_t Delay_to_counter(uint32_t delay_us) {
    return (delay_us * Timer_Clock) / (Prescaler + 1);
}

uint32_t feedrate_to_delay(uint32_t feedrate) {
    return (60000000 / (feedrate * 400));
}
