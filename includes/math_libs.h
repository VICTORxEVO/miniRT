#ifndef MATH_H
#define MATH_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct s_vector
{
    double x; // 1
    double y; // 0
    double z; // 0
} t_vector;

typedef struct s_point
{
    double x;
    double y;
    double z;
} t_point;

typedef struct s_ray
{
    t_point origin;
    t_vector direction;
} t_ray;


#endif