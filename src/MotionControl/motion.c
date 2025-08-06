// MotionControl/motion.c
// Contains the main motion control state machine

#include "motion.h"
#include "planner.h"
#include "bresenham.h"
#include "stepgen.h"
#include "math_utils.h"
#include "config.h"
#include "error_manager.h"

static enum {
    STATE_ACCEL,
    STATE_CRUISE,
    STATE_DEACCEL,
    STATE_ERROR,
    STATE_DONE,
} MotionState

MotionState motion_state = STATE_IDLE;

static int dx, dy, sx, sy, err;
bool x_is_primary;
extern uint32_t step_index;

void Move_to(int x2, int y2, int Feedrate) {
    if (motion_state != STATE_IDLE)
        return;

    if (x2 < PARAM_MIN  x2 > PARAM_MAX  y2 < PARAM_MIN || y2 > PARAM_MAX) {
        ErrorHandler(ERR_OUT_OF_BOUND);
        return;
    }

    if (Feedrate <= 0 || Feedrate > MAX_FEEDRATE) {
        ErrorHandler(ERR_INVALID_FEEDRATE
   );
        return;
    }

    if (x1 == x2 && y1 == y2)
        return; // مقصد با مبدا یکسان است

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    sx = (x2 > x1) ? 1 : -1;
    sy = (y2 > y1) ? 1 : -1;
    err = 2 * dy - dx;
    Target_Delay = feedrate_to_delay(Feedrate);

    Stepx_required_calculate(dx);
    Stepy_required_calculate(dy);
    x_is_primary = (dx > dy);

    motion_state = STATE_ACCEL;  // فقط زمانی که همه چیز OK بود
}
