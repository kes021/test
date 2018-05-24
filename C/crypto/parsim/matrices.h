#ifndef MATRICES_HEADER
#define MATRICES_HEADER
#include <math.h>

#include "vectors.h"


/*      ABOUT PROJECTION MATRICES - READ BEFOR COMPLAINING
 *              THAT IT DOESN'T WORK!
 *
 *  We use a left handed coordinate system. ie. the camera looks at +infinity
 *  on the z axis. Further more our clipping cube is [0, 1] on the z-axis.
 *  Just like Direct3D does. This makes much more sense.
 *  Further more, not like Direct3D, (-1, -1) on the screen is the lower left
 *  corner.
 *
 *  What you need is a glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);
 */


// matrices are given in column first order
// as in opengl, use glLoadMatrix
// +-           -+
// | 0  4  8  12 |
// | 1  5  9  13 |
// | 2  6  10 14 |
// | 3  7  11 15 |
// +-           -+
typedef float mat2[4];
typedef float mat3[9];
typedef float mat4[16];

// "Zeile Zuerst, Spalte Später" does not translate well to english,
//  ie. "row first, column later"
#define M2_ENTRY(i, j) (j * 2 + i)
#define M3_ENTRY(i, j) (j * 3 + i)
#define M4_ENTRY(i, j) (j * 4 + i)


//  m = Id
static inline void identity2 (mat2 m)
{
    m[M2_ENTRY(0, 0)] = 1.0;
    m[M2_ENTRY(1, 0)] = 0.0;

    m[M2_ENTRY(0, 1)] = 0.0;
    m[M2_ENTRY(1, 1)] = 1.0;
}

static inline void identity3 (mat3 m)
{
    m[M3_ENTRY(0, 0)] = 1.0;
    m[M3_ENTRY(1, 0)] = 0.0;
    m[M3_ENTRY(2, 0)] = 0.0;

    m[M3_ENTRY(0, 1)] = 0.0;
    m[M3_ENTRY(1, 1)] = 1.0;
    m[M3_ENTRY(2, 1)] = 0.0;

    m[M3_ENTRY(0, 2)] = 0.0;
    m[M3_ENTRY(1, 2)] = 0.0;
    m[M3_ENTRY(2, 2)] = 1.0;
}

static inline void identity4 (mat4 m)
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

    m[M4_ENTRY(0, 3)] = 0.0;
    m[M4_ENTRY(1, 3)] = 0.0;
    m[M4_ENTRY(2, 3)] = 0.0;
    m[M4_ENTRY(3, 3)] = 1.0;
}

//  m = n * o
void matrix_mult2 (mat2 m, const mat2 n, const mat2 o);
void matrix_mult3 (mat3 m, const mat3 n, const mat3 o);
void matrix_mult4 (mat4 m, const mat4 n, const mat4 o);

// u = m * v
void matrix_mult_vector2 (vec2 *u, const mat2 m, const vec2 *v);
void matrix_mult_vector3 (vec3 *u, const mat3 m, const vec3 *v);
void matrix_mult_vector4 (vec4 *u, const mat4 m, const vec4 *v);

// u = mT * v
void matrix_transpose_mult_vector2 (vec2 *u, const mat2 m, const vec2 *v);
void matrix_transpose_mult_vector3 (vec3 *u, const mat3 m, const vec3 *v);
void matrix_transpose_mult_vector4 (vec4 *u, const mat4 m, const vec4 *v);

/*
 *  Linear matrix multiplications. Multiply only the linear part
 *  and copy the w component.
 */
void matrix_mult_vector4l (vec4 *u, const mat4 m, const vec4 *v);
void matrix_transpose_mult_vector4l (vec4 *u, const mat4 m, const vec4 *v);

void matrix_transpose4 (mat4 m, const mat4 n);
void matrix_inverse4 (mat4 m, const mat4 n);
void matrix_normal4 (mat4 m, const mat4 n);  // transpose inverse?

void orthogonal_matrix4
    (mat4 m, float left, float right, float bottom, float top, float znear, float zfar);

void perspective_matrix4
    (mat4 m, float fovy, float aspect, float zNear, float zFar);

void look_at_matrix4
    (mat4 m, const vec3 *position, const vec3 *look_at, const vec3 *top);

void view_in_matrix4
    (mat4 m, const vec3 *position, const vec3 *view, const vec3 *top);

void rotation_matrix4_v (mat4 m, float alpha, const vec3 *axis);
void scale_matrix4_v (mat4 m, float scale);
void translate_matrix4_v (mat4 m, const vec3 *delta);

/*
void rotation_matrix4_s (mat4 m, float alpha, float x, float y, float z);
void scale_matrix4_s (mat4 m, float x, float y, float z);
*/

void translate_matrix4_s (mat4 m, float dx, float dy, float dz);


void column_matrix4_linear_transpose
    (mat4 m, const vec3 *u, const vec3 *v, const vec3 *w);

void column_matrix4_linear_transpose_affine
    (mat4 m, const vec3 *u, const vec3 *v, const vec3 *w, const vec3 *p);

void column_matrix4_linear_affine
    (mat4 m, const vec3 *u, const vec3 *v, const vec3 *w, const vec3 *p);

void row_scale_matrix4
    (mat4 m, float scale, const vec4 *a, const vec4 *b, const vec4 *c, const vec4 *d);

#endif  /* MATRICES_HEADER */