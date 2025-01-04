#include "../includes/miniRT.h"
#include "../includes/math_lib.h"

inline float deg_to_rad(float deg)
{
    return (deg * M_PI / 180);
    // deg -> 180
    // rad -> PIE
}

inline float rad_to_rad(float rad)
{
    return (rad * 180 / M_PI);
    // deg -> 180
    // rad -> PIE
}

inline t_vector add_vectors(t_vector v1, t_vector v2)
{
    t_vector res_v;

    res_v.x = v1.x + v2.x;
    res_v.y = v1.y + v2.y;
    res_v.z = v1.z + v2.z;

    return res_v;
}

inline t_vector sub_vectors(t_vector v1, t_vector v2)
{
    t_vector res_v;

    res_v.x = v1.x - v2.x;
    res_v.y = v1.y - v2.y;
    res_v.z = v1.z - v2.z;
    return res_v;
}

/* [p1 - p2]*/
inline t_vector sub_points(t_point p1, t_point p2)
{
    t_vector res_p;

    res_p.x = p1.x - p2.x;
    res_p.y = p1.y - p2.y;
    res_p.z = p1.z - p2.z;
    return res_p;
}

inline t_vector neg_vector(t_vector v1)
{
    t_vector neg;

    neg.x = 0 - v1.x;
    neg.y = 0 - v1.y;
    neg.z = 0 - v1.z;
    return neg;
}

inline t_vector scale_vector(t_vector v, float scale)
{
    t_vector scaled;

    scaled.x = v.x * scale;
    scaled.y = v.y * scale;
    scaled.z = v.z * scale;
    return scaled;
}

inline t_vector shrink_vector(t_vector v, float shrink)
{
    t_vector shrinked;

    shrinked.x = v.x / shrink;
    shrinked.y = v.y / shrink;
    shrinked.z = v.z / shrink;
    return shrinked;
}

inline float get_len_vector(t_vector v1)
{
    float len;

    len = sqrtf(pow(v1.x, 2) + pow(v1.y, 2)+ pow(v1.z, 2));
    return len;
}

inline void print_vector(t_vector v)
{
    printf("t_vector => {%f, %f, %f}\n", v.x, v.y, v.z);
}

inline void print_point(t_point p)
{
    printf("t_point => {%f, %f, %f}\n", p.x, p.y, p.z);
}

inline t_vector get_normalized(t_vector v)
{
    t_vector normalized;
    float len;

    len = get_len_vector(v);
    normalized.x = v.x / len;
    normalized.y = v.y / len;
    normalized.z = v.z / len;
    return normalized;
}

/*
    the dot product is commutive A x B = B x A
*/
inline float dot(t_vector v1, t_vector v2)
{
    float dot;

    dot = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
    return dot;
}

/*  cross product -> 
    res vector being perpendicular to 
    the plane defined by the two original vectors. 
*/
/* this works for right hand only */
inline t_vector cross(t_vector v1, t_vector v2)
{
    t_vector res;
    res.x = v1.y * v2.z - v1.z * v2.y;
    res.y = v1.z * v2.x - v1.x * v2.z;
    res.z = v1.x * v2.y - v1.y * v2.x;
    return res;
}

inline t_vector normal_at(t_sphere s, t_point p)
{
    return get_normalized(sub_points(p, s.origin));
}
