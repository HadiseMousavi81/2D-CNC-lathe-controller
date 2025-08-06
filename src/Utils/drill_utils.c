#include "drill_utils.h"
#include <math.h>

#define Timer_Clock 72000000UL
#define Prescaler    72

// ---- Motion Variables ----
uint32_t Stepz_required;
uint32_t first_phstep_z, second_phstep_z, third_phstep_z;
uint32_t Target_Delay, Start_Delay = 50;  // us

void Stepz_required_calculate(uint32_t deltaz) {
    Stepz_required = deltaz * 400;   // steps/mm
    first_phstep_z = Stepz_required * 0.2;
    second_phstep_z = Stepz_required * 0.6 - first_phstep_z;
    third_phstep_z = Stepz_required - Stepz_required * 0.6;
}

uint32_t Delay_to_counter(uint32_t delay_us) {
    return (delay_us * Timer_Clock) / (Prescaler + 1);
}

uint32_t feedrate_to_delay(uint32_t feedrate) {
    return (60000000 / (feedrate * 400));
}

uint32_t Calc_StepDelay(uint32_t stepindex, uint8_t op) {
    uint32_t current_delay = 0;

    switch(op) {
        case 0: // accel
            current_delay = Target_Delay + (Target_Delay - Start_Delay) *
            sqrtf(1.0f - ((float)stepindex / first_phstep_z));
            break;

        case 1: // cruise
            current_delay = Target_Delay;
            break;

        case 2: // decel
            current_delay = Target_Delay + (Target_Delay - Start_Delay) *
            sqrtf((float)stepindex / third_phstep_z);
            break;
    }

    return current_delay;
}
