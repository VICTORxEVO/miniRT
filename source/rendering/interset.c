#include "miniRT.h"


float sp_intersect(t_sphere *s, t_ray *ray)
{
    t_vector oc;
    float a;
    float b;
    float c;
    float d;
    float t1, t2;

    oc = sub_points(ray->origin, s->origin);
    a = dot(ray->direction, ray->direction);
    b = 2.0f * dot(ray->direction, oc);
    c = dot(oc, oc) - s->radius_squared;

    d = (b * b) - (4.0f * a * c);
	if (d <= 0 || fabs(a) < EPSILON)
		return -1;
    t1 = (-b - sqrtf(d)) / (2.0f * a);
    t2 = (-b + sqrtf(d)) / (2.0f * a);
	if (t1 < t2 && t1 >= 0)
		return t1;
	return t2;
}

float pl_intersect(t_plane *pl, t_ray *ray)
{
	float    denom;
    float t;
    t_vector pl_to_ray;

    denom = dot(pl->normal, ray->direction);
    if (fabs(denom) < EPSILON)
        return -1;
    pl_to_ray = sub_points(pl->origin, ray->origin);
    t = dot(pl_to_ray, pl->normal) / denom;
    if (t >= EPSILON)
        return t;
	return -1;
}
// a ← ray.direction.x² + ray.direction.z²
// # ray is parallel to the y axis
// return () if a is approximately zero
// b ← 2 * ray.origin.x * ray.direction.x +
// 2 * ray.origin.z * ray.direction.z
// c ← ray.origin.x² + ray.origin.z² - 1
// disc ← b² - 4 * a * c
// # ray does not intersect the cylinder
// return () if disc < 0
// # this is just a placeholder, to ensure the tests
// # pass that expect the ray to miss.
// return ( intersection(1, cylinder) )
// end function
float cy_intersect(t_cylinder	*cy, t_ray	*r)
{
	float	a;
	float	b;
	float	c;
	float	d;

	a = (r->direction.x * r->direction.x) + (r->direction.z * r->direction.z);
	return a;
}

inline t_hit set_hit(float d, t_object	*o)
{
	t_hit	hit;

	hit.d = d;
	hit.obj = o;
	return hit;
}

t_color intersect_world(t_world *w, t_ray *cam_ray, int remaining)
{
	t_hit	hit;
	hit.obj = NULL;
	t_object	*node;
	float t;
	hit.d = __FLT_MAX__;
	node = w->objects;
	while (node)
	{
		if (node->type == SP_OBJ)
		{
			t = sp_intersect(node->data, cam_ray);
			if (t <= hit.d && t > 0)
				hit = set_hit(t, node);
 		}
		else if (node->type == PL_OBJ)
		{
			t = pl_intersect(node->data, cam_ray);
			if (t <= hit.d && t >= 0)
				hit = set_hit(t, node);
		}
		node = node->next;
	}
	return lighting(cam_ray, hit.obj, hit.d, remaining);
}


bool is_shadowed(t_world *w, t_point p)
{
	t_light *light;
	t_ray offseted_p;
	t_vector offset;
	float inter_dist;
	float pt_to_light_dist;
	light = w->lights->data;
	offset = scale_vector(normal(sub_points(light->p, p)), EPSILON);
	offseted_p.origin = add_points(p, v_to_p(offset));
	offseted_p.direction = normal(sub_points(light->p, p));
	pt_to_light_dist = get_len_vector(sub_points(light->p, p));
	inter_dist = get_intersect_dist(w, &offseted_p);
	if (inter_dist > EPSILON && inter_dist < pt_to_light_dist)
		return true;
	return false;
}
