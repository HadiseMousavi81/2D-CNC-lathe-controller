// MotionControl/bresenham.c
// Bresenham-based stepping logic and motion state update

#include "bresenham.h"
#include "planner.h"
#include "stepgen.h"

extern bool update_needed;
extern uint32_t Target_Delay;
extern uint32_t Start_Delay;
extern enum { STATE_IDLE, STATE_PREPARING, STATE_ACCEL, STATE_CRUISE, STATE_DEACCEL, STATE_DONE } motion_state;

void SeT_Mototrspeed(uint32_t stepindex, uint8_t op) {
    uint32_t current_delay = 0;

    switch(op) {
        case 0: // plus
            current_delay = Target_Delay + (Target_Delay - Start_Delay) * sqrt(1.0 - ((float)stepindex / first_phstep_x));
            break;
        case 1: // NULL
            current_delay = Target_Delay;
            break;
        case 2: // minus
            current_delay = Target_Delay + (Target_Delay - Start_Delay) * sqrt((float)stepindex / third_phstep_x);
            break;
    }

    TIM2->ARR = Delay_to_counter(current_delay);
}



void Update_Delay(uint32_t index) {
    if (update_needed) {
        if (index > 0 && index <= first_phstep_x) {
            SeT_Mototrspeed(index, 0);
        } else if (index > first_phstep_x && index <= (Stepx_required * 0.6)) {
            motion_state = STATE_CRUISE;
        } else if (index > (Stepx_required * 0.6) && index <= Stepx_required) {
            SeT_Mototrspeed(index, 2);
        } else {
            motion_state = STATE_DONE;
        }
        update_needed = false;
    }
}
