<<<<<<< HEAD
#include <math.h>
#include <stdio.h>
#include "arc_motion.h"
#include "motion_state.h"
#include "constants.h"

extern void moveTo(float x, float y, float feedrate); // ??? ?? ???? ??? ???? ?? ??? ????

static arc_t arc;  // ????? ??????

void arc_init(float X, float Y, float i, float j, int cw, float feedrate) {
    int x_start = state->x;
    int y_start = state->y;

    arc.xc = x_start + i;
    arc.yc = y_start + j;

    float dx = x_start - arc.xc;
    float dy = y_start - arc.yc;
    arc.radius = sqrt(dx * dx + dy * dy);

    arc.theta_start = atan2(y_start - arc.yc, x_start - arc.xc);
    arc.theta_end   = atan2(Y - arc.yc, X - arc.xc);

    float dtheta;
    arc.cw = cw;
    if (arc.cw) {
        // ???????? (G2)
        if (arc.theta_end > arc.theta_start)
            arc.theta_end -= 2 * PI;
        dtheta = arc.theta_end - arc.theta_start;
    } else {
        // ??????????? (G3)
        if (arc.theta_end < arc.theta_start)
            arc.theta_end += 2 * PI;
        dtheta = arc.theta_end - arc.theta_start;
    }

    arc.segment_count = arc.radius * RESOLUTION;
    arc.theta_step = dtheta / arc.segment_count;

    arc.feedrate = feedrate;
    arc.x_end = X;
    arc.y_end = Y;
    arc_interpolate(arc);
}

void arc_interpolate(arc_t arc) {
    float x = 0.0f, y = 0.0f;

    for (int i = 1; i <= arc.segment_count; i++) {
        float theta = arc.theta_start + i * arc.theta_step;
        x = arc.xc + arc.radius * cos(theta);
        y = arc.yc + arc.radius * sin(theta);
        moveTo(x, y, arc.feedrate);
    }

    if (fabs(x - arc.x_end) > ARC_EPSILON || fabs(y - arc.y_end) > ARC_EPSILON) {
        moveTo(arc.x_end, arc.y_end, arc.feedrate);
    }
}
=======
#include <math.h>
#include <stdio.h>
#include "arc_motion.h"
#include "motion_state.h"
#include "constants.h"

extern void moveTo(float x, float y, float feedrate); // ??? ?? ???? ??? ???? ?? ??? ????

static arc_t arc;  // ????? ??????

void arc_init(float X, float Y, float i, float j, int cw, float feedrate) {
    int x_start = state->x;
    int y_start = state->y;

    arc.xc = x_start + i;
    arc.yc = y_start + j;

    float dx = x_start - arc.xc;
    float dy = y_start - arc.yc;
    arc.radius = sqrt(dx * dx + dy * dy);

    arc.theta_start = atan2(y_start - arc.yc, x_start - arc.xc);
    arc.theta_end   = atan2(Y - arc.yc, X - arc.xc);

    float dtheta;
    arc.cw = cw;
    if (arc.cw) {
        // ???????? (G2)
        if (arc.theta_end > arc.theta_start)
            arc.theta_end -= 2 * PI;
        dtheta = arc.theta_end - arc.theta_start;
    } else {
        // ??????????? (G3)
        if (arc.theta_end < arc.theta_start)
            arc.theta_end += 2 * PI;
        dtheta = arc.theta_end - arc.theta_start;
    }

    arc.segment_count = arc.radius * RESOLUTION;
    arc.theta_step = dtheta / arc.segment_count;

    arc.feedrate = feedrate;
    arc.x_end = X;
    arc.y_end = Y;
    arc_interpolate(arc);
}

void arc_interpolate(arc_t arc) {
    float x = 0.0f, y = 0.0f;

    for (int i = 1; i <= arc.segment_count; i++) {
        float theta = arc.theta_start + i * arc.theta_step;
        x = arc.xc + arc.radius * cos(theta);
        y = arc.yc + arc.radius * sin(theta);
        moveTo(x, y, arc.feedrate);
    }

    if (fabs(x - arc.x_end) > ARC_EPSILON || fabs(y - arc.y_end) > ARC_EPSILON) {
        moveTo(arc.x_end, arc.y_end, arc.feedrate);
    }
}
>>>>>>> 51c48adcdea636a554917b96feec4cc4f97eb4b9
