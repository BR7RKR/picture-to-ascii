#include "global.h"
#include <math.h>

const int MAX_BRIGHTNESS = 255;

bool is_equalf(float first, float second){
    float epsilon = 1e-6f;
    return fabsf(first - second) <= epsilon * fmaxf(fabsf(first), fabsf(second));
}

