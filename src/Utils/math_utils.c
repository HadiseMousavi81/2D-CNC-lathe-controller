#include "math_utils.h"
#include "constants.h"


float deg2rad(float deg) {
    return deg * PI / 180.0f;
}

float normalize_angle(float theta) {
    while (theta < 0) theta += 2 * PI;
    while (theta >= 2 * PI) theta -= 2 * PI;
    return theta;
}
