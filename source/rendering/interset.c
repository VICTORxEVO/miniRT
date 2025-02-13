#include "miniRT.h"

t_vector cube_normal_at(t_cube *cube, t_point world_point)
{
    // Transform point to object space
    t_point local_point = v_to_p(sub_points(world_point, cube->origin));
    
    // Find the largest component
    double maxc = maxf(fabs(local_point.x), maxf(fabs(local_point.y), fabs(local_point.z)));
    
    if (maxc == fabs(local_point.x))
        return (t_vector){local_point.x > 0 ? 1 : -1, 0, 0};
    else if (maxc == fabs(local_point.y))
        return (t_vector){0, local_point.y > 0 ? 1 : -1, 0};
    else
        return (t_vector){0, 0, local_point.z > 0 ? 1 : -1};
}

t_inter cube_intersect(t_cube *cube, t_ray *ray)
{
    // Transform ray to object space
	t_inter	it;
    t_vector oc = sub_points(ray->origin, cube->origin);
    
    // Check intersections with all three axis pairs
    double xtmin, xtmax, ytmin, ytmax, ztmin, ztmax;
    it.t1 = -1;
    it.t2 = -1;
    check_axis(oc.x, ray->direction.x, &xtmin, &xtmax);
    check_axis(oc.y, ray->direction.y, &ytmin, &ytmax);
    check_axis(oc.z, ray->direction.z, &ztmin, &ztmax);
    
    // Find largest minimum t value
    double tmin = maxf(xtmin, maxf(ytmin, ztmin));
    // Find smallest maximum t value
    double tmax = minf(xtmax, minf(ytmax, ztmax));
    
    // If tmin > tmax, ray misses cube
	
    if (tmin > tmax || tmax < 0)
        return it;
    it.t1 = tmin;
    it.t2 = tmax;
    // Return nearest intersection
	if (tmin < 0)
		swapf(&it.t1, &it.t2);
    return it;
}

t_inter sp_intersect(t_sphere *s, t_ray *ray)
{
    t_vector oc;
    double a;
    double b;
    double c;
    double d;
	t_inter	it;
	double tp;

	it.t1 = -1;
	it.t2 = -1;
    oc = sub_points(ray->origin, s->origin);
    a = dot(ray->direction, ray->direction);
    b = 2.0f * dot(ray->direction, oc);
    c = dot(oc, oc) - s->radius_squared;

    d = (b * b) - (4.0f * a * c);
	if (d <= 0 || fabs(a) < EPSILON)
		return it;
    it.t1 = (-b - sqrtf(d)) / (2.0f * a);
    it.t2 = (-b + sqrtf(d)) / (2.0f * a);
	if (it.t1 > it.t2)
		swapf(&it.t1, &it.t2);
	return it;
}

t_inter pl_intersect(t_plane *pl, t_ray *ray)
{
	double    denom;
    double t;
	t_inter	it;
    t_vector pl_to_ray;

	it.t1 = -1;
	it.t2 = -1;
    denom = dot(pl->normal, ray->direction);
    if (fabs(denom) < EPSILON)
        return it;
    pl_to_ray = sub_points(pl->origin, ray->origin);
    t = dot(pl_to_ray, pl->normal) / denom;
    if (t >= EPSILON)
	{
		it.t1 = t;
		it.t2 = t;
	}
	return it;
}

t_inter cy_intersect(t_cylinder *cy, t_ray *r)
{
    double a, b, c, d;
    double radius = cy->diameter / 2;
    double body_hit = -1;
    double bottom_hit = -1;
    double top_hit = -1;
    t_inter it = {-1, -1};

    t_vector X = sub_points(r->origin, cy->origin);

    // Cylinder body intersection
    a = dot(r->direction, r->direction) - pow(dot(r->direction, cy->normal), 2);
    b = 2 * (dot(r->direction, X) - dot(r->direction, cy->normal) * dot(X, cy->normal));
    c = dot(X, X) - pow(dot(X, cy->normal), 2) - (radius * radius);
    d = b*b - 4*a*c;

    if (d >= 0) {
        double sqrt_d = sqrtf(d);
        double t1 = (-b - sqrt_d) / (2 * a);
        double t2 = (-b + sqrt_d) / (2 * a);

        if (t1 > 0)
			body_hit = t1;
        else if (t2 > 0)
			body_hit = t2;

        // Validate body hit height
        if (body_hit > 0) {
            t_point hit_point = add_points(r->origin, v_to_p(scale_vector(r->direction, body_hit)));
            double height = dot(sub_points(hit_point, cy->origin), cy->normal);
            if (height < 0 || height > cy->height)
				body_hit = -1;
        }
    }

    // Bottom cap intersection
    double denom = dot(r->direction, cy->normal);
    if (fabs(denom) > EPSILON) {
        double t = -dot(X, cy->normal) / denom;
        if (t > 0) {
            t_point P = add_points(r->origin, v_to_p(scale_vector(r->direction, t)));
            if (get_len_vector(sub_points(P, cy->origin)) <= radius)
                bottom_hit = t;
        }
    }

    // Top cap intersection
    t_point top_center = add_points(cy->origin, v_to_p(scale_vector(cy->normal, cy->height)));
    X = sub_points(r->origin, top_center);
    if (fabs(denom) > EPSILON)
	{
        double t = -dot(X, cy->normal) / denom;
        if (t > 0)
		{
            t_point P = add_points(r->origin, v_to_p(scale_vector(r->direction, t)));
            if (get_len_vector(sub_points(P, top_center)) <= radius)
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

inline t_hit set_hit(double t1, double t2, t_object	*o)
{
	t_hit	hit;

	hit.t2 = t2;
	hit.t1 = t1;
	hit.obj = o;
	return hit;
}

t_color intersect_world(t_world *w, t_ray *cam_ray, int remaining)
{
	t_hit	hit;
    t_color color;
    t_color final;
	t_inter	it;
	hit.obj = NULL;
	t_object	*node;
	t_node	*light_node;
    t_light *light;
	double t;
	unsigned n_lights;
	hit.t1 = __FLT_MAX__;
	hit.t2 = __FLT_MAX__;
    light_node = w->lights;
	node = w->objects;
    final = zero_color();
	while (node)
	{
		if (node->type == SP_OBJ)
			it = sp_intersect(node->data, cam_ray);
		else if (node->type == PL_OBJ)
			it = pl_intersect(node->data, cam_ray);
		else if (node->type == CB_OBJ)
			it = cube_intersect(node->data, cam_ray);
		else if (node->type == CY_OBJ)
			it = cy_intersect(node->data, cam_ray);
		if (it.t1 <= hit.t1 && it.t1 > 0)
			hit = set_hit(it.t1, it.t2, node);
		node = node->next;
	}
    n_lights = 0;
    while (light_node)
    {
        light = light_node->data;
        color = lighting(cam_ray, hit.obj, hit.t1, remaining, light);
        final = add_colors(final, color, false);
        light_node = light_node->next;
        n_lights++;
    }
    final = scale_color(final, 1.f / n_lights, 0);
	return final;
}

bool is_shadowed(t_world *w, t_point p, t_light *light)
{
	t_ray offseted_p;
	t_vector offset;
	double inter_dist;
	double pt_to_light_dist;
    offset = scale_vector(normal(sub_points(light->p, p)), EPSILON);
    offseted_p.origin = add_points(p, v_to_p(offset));
    offseted_p.direction = normal(sub_points(light->p, p));
    pt_to_light_dist = get_len_vector(sub_points(light->p, p));
    inter_dist = get_intersect_dist(w, &offseted_p);
    if (inter_dist > EPSILON && inter_dist < pt_to_light_dist)
        return true;
	return false;
}
