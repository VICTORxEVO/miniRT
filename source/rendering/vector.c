#include "../includes/miniRT.h"

inline t_vec	normal(t_vec v)
{
	t_vec	norm;
	double	len;

	len = vec_len(v);
	norm.x = v.x / len;
	norm.y = v.y / len;
	norm.z = v.z / len;
	return (norm);
}

inline t_vec	position_at(t_ray *r, double t)
{
	t_vec	p;

	p.x = r->direction.x * t + r->origin.x;
	p.y = r->direction.y * t + r->origin.y;
	p.z = r->direction.z * t + r->origin.z;
	return (p);
}

inline double	vec_dot(t_vec v1, t_vec v2)
{
	double	vec_dot;

	vec_dot = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return (vec_dot);
}

inline t_vec	cross(t_vec v1, t_vec v2)
{
	t_vec	res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}

inline t_vec	reflect(t_vec light, t_vec norm)
		// light is a vector from a point towards the light
{
	return (vec_sub(light, vec_scl(norm, 2 * vec_dot(norm, light))));
}
