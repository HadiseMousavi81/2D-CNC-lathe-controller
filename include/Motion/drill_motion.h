#ifndef DRILL_MOTION_H
#define DRILL_MOTION_H

#include "stm32f103.h"
#include <stdbool.h>
#include <stdint.h>

// -----------------------------
// State Machine for Motion
// -----------------------------
typedef enum {
    STATE_IDLE,
    STATE_PREPARING,
    STATE_ACCEL,
    STATE_CRUISE,
    STATE_DEACCEL,
    STATE_COMEBACK,
    STATE_DONE
} MotionState;

extern volatile MotionState motion_state;

// -----------------------------
// Global Variables
// -----------------------------
extern volatile uint32_t step_index;
extern volatile bool update_needed;
extern volatile bool step_state;
extern volatile bool comeback_flag;

extern uint8_t back_index;
extern uint8_t back_num;
extern volatile uint32_t peck_depth_q;

// -----------------------------
// Public Function Prototypes
// -----------------------------
void TIM1_Init(void);
void GPIOC_Init(void);

void Update_DrillMotion(void);
void Drill_In(int x2 , int y2 , int dz, int Feedrate, int q);


void move_to(int x, int y, int speed);

#endif // MOTION_H
