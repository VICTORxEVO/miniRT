#include "../includes/miniRT.h"



inline t_vec vec_add(t_vec v1, t_vec v2)
{
    t_vec res_v;

    res_v.x = v1.x + v2.x;
    res_v.y = v1.y + v2.y;
    res_v.z = v1.z + v2.z;

    return res_v;
}

inline t_vec sub_vectors(t_vec v1, t_vec v2)
{
    t_vec res_v;

    res_v.x = v1.x - v2.x;
    res_v.y = v1.y - v2.y;
    res_v.z = v1.z - v2.z;
    return res_v;
}
/*
    p1 - p2  ->  vector from p2 to p1
*/
inline t_vec vec_sub(t_vec p1, t_vec p2)
{
    t_vec res_p;

    res_p.x = p1.x - p2.x;
    res_p.y = p1.y - p2.y;
    res_p.z = p1.z - p2.z;
    return res_p;
}
inline t_vec vec_neg(t_vec v1)
{
    t_vec neg;

    neg.x = 0 - v1.x;
    neg.y = 0 - v1.y;
    neg.z = 0 - v1.z;
    return neg;
}

inline t_vec vec_scl(t_vec v, double scale)
{
    t_vec scaled;

    scaled.x = v.x * scale;
    scaled.y = v.y * scale;
    scaled.z = v.z * scale;
    return scaled;
}

inline double vec_len(t_vec v1)
{
    double len;

    len = sqrtf(pow(v1.x, 2) + pow(v1.y, 2)+ pow(v1.z, 2));
    return len;
}

inline void vec_log(t_vec v)
{
    printf("t_vec => {%f, %f, %f}\n", v.x, v.y, v.z);
}

inline t_vec normal(t_vec v)
{
    t_vec norm;
    double len;

    len = vec_len(v);
    norm.x = v.x / len;
    norm.y = v.y / len;
    norm.z = v.z / len;
    return norm;
}

inline t_vec	position_at(t_ray	*r, double t)
{
	t_vec	p;
	p.x = r->direction.x * t + r->origin.x;
	p.y = r->direction.y * t + r->origin.y;
	p.z = r->direction.z * t + r->origin.z;
	return p;
}

/*
    the vec_dot product is commutive A x B = B x A
*/
inline double vec_dot(t_vec v1, t_vec v2)
{
    double vec_dot;

    vec_dot = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
    return vec_dot;
}

/*  cross product -> 
    res vector being perpendicular to 
    the plane defined by the two original vectors. 
*/
/* this works for right hand only */
inline t_vec cross(t_vec v1, t_vec v2)
{
    t_vec res;
    res.x = v1.y * v2.z - v1.z * v2.y;
    res.y = v1.z * v2.x - v1.x * v2.z;
    res.z = v1.x * v2.y - v1.y * v2.x;
    return res;
}

inline double deg_to_rad(double deg)
{
    return (deg * M_PI / 180);
    // deg -> 180
    // rad -> PIE
}

inline double rad_to_rad(double rad)
{
    return (rad * 180 / M_PI);
    // deg -> 180
    // rad -> PIE
}

inline t_vec	reflect (t_vec	light, t_vec	norm) // light is a vector from a point towards the light
{
	return vec_sub(light, vec_scl(norm, 2 * vec_dot(norm, light))); 
}
