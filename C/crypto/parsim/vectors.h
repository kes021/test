#ifndef VECTORES_HEADER
#define VECTORES_HEADER
#include <math.h>
#pragma pack(push)
#pragma pack(1)

/*
 *  Does is realy make sense to inline every function?
 *  Most of the time the compiler would to this by testing.
 */

typedef struct {
    float x, y;
} vec2;

typedef struct {
    float x, y, z;
} vec3;

typedef struct {
    float x, y, z, w;
} vec4;


extern const vec2 base_vectors_2 [2];
extern const vec3 base_vectors_3 [3];
extern const vec4 base_vectors_4 [4];

extern const vec2 origin_2;
extern const vec3 origin_3;
extern const vec4 origin_4;

/*
 *  TODO
 *  This can be highly optimized using some intrinsics from sse.
 *  But for now, this should be enough.
 */

static inline void add2 (vec2 *u, const vec2 *v, const vec2 *w)
{
    u->x = v->x + w->x;
    u->y = v->y + w->y;
}

static inline void add3 (vec3 *u, const vec3 *v, const vec3 *w)
{
    u->x = v->x + w->x;
    u->y = v->y + w->y;
    u->z = v->z + w->z;
}

static inline void add4 (vec4 *u, const vec4 *v, const vec4 *w)
{
    u->x = v->x + w->x;
    u->y = v->y + w->y;
    u->z = v->z + w->z;
    u->w = u->w + w->w;
}

static inline void add_scaled2 (vec2 *u, const vec2 *v, float a, const vec2 *w)
{
    u->x = v->x + a * w->x;
    u->y = v->y + a * w->y;
}

static inline void add_scaled3 (vec3 *u, const vec3 *v, float a, const vec3 *w)
{
    u->x = v->x + a * w->x;
    u->y = v->y + a * w->y;
    u->z = v->z + a * w->z;
}

static inline void add_scaled4 (vec4 *u, const vec4 *v, float a, const vec4 *w){
    u->x = v->x + a * w->x;
    u->y = v->y + a * w->y;
    u->z = v->z + a * w->z;
    u->w = u->w + a * w->w;
}

static inline void linear_combine2 (vec2 *u, float a, const vec2 *v, float b, const vec2 *w)
{
    u->x = a * v->x + b * w->x;
    u->y = a * v->y + b * w->y;
}

static inline void linear_combine3 (vec3 *u, float a, const vec3 *v, float b, const vec3 *w)
{
    u->x = a * v->x + b * w->x;
    u->y = a * v->y + b * w->y;
    u->z = a * v->z + b * w->z;
}

static inline void linear_combine4 (vec4 *u, float a, const vec4 *v, float b, const vec4 *w)
{
    u->x = a * v->x + b * w->x;
    u->y = a * v->y + b * w->y;
    u->z = a * v->z + b * w->z;
    u->w = a * u->w + b * w->w;
}

static inline void sub2 (vec2 *u, const vec2 *v, const vec2 *w)
{
    u->x = v->x - w->x;
    u->y = v->y - w->y;
}

static inline void sub3 (vec3 *u, const vec3 *v, const vec3 *w)
{
    u->x = v->x - w->x;
    u->y = v->y - w->y;
    u->z = v->z - w->z;
}

static inline void sub4 (vec4 *u, const vec4 *v, const vec4 *w)
{
    u->x = v->x - w->x;
    u->y = v->y - w->y;
    u->z = v->z - w->z;
    u->w = v->w - w->w;
}

static inline void scale2 (vec2 *u, float s, const vec2 *v)
{
    u->x = s * v->x;
    u->y = s * v->y;
}

static inline void scale3 (vec3 *u, float s, const vec3 *v)
{
    u->x = s * v->x;
    u->y = s * v->y;
    u->z = s * v->z;
}

static inline void scale4 (vec4 *u, float s, const vec4 *v)
{
    u->x = s * v->x;
    u->y = s * v->y;
    u->z = s * v->z;
    u->w = s * v->w;
}

float acos_dot2 (const vec2 *v, const vec2 *w);
float acos_dot3 (const vec3 *v, const vec3 *w);
float acos_dot4 (const vec4 *v, const vec4 *w);

static inline float dot2 (const vec2 *v, const vec2 *w)
{
    return v->x * w->x + v->y * w->y;
}

static inline float dot3 (const vec3 *v, const vec3 *w)
{
    return v->x * w->x + v->y * w->y + v->z * w->z;
}

static inline float dot4 (const vec4 *v, const vec4 *w)
{
    return v->x * w->x + v->y * w->y + v->z * w->z + v->w * w->w;
}

static inline float length2 (const vec2 *v)
{
    return sqrt (dot2 (v, v));
}

static inline float length3 (const vec3 *v)
{
    return sqrt (dot3 (v, v));
}

static inline float length4 (const vec4 *v)
{
    return sqrt (dot4 (v, v));
}

static inline void normalize2 (vec2 *v)
{
    scale2 (v, 1.0 / length2 (v), v);
}

static inline void normalize3 (vec3 *v)
{
    scale3 (v, 1.0 / length3 (v), v);
}

static inline void normalize4 (vec4 *v)
{
    scale4 (v, 1.0 / length4 (v), v);
}

static inline void normalized2 (vec2* w, const vec2 *v)
{
    scale2 (w, 1.0 / length2 (v), v);
}

static inline void normalized3 (vec3* w, const vec3 *v)
{
    scale3 (w, 1.0 / length3 (v), v);
}

static inline void normalized4 (vec4* w, const vec4 *v)
{
    scale4 (w, 1.0 / length4 (v), v);
}

static inline float distance2 (const vec2 *v, const vec2 *w)
{
    vec2 d;

    sub2(&d, v, w);
    return length2(&d);
}

static inline float distance3 (const vec3 *v, const vec3 *w)
{
    vec3 d;

    sub3(&d, v, w);
    return length3(&d);
}

static inline float distance4 (const vec4 *v, const vec4 *w)
{
    vec4 d;

    sub4(&d, v, w);
    return length4(&d);
}

static inline void cross_product (vec3 *u, const vec3 *v, const vec3 *w)
{
    u->x = v->y * w->z - v->z * w->y;
    u->y = v->z * w->x - v->x * w->z;
    u->z = v->x * w->y - v->y * w->x;
}

static inline void homogenise (vec4 *u, const vec3 *v)
{
    u->x = v->x;
    u->y = v->y;
    u->z = v->z;
    u->w = 1.0;
}

static inline void dehomogenise (vec3 *u, const vec4 *v)
{
    u->x = v->x / v->w;
    u->y = v->y / v->w;
    u->z = v->z / v->w;
}

/*
 *  Affine Methods. These methods use vec4 but operate only on the first three
 *      components and set w to the value of the first operand;
 */

static inline void add4a (vec4 *u, const vec4 *v, const vec4 *w)
{
    u->x = v->x + w->x;
    u->y = v->y + w->y;
    u->z = v->z + w->z;
    u->w = v->w;
}

static inline void add_scaled4a (vec4 *u, const vec4 *v, float a, const vec4 *w){
    u->x = v->x + a * w->x;
    u->y = v->y + a * w->y;
    u->z = v->z + a * w->z;
    u->w = v->w;
}

static inline void sub4a (vec4 *u, const vec4 *v, const vec4 *w)
{
    u->x = v->x - w->x;
    u->y = v->y - w->y;
    u->z = v->z - w->z;
    u->w = v->w;
}

static inline void scale4a (vec4 *u, float a, const vec4 *v)
{
    u->x = a * v->x;
    u->y = a * v->y;
    u->z = a * v->z;
    u->w = v->w;
}


static inline
float atan2_vec2 (const vec2 *v, const vec2 *w)
{
    vec2 d;
    sub2 (&d, w, v);

    return atan2 (d.x, d.y);
}

static inline
float atan2_vec3xy (const vec3 *v, const vec3 *w)
{
    vec3 d;
    sub3 (&d, w, v);

    return atan2 (d.x, d.y);
}

static inline
float atan2_vec3xz (const vec3 *v, const vec3 *w)
{
    vec3 d;
    sub3 (&d, w, v);

    return atan2 (d.x, d.z);
}


#pragma pack(pop)
#endif  /* VECTORES_HEADER */
