#ifndef MATH_H
# define MATH_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct s_vec
{
	double x; // 1
	double y; // 0
	double z; // 0
}			t_vec;

typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;
}			t_ray;

#endif