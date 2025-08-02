#ifndef TYPES_H
#define TYPES_H

typedef struct {
    float xc, yc;
    float radius;
    float theta_start, theta_end;
    float theta_step;
    int segment_count;
    float feedrate;
    int cw;
    float x_end, y_end;
} arc_t;

// state motion_state.h 

#endif // TYPES_H