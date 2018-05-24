#include <stdbool.h>
#include <math.h>

#include "vectors.h"
#include "matrices.h"

/*
 *  TODO: may inline some of these functions?
 */

void matrix_mult2 (mat2 m, const mat2 n, const mat2 o)
{
    int i, j, k;
    for(i = 0; i < 2; i++) {
        for(j = 0; j < 2; j++) {
            m[M2_ENTRY(i, j)] = 0.0;
            for(k = 0; k < 2; k++) {
                m[M2_ENTRY(i, j)] += n[M2_ENTRY(i, k)] * o[M2_ENTRY(k, j)];
            }
        }
    }
}

void matrix_mult3 (mat3 m, const mat3 n, const mat3 o)
{
    int i, j, k;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            m[M3_ENTRY(i, j)] = 0.0;
            for(k = 0; k < 3; k++) {
                m[M3_ENTRY(i, j)] += n[M3_ENTRY(i, k)] * o[M3_ENTRY(k, j)];
            }
        }
    }
}

void matrix_mult4 (mat4 m, const mat4 n, const mat4 o)
{
    int i, j, k;
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            m[M4_ENTRY(i, j)] = 0.0;
            for(k = 0; k < 4; k++) {
                m[M4_ENTRY(i, j)] += n[M4_ENTRY(i, k)] * o[M4_ENTRY(k, j)];
            }
        }
    }
}

void matrix_mult_vector2 (vec2 *u, const mat2 m, const vec2 *v)
{
    u->x = m[M2_ENTRY(0, 0)] * v->x + m[M2_ENTRY(0, 1)] * v->y;
    u->y = m[M2_ENTRY(1, 0)] * v->x + m[M2_ENTRY(1, 1)] * v->y;
}

void matrix_mult_vector3 (vec3 *u, const mat3 m, const vec3 *v)
{
    u->x = m[M3_ENTRY(0, 0)] * v->x + m[M3_ENTRY(0, 1)] * v->y + m[M3_ENTRY(0, 2)] * v->z;
    u->y = m[M3_ENTRY(1, 0)] * v->x + m[M3_ENTRY(1, 1)] * v->y + m[M3_ENTRY(1, 2)] * v->z;
    u->z = m[M3_ENTRY(2, 0)] * v->x + m[M3_ENTRY(2, 1)] * v->y + m[M3_ENTRY(2, 2)] * v->z;
}

void matrix_mult_vector4 (vec4 *u, const mat4 m, const vec4 *v)
{
    u->x = m[M4_ENTRY(0, 0)] * v->x + m[M4_ENTRY(0, 1)] * v->y + m[M4_ENTRY(0, 2)] * v->z + m[M4_ENTRY(0, 3)] * v->w;
    u->y = m[M4_ENTRY(1, 0)] * v->x + m[M4_ENTRY(1, 1)] * v->y + m[M4_ENTRY(1, 2)] * v->z + m[M4_ENTRY(1, 3)] * v->w;
    u->z = m[M4_ENTRY(2, 0)] * v->x + m[M4_ENTRY(2, 1)] * v->y + m[M4_ENTRY(2, 2)] * v->z + m[M4_ENTRY(2, 3)] * v->w;
    u->w = m[M4_ENTRY(3, 0)] * v->x + m[M4_ENTRY(3, 1)] * v->y + m[M4_ENTRY(3, 2)] * v->z + m[M4_ENTRY(3, 3)] * v->w;
}

void matrix_mult_vector4l (vec4 *u, const mat4 m, const vec4 *v)
{
    u->x = m[M4_ENTRY(0, 0)] * v->x + m[M4_ENTRY(0, 1)] * v->y + m[M4_ENTRY(0, 2)] * v->z;
    u->y = m[M4_ENTRY(1, 0)] * v->x + m[M4_ENTRY(1, 1)] * v->y + m[M4_ENTRY(1, 2)] * v->z;
    u->z = m[M4_ENTRY(2, 0)] * v->x + m[M4_ENTRY(2, 1)] * v->y + m[M4_ENTRY(2, 2)] * v->z;
    u->w = v->w;
}

void matrix_transpose_mult_vector4l (vec4 *u, const mat4 m, const vec4 *v)
{
    u->x = m[M4_ENTRY(0, 0)] * v->x + m[M4_ENTRY(1, 0)] * v->y + m[M4_ENTRY(2, 0)] * v->z;
    u->y = m[M4_ENTRY(0, 1)] * v->x + m[M4_ENTRY(1, 1)] * v->y + m[M4_ENTRY(2, 1)] * v->z;
    u->z = m[M4_ENTRY(0, 2)] * v->x + m[M4_ENTRY(1, 2)] * v->y + m[M4_ENTRY(2, 2)] * v->z;
    u->w = v->w;
}

void matrix_transpose4 (mat4 m, const mat4 n)
{
    m[M4_ENTRY(0, 0)] = n[M4_ENTRY(0, 0)];
    m[M4_ENTRY(1, 0)] = n[M4_ENTRY(0, 1)];
    m[M4_ENTRY(2, 0)] = n[M4_ENTRY(0, 2)];
    m[M4_ENTRY(3, 0)] = n[M4_ENTRY(0, 3)];

    m[M4_ENTRY(0, 1)] = n[M4_ENTRY(1, 0)];
    m[M4_ENTRY(1, 1)] = n[M4_ENTRY(1, 1)];
    m[M4_ENTRY(2, 1)] = n[M4_ENTRY(1, 2)];
    m[M4_ENTRY(3, 1)] = n[M4_ENTRY(1, 3)];

    m[M4_ENTRY(0, 2)] = n[M4_ENTRY(2, 0)];
    m[M4_ENTRY(1, 2)] = n[M4_ENTRY(2, 1)];
    m[M4_ENTRY(2, 2)] = n[M4_ENTRY(2, 2)];
    m[M4_ENTRY(3, 2)] = n[M4_ENTRY(2, 3)];

    m[M4_ENTRY(0, 3)] = n[M4_ENTRY(3, 0)];
    m[M4_ENTRY(1, 3)] = n[M4_ENTRY(3, 1)];
    m[M4_ENTRY(2, 3)] = n[M4_ENTRY(3, 2)];
    m[M4_ENTRY(3, 3)] = n[M4_ENTRY(3, 3)];
}

void orthogonal_matrix4
    (mat4 m, float left, float right, float bottom, float top, float near, float far)
{

    // map [left, right]    to [-1, 1]
    // map [bottom, top]    to [-1, 1]
    // map [near, far]      to [0, 1] (!)

    m[M4_ENTRY(0, 0)]   = 2.0 / ( right - left );
    m[M4_ENTRY(1, 0)]   = 0.0;
    m[M4_ENTRY(2, 0)]   = 0.0;
    m[M4_ENTRY(3, 0)]   = 0.0;

    m[M4_ENTRY(0, 1)]   = 0.0;
    m[M4_ENTRY(1, 1)]   = 2.0 / ( top - bottom );
    m[M4_ENTRY(2, 1)]   = 0.0;
    m[M4_ENTRY(3, 1)]   = 0.0;

    m[M4_ENTRY(0, 2)]   = 0.0;
    m[M4_ENTRY(1, 2)]   = 0.0;
    m[M4_ENTRY(2, 2)]   = 1.0 / ( far - near );
    m[M4_ENTRY(3, 2)]   = 0.0;

    m[M4_ENTRY(0, 3)]   = - ( right + left ) / ( right - left );
    m[M4_ENTRY(1, 3)]   = - ( top + bottom ) / ( top - bottom );
    m[M4_ENTRY(2, 3)]   = - near / ( far - near );
    m[M4_ENTRY(3, 3)]   = 1.0;
}

void perspective_matrix4
    (mat4 m, float fovy, float aspect, float zNear, float zFar)
{
    float f = 1.0 / tan(fovy / 2.0);

    m[M4_ENTRY(0, 0)]   = f / aspect;
    m[M4_ENTRY(1, 0)]   = 0.0;
    m[M4_ENTRY(2, 0)]   = 0.0;
    m[M4_ENTRY(3, 0)]   = 0.0;

    m[M4_ENTRY(0, 1)]   = 0.0;
    m[M4_ENTRY(1, 1)]   = f;
    m[M4_ENTRY(2, 1)]   = 0.0;
    m[M4_ENTRY(3, 1)]   = 0.0;

    m[M4_ENTRY(0, 2)]   = 0.0;
    m[M4_ENTRY(1, 2)]   = 0.0;
    m[M4_ENTRY(2, 2)]   = - zFar / (zNear - zFar);
    m[M4_ENTRY(3, 2)]   = 1.0;

    m[M4_ENTRY(0, 3)]   = 0.0;
    m[M4_ENTRY(1, 3)]   = 0.0;
    m[M4_ENTRY(2, 3)]   = zNear * zFar / (zNear - zFar);
    m[M4_ENTRY(3, 3)]   = 0.0;
}

void look_at_matrix4
    (mat4 m, const vec3 *position, const vec3 *look_at, const vec3 *top)
{
    vec3 view;

    sub3(&view, look_at, position);
    view_in_matrix4(m, position, &view, top);
}

void view_in_matrix4
    (mat4 m, const vec3 *position, const vec3 *view, const vec3 *top)
{
    mat4 linear, affine;
    vec3 nView = *view, nTop = *top, nRight;

    normalize3(&nView);                         // map view to +z
    normalize3(&nTop);                          // map top to +y
    cross_product(&nRight, &nView, &nTop);      // get the right
    normalize3(&nRight);                        //  this must not be normal
    cross_product(&nTop, &nRight, &nView);      //  get normal top, is normal, since nRight, nTop orthonormal
    scale3(&nRight, -1.0, &nRight);             // LEFT HANDED!

    // remember, we want the position to become zero
    //  further the x axis should be nRight, y equals nTop and z(!) is nView
    //  since this is a orthonormal basis just transpose to invert
    translate_matrix4_s(affine, -position->x, -position->y, -position->z);
    column_matrix4_linear_transpose(linear, &nRight, &nTop, &nView);
    matrix_mult4(m, linear, affine);
}

void rotation_matrix4_v (mat4 m, float alpha, const vec3 *axis)
{
    vec3 n = *axis;
    normalize3(&n);

    float c = cos(alpha), s = sin(alpha), ac = 1.0 - c;

    m[M4_ENTRY(0, 0)] = n.x * n.x * ac + c;
    m[M4_ENTRY(1, 0)] = n.x * n.y * ac + n.z * s;
    m[M4_ENTRY(2, 0)] = n.x * n.z * ac - n.y * s;
    m[M4_ENTRY(3, 0)] = 0.0;

    m[M4_ENTRY(0, 1)] = n.x * n.y * ac - n.z * s;
    m[M4_ENTRY(1, 1)] = n.y * n.y * ac + c;
    m[M4_ENTRY(2, 1)] = n.z * n.y * ac + n.x * s;
    m[M4_ENTRY(3, 1)] = 0.0;

    m[M4_ENTRY(0, 2)] = n.x * n.z * ac + n.y * s;
    m[M4_ENTRY(1, 2)] = n.y * n.z * ac - n.x * s;
    m[M4_ENTRY(2, 2)] = n.z * n.z * ac + c;
    m[M4_ENTRY(3, 2)] = 0.0;

    m[M4_ENTRY(0, 3)] = 0.0;
    m[M4_ENTRY(1, 3)] = 0.0;
    m[M4_ENTRY(2, 3)] = 0.0;
    m[M4_ENTRY(3, 3)] = 1.0;
}

void scale_matrix4_v (mat4 m, float scale)
{
    m[M4_ENTRY(0, 0)] = scale;
    m[M4_ENTRY(1, 0)] = 0.0;
    m[M4_ENTRY(2, 0)] = 0.0;
    m[M4_ENTRY(3, 0)] = 0.0;

    m[M4_ENTRY(0, 1)] = 0.0;
    m[M4_ENTRY(1, 1)] = scale;
    m[M4_ENTRY(2, 1)] = 0.0;
    m[M4_ENTRY(3, 1)] = 0.0;

    m[M4_ENTRY(0, 2)] = 0.0;
    m[M4_ENTRY(1, 2)] = 0.0;
    m[M4_ENTRY(2, 2)] = scale;
    m[M4_ENTRY(3, 2)] = 0.0;

    m[M4_ENTRY(0, 3)] = 0.0;
    m[M4_ENTRY(1, 3)] = 0.0;
    m[M4_ENTRY(2, 3)] = 0.0;
    m[M4_ENTRY(3, 3)] = 1.0;
}

/*
void rotation_matrix4_s(mat4 m, float alpha, float x, float y, float z)
{
    vec3 axis = {
        { x, y, z }
    };

    rotation_matrix4_v (m, alpha, &axis);
}

void scale_matrix4_s(mat4 m, float x, float y, float z)
{
    m[M4_ENTRY(0, 0)] = x;
    m[M4_ENTRY(1, 0)] = 0.0;
    m[M4_ENTRY(2, 0)] = 0.0;
    m[M4_ENTRY(3, 0)] = 0.0;

    m[M4_ENTRY(0, 1)] = 0.0;
    m[M4_ENTRY(1, 1)] = y;
    m[M4_ENTRY(2, 1)] = 0.0;
    m[M4_ENTRY(3, 1)] = 0.0;

    m[M4_ENTRY(0, 2)] = 0.0;
    m[M4_ENTRY(1, 2)] = 0.0;
    m[M4_ENTRY(2, 2)] = z;
    m[M4_ENTRY(3, 2)] = 0.0;

    m[M4_ENTRY(0, 3)] = 0.0;
    m[M4_ENTRY(1, 3)] = 0.0;
    m[M4_ENTRY(2, 3)] = 0.0;
    m[M4_ENTRY(3, 3)] = 1.0;
}*/

void translate_matrix4_s(mat4 m, float dx, float dy, float dz)
{
    m[M4_ENTRY(0, 0)] = 1.0;
    m[M4_ENTRY(1, 0)] = 0.0;
    m[M4_ENTRY(2, 0)] = 0.0;
    m[M4_ENTRY(3, 0)] = 0.0;

    m[M4_ENTRY(0, 1)] = 0.0;
    m[M4_ENTRY(1, 1)] = 1.0;
    m[M4_ENTRY(2, 1)] = 0.0;
    m[M4_ENTRY(3, 1)] = 0.0;

    m[M4_ENTRY(0, 2)] = 0.0;
    m[M4_ENTRY(1, 2)] = 0.0;
    m[M4_ENTRY(2, 2)] = 1.0;
    m[M4_ENTRY(3, 2)] = 0.0;

    m[M4_ENTRY(0, 3)] = dx;
    m[M4_ENTRY(1, 3)] = dy;
    m[M4_ENTRY(2, 3)] = dz;
    m[M4_ENTRY(3, 3)] = 1.0;
}


void column_matrix4_linear_transpose
    (mat4 m, const vec3 *u, const vec3 *v, const vec3 *w)
{
    m[M4_ENTRY(0, 0)]   = u->x;
    m[M4_ENTRY(1, 0)]   = v->x;
    m[M4_ENTRY(2, 0)]   = w->x;
    m[M4_ENTRY(3, 0)]   = 0.0;

    m[M4_ENTRY(0, 1)]   = u->y;
    m[M4_ENTRY(1, 1)]   = v->y;
    m[M4_ENTRY(2, 1)]   = w->y;
    m[M4_ENTRY(3, 1)]   = 0.0;

    m[M4_ENTRY(0, 2)]   = u->z;
    m[M4_ENTRY(1, 2)]   = v->z;
    m[M4_ENTRY(2, 2)]   = w->z;
    m[M4_ENTRY(3, 2)]   = 0.0;

    m[M4_ENTRY(0, 3)]   = 0.0;
    m[M4_ENTRY(1, 3)]   = 0.0;
    m[M4_ENTRY(2, 3)]   = 0.0;
    m[M4_ENTRY(3, 3)]   = 1.0;
}

void column_matrix4_linear_transpose_affine
    (mat4 m, const vec3 *u, const vec3 *v, const vec3 *w, const vec3 *p)
{
    m[M4_ENTRY(0, 0)]   = u->x;
    m[M4_ENTRY(1, 0)]   = v->x;
    m[M4_ENTRY(2, 0)]   = w->x;
    m[M4_ENTRY(3, 0)]   = 0.0;

    m[M4_ENTRY(0, 1)]   = u->y;
    m[M4_ENTRY(1, 1)]   = v->y;
    m[M4_ENTRY(2, 1)]   = w->y;
    m[M4_ENTRY(3, 1)]   = 0.0;

    m[M4_ENTRY(0, 2)]   = u->z;
    m[M4_ENTRY(1, 2)]   = v->z;
    m[M4_ENTRY(2, 2)]   = w->z;
    m[M4_ENTRY(3, 2)]   = 0.0;

    m[M4_ENTRY(0, 3)]   = p->x;
    m[M4_ENTRY(1, 3)]   = p->y;
    m[M4_ENTRY(2, 3)]   = p->z;
    m[M4_ENTRY(3, 3)]   = 1.0;
}

void column_matrix4_linear_affine
    (mat4 m, const vec3 *u, const vec3 *v, const vec3 *w, const vec3 *p)
{
    m[M4_ENTRY(0, 0)]   = u->x;
    m[M4_ENTRY(1, 0)]   = u->y;
    m[M4_ENTRY(2, 0)]   = u->z;
    m[M4_ENTRY(3, 0)]   = 0.0;

    m[M4_ENTRY(0, 1)]   = v->x;
    m[M4_ENTRY(1, 1)]   = v->y;
    m[M4_ENTRY(2, 1)]   = v->z;
    m[M4_ENTRY(3, 1)]   = 0.0;

    m[M4_ENTRY(0, 2)]   = w->x;
    m[M4_ENTRY(1, 2)]   = w->y;
    m[M4_ENTRY(2, 2)]   = w->z;
    m[M4_ENTRY(3, 2)]   = 0.0;

    m[M4_ENTRY(0, 3)]   = p->x;
    m[M4_ENTRY(1, 3)]   = p->y;
    m[M4_ENTRY(2, 3)]   = p->z;
    m[M4_ENTRY(3, 3)]   = 1.0;
}

void row_scale_matrix4
    (mat4 m, float scale, const vec4 *a, const vec4 *b, const vec4 *c, const vec4 *d)
{
    // this can be made much faster with SSE
    m[M4_ENTRY(0, 0)]   = scale * a->x;
    m[M4_ENTRY(1, 0)]   = scale * a->y;
    m[M4_ENTRY(2, 0)]   = scale * a->z;
    m[M4_ENTRY(3, 0)]   = a->w;

    m[M4_ENTRY(0, 1)]   = scale * b->x;
    m[M4_ENTRY(1, 1)]   = scale * b->y;
    m[M4_ENTRY(2, 1)]   = scale * b->z;
    m[M4_ENTRY(3, 1)]   = b->w;

    m[M4_ENTRY(0, 2)]   = scale * c->x;
    m[M4_ENTRY(1, 2)]   = scale * c->y;
    m[M4_ENTRY(2, 2)]   = scale * c->z;
    m[M4_ENTRY(3, 2)]   = c->w;

    m[M4_ENTRY(0, 3)]   = d->x;
    m[M4_ENTRY(1, 3)]   = d->y;
    m[M4_ENTRY(2, 3)]   = d->z;
    m[M4_ENTRY(3, 3)]   = d->w;
}


bool project2_4 (vec2 *v, mat4 m, vec4 *w)
{
    vec4 t;

    matrix_mult_vector4(&t, m, w);

    v->x    = t.x / t.w;
    v->y    = t.y / t.w;

    float depth = t.z / t.w;

    return -1.0 <= v->x && v->x <= 1.0
        && -1.0 <= v->y && v->y <= 1.0
        && 0.0 <= depth && depth <= 1.0;
}