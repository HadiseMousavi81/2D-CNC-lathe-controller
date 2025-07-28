// MotionControl/motion.c
// Contains the main motion control state machine

#include "motion.h"
#include "planner.h"
#include "bresenham.h"
#include "stepgen.h"
#include "math_utils.h"
#include "config.h"

static enum {
    STATE_IDLE,
    STATE_PREPARING,
    STATE_ACCEL,
    STATE_CRUISE,
    STATE_DEACCEL,
    STATE_DONE,
} motion_state = STATE_IDLE;

static int dx, dy, sx, sy, err;
bool x_is_primary;
extern uint32_t step_index;

void Move_to(int x2, int y2, int Feedrate) {
    switch (motion_state) {
        case STATE_IDLE:
            motion_state = STATE_PREPARING;
            break;

        case STATE_PREPARING:
            dx = abs(x2 - x1);
            dy = abs(y2 - y1);
            sx = (x2 > x1) ? 1 : -1;
            sy = (y2 > y1) ? 1 : -1;
            err = 2 * dy - dx;
            Target_Delay = feedrate_to_delay(Feedrate);
            step_index = 0;
            Stepx_required_calculate(dx);
            Stepy_required_calculate(dy);
            x_is_primary = (dx > dy);
            motion_state = STATE_ACCEL;
            break;

        case STATE_ACCEL:
        case STATE_CRUISE:
        case STATE_DEACCEL:
            if (x_is_primary) {
                if (err <= 0) {
                    Step_x();
                    err += 2 * dy;
                } else {
                    Step_x();
                    Step_y();
                    err -= 2 * dx;
                }
            } else {
                if (err <= 0) {
                    Step_y();
                    err += 2 * dx;
                } else {
                    Step_y();
                    Step_x();
                    err -= 2 * dy;
                }
            }
            break;

        case STATE_DONE:
            motion_state = STATE_IDLE;
            break;
    }
}