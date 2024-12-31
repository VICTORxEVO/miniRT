#ifndef MATH_H
#define MATH_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct s_vector
{
    float x; // 1
    float y; // 0
    float z; // 0
} t_vector;

typedef struct s_point
{
    float x;
    float y;
    float z;
} t_point;

typedef struct s_ray
{
    t_point origin;
    t_vector direction;
} t_ray;

#endif