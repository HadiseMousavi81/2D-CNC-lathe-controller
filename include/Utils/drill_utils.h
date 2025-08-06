#ifndef DRILL_UTILS_H
#define DRILL_UTILS_H

#include <stdint.h>


void Stepz_required_calculate(uint32_t deltaz);


uint32_t Delay_to_counter(uint32_t delay_us);


uint32_t feedrate_to_delay(uint32_t feedrate);


uint32_t Calc_StepDelay(uint32_t stepindex, uint8_t op);

extern uint32_t Stepz_required;
extern uint32_t first_phstep_z, second_phstep_z, third_phstep_z;
extern uint32_t Target_Delay, Start_Delay;

#endif
