#include "miniRT.h"

t_inter	sp_intersect(t_sphere *s, t_ray *ray)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	d;
	t_inter	it;

	it.t1 = -1;
	it.t2 = -1;
	oc = vec_sub(ray->origin, s->origin);
	a = vec_dot(ray->direction, ray->direction);
	b = 2.0f * vec_dot(ray->direction, oc);
	c = vec_dot(oc, oc) - s->radius_squared;
	d = (b * b) - (4.0f * a * c);
	if (d < 0 || fabs(a) < EPSILON)
		return (it);
	it.t1 = (-b - sqrt(d)) / (2.0f * a);
	it.t2 = (-b + sqrt(d)) / (2.0f * a);
	if (it.t1 < 0 && it.t2 > 0)
		it.t1 = it.t2;
	return (it);
}

t_inter	pl_intersect(t_plane *pl, t_ray *ray)
{
	double	denom;
	double	t;
	t_inter	it;
	t_vec	pl_to_ray;

	it.t1 = -1;
	it.t2 = -1;
	denom = vec_dot(pl->normal, ray->direction);
	if (fabs(denom) < EPSILON)
		return (it);
	pl_to_ray = vec_sub(pl->origin, ray->origin);
	t = vec_dot(pl_to_ray, pl->normal) / denom;
	if (t >= EPSILON)
	{
		it.t1 = t;
		it.t2 = t;
	}
	return (it);
}

t_inter cy_intersect(t_cylinder *cy, t_ray *r)
{
    double a, b, c, d;
    double radius = cy->diameter / 2;
    double body_hit = -1;
    double bottom_hit = -1;
    double top_hit = -1;
    t_inter it = {-1, -1};

    t_vec X = vec_sub(r->origin, cy->origin);

    // Cylinder body intersection
    a = vec_dot(r->direction, r->direction) - pow(vec_dot(r->direction, cy->normal), 2);
    b = 2 * (vec_dot(r->direction, X) - vec_dot(r->direction, cy->normal) * vec_dot(X, cy->normal));
    c = vec_dot(X, X) - pow(vec_dot(X, cy->normal), 2) - (radius * radius);
    d = b*b - 4*a*c;

    if (d >= 0) {
        double sqrt_d = sqrt(d);
        double t1 = (-b - sqrt_d) / (2 * a);
        double t2 = (-b + sqrt_d) / (2 * a);

        if (t1 > 0)
			body_hit = t1;
        else if (t2 > 0)
			body_hit = t2;

        // Validate body hit height
        if (body_hit > 0)
        {
            t_vec hit_point = vec_add(r->origin, (vec_scl(r->direction, body_hit)));
            double height = vec_dot(vec_sub(hit_point, cy->origin), cy->normal);
            if (height < 0 || height > cy->height)
				body_hit = -1;
        }
    }

    // Bottom cap intersection
    double denom = vec_dot(r->direction, cy->normal);
    if (fabs(denom) > EPSILON) {
        double t = -vec_dot(X, cy->normal) / denom;
        if (t > 0)
        {
            t_vec P = vec_add(r->origin, (vec_scl(r->direction, t)));
            if (vec_len(vec_sub(P, cy->origin)) <= radius)
                bottom_hit = t;
        }
    }

    // Top cap intersection
    t_vec top_center = vec_add(cy->origin, (vec_scl(cy->normal, cy->height)));
    X = vec_sub(r->origin, top_center);
    if (fabs(denom) > EPSILON)
	{
        double t = -vec_dot(X, cy->normal) / denom;
        if (t > 0)
		{
            t_vec P = vec_add(r->origin, (vec_scl(r->direction, t)));
            if (vec_len(vec_sub(P, top_center)) <= radius)
                top_hit = t;
        }
    }

    // Find closest valid hit
    double hits[] = {body_hit, bottom_hit, top_hit};
    double min_hit = __FLT_MAX__;
    for (int i = 0; i < 3; i++) {
        if (hits[i] > 0 && hits[i] < min_hit)
            min_hit = hits[i];
    }

    if (min_hit != __FLT_MAX__) {
        it.t1 = min_hit;
        it.t2 = min_hit;
    }
    return it;
}

t_color	intersect_world(t_world *w, t_ray *cam_ray)
{
	t_hit	hit;
	t_color	color;
	t_color	final;
	t_color	ambient_color;
	t_node	*light_node;
	t_calc	calc;

	light_node = w->lights;
	final = zero_color();
	hit = find_hit(w, cam_ray);
	calc.obj_clr = zero_color();
	while (light_node && hit.obj)
	{
		calc.light = light_node->data;
		calc.lighted = false;
		calc.smallest_t = hit.t1;
		color = lighting(cam_ray, hit.obj, &calc);
		final = rgb_add(final, color, false);
		light_node = light_node->next;
	}
	ambient_color = get_ambient(calc.lighted, w, hit.obj, calc.obj_clr);
	final = rgb_add(final, ambient_color, true);
	final = clamp_color(final);
	return (final);
}

double	get_intersect_dist(t_world *w, t_ray *ray)
{
	t_object	*node;
	double		smallest_t;

	smallest_t = __FLT_MAX__;
	node = w->objects;
	while (node)
	{
		smallest_t = get_smallest_t(node, ray);
		node = node->next;
	}
	return (smallest_t);
}
