#ifndef MATH_UTILS_HEADER
#define MATH_UTILS_HEADER
#include <stdlib.h>
#include <math.h>

#define M_PI 3.14159265358979323846

/*
 *  Clamps the value d to [-1, 1] and then
 *      passes to acos.
 */
float acos_clamp (float d);


/*
 *  Fast truncation. Returns the integer part of the value.
 */
static inline
int trunc_f (float x)
{
    return (int) (x >= 0.0) ? x : (x - 1.0);
}


/*
 *  Returns the maximum of the absolute values.
 */
static inline
int max_abs3 (int a, int b, int c)
{
    return ( abs(a) + abs(b) + abs(c) ) >> 1;
}



static inline
float interval_clamp (float high, float low, float value)
{
    if (value >= high)
    {
        return high;
    }
    else if (value <= low)
    {
        return low;
    }
    else
    {
        return value;
    }
}

static inline
float interval_truncate (float high, float low, float value)
{
    if (value >= high)
    {
        return 1.0;
    }
    else if (value <= low)
    {
        return -1.0;
    }
    else
    {
        return 0.0;
    }
}

#endif  /* MATH_UTILS_HEADER */
