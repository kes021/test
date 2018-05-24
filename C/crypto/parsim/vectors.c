#include <math.h>
#include "utils.h"
#include "vectors.h"

const vec2 base_vectors_2 [2] = {
    { 1.0, 0.0 },
    { 0.0, 1.0 }
};

const vec3 base_vectors_3 [3] = {
    { 1.0, 0.0, 0.0 },
    { 0.0, 1.0, 0.0 },
    { 0.0, 0.0, 1.0 }
};

const vec4 base_vectors_4 [4] = {
    { 1.0, 0.0, 0.0, 0.0 },
    { 0.0, 1.0, 0.0, 0.0 },
    { 0.0, 0.0, 1.0, 0.0 },
    { 0.0, 0.0, 0.0, 1.0 }
};

const vec2 origin_2 = {
    0.0, 0.0
};

const vec3 origin_3 = {
    0.0, 0.0, 0.0
};

const vec4 origin_4 = {
    0.0, 0.0, 0.0, 0.0
};

float acos_dot2 (const vec2 *v, const vec2 *w)
{
    vec2 nv, nw;
    normalized2 (&nv, v);
    normalized2 (&nw, w);
    return acos_clamp (dot2 (&nv, &nw));
}

float acos_dot3 (const vec3 *v, const vec3 *w)
{
    vec3 nv, nw;
    normalized3 (&nv, v);
    normalized3 (&nw, w);
    return acos_clamp (dot3 (&nv, &nw));
}

float acos_dot4 (const vec4 *v, const vec4 *w)
{
    vec4 nv, nw;
    normalized4 (&nv, v);
    normalized4 (&nw, w);
    return acos_clamp (dot4 (&nv, &nw));
}
