// MotionControl/planner.c
// Calculates the required step counts for motion phases

#include "planner.h"

int Stepx_required, Stepy_required;
uint32_t first_phstep_x, second_phstep_x, third_phstep_x;
uint32_t first_phstep_y, second_phstep_y, third_phstep_y;

void Stepx_required_calculate(uint32_t deltax) {
    Stepx_required = deltax * 400;
    first_phstep_x = Stepx_required * 0.2;
    second_phstep_x = Stepx_required * 0.6 - first_phstep_x;
    third_phstep_x = Stepx_required - Stepx_required * 0.6;
}

void Stepy_required_calculate(uint32_t deltay) {
    Stepy_required = deltay * 400;
    first_phstep_y = Stepy_required * 0.2;
    second_phstep_y = Stepy_required * 0.6 - first_phstep_y;
    third_phstep_y = Stepy_required - Stepy_required * 0.6;
}