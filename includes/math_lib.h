#ifndef MATH_H
#define MATH_H

#include "miniRT.h"
#include "render.h"


typedef struct s_camera t_camera;
typedef struct s_data t_data;
typedef struct s_mlx t_mlx;
typedef struct s_img t_img;
typedef struct s_sphere t_sphere;

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


t_vector add_vectors(t_vector v1, t_vector v2);
t_vector sub_vectors(t_vector v1, t_vector v2);
t_vector sub_points(t_point p1, t_point p2);
t_vector neg_vector(t_vector v1);
t_vector scale_vector(t_vector v, float scale);
t_vector shrink_vector(t_vector v, float shrink);
float get_len_vector(t_vector v1);
void print_vector(t_vector v);
void print_point(t_point p);
t_point	position_at(t_ray	*r, float t);
t_vector get_normalized(t_vector v);
float dot(t_vector v1, t_vector v2);
t_vector cross(t_vector v1, t_vector v2);
t_vector normal_at(t_sphere s, t_point p);
float deg_to_rad(float deg);
float rad_to_rad(float rad);
#endif