// MotionControl/planner.h
#ifndef PLANNER_H
#define PLANNER_H

#include <stdint.h>
extern int Stepx_required, Stepy_required;
extern uint32_t first_phstep_x, second_phstep_x, third_phstep_x;
extern uint32_t first_phstep_y, second_phstep_y, third_phstep_y;

void Stepx_required_calculate(uint32_t deltax);
void Stepy_required_calculate(uint32_t deltay);

#endif