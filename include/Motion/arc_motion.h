#ifndef ARC_MOTION_H
#define ARC_MOTION_H

#include "types.h"

void arc_init(float X, float Y, float i, float j, int cw, float feedrate);
void arc_interpolate(arc_t arc);

#endif // ARC_MOTION_H
