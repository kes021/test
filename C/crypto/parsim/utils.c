#include <math.h>
#include "utils.h"


float acos_clamp (float d)
{
    if (d > 1.0)
    {
        d = 1.0;
    }
    else if (d < -1.0)
    {
        d = -1.0;
    }

    return acos (d);
}