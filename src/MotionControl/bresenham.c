// MotionControl/bresenham.c
// Bresenham-based stepping logic and motion state update

#include "bresenham.h"
#include "planner.h"
#include "stepgen.h"

extern bool update_needed;
extern uint32_t Target_Delay;
extern uint32_t Start_Delay , current_delay;
extern enum { STATE_IDLE, STATE_PREPARING, STATE_ACCEL, STATE_CRUISE, STATE_DEACCEL, STATE_DONE } motion_state;

void Calc_StepDelay(uint32_t stepindex, uint8_t op) {
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

return current_delay ;


}

// ---- Motion Update (call in while(1)) ----
void Update_Motion(void) {
if (!update_needed) return;
update_needed = false;

switch(motion_state) {  
    case STATE_ACCEL:  
        if (step_index <= first_phstep_z) {  
            TIM1->ARR = Delay_to_counter(Calc_StepDelay(step_index, 0));  
        } else {  
            motion_state = STATE_CRUISE;  
        }  
        break;  

    case STATE_CRUISE:  
        if (step_index <= Stepz_required * 0.6) {  
            TIM2->ARR = Delay_to_counter(Calc_StepDelay(step_index, 1));  
        } else {  
            motion_state = STATE_DEACCEL;  
        }  
        break;  

    case STATE_DEACCEL:  
        if (step_index <= Stepz_required) {  
            TIM2->ARR = Delay_to_counter(Calc_StepDelay(step_index, 2));  
        } else {  
            motion_state = STATE_DONE;  
               }  
        break;  

 
    case STATE_DONE:
          return ; 
          break;

    default:  
        break;  
}

}