# include "miniRT.h"

void save_to_img(t_color px_color, int x, int y)
{
    t_core      *engine;

	engine = getengine();
	int index = (y * SCREEN_WIDTH + x) * 3;
	engine->png[index] = px_color.r;
	engine->png[index + 1] = px_color.g;
	engine->png[index + 2] = px_color.b;
}

t_vec get_cube_norm(t_object *o, t_vec pt_on_cube)
{
    t_cube *cube = (t_cube *)o->data;
    t_vec local_point = (vec_sub(pt_on_cube, cube->origin));
    
    double maxc = maxf(fabs(local_point.x), maxf(fabs(local_point.y), fabs(local_point.z)));
    
    if (maxc == fabs(local_point.x))
        return (t_vec){local_point.x > 0 ? 1 : -1, 0, 0};
    else if (maxc == fabs(local_point.y))
        return (t_vec){0, local_point.y > 0 ? 1 : -1, 0};
    return (t_vec){0, 0, local_point.z > 0 ? 1 : -1};
}


t_vec cube_normal_at(t_cube *cube, t_vec world_point)
{
    // Transform point to object space
    t_vec local_point = vec_sub(world_point, cube->origin);
    
    // Find the largest component
    double maxc = maxf(fabs(local_point.x), maxf(fabs(local_point.y), fabs(local_point.z)));
    
    if (maxc == fabs(local_point.x))
        return (t_vec){local_point.x > 0 ? 1 : -1, 0, 0};
    else if (maxc == fabs(local_point.y))
        return (t_vec){0, local_point.y > 0 ? 1 : -1, 0};
    else
        return (t_vec){0, 0, local_point.z > 0 ? 1 : -1};
}
void check_axis(double origin, double direction, double *tmin, double *tmax)
{
    double tmin_numerator = (-1 - origin);
    double tmax_numerator = (1 - origin);
    
    if (fabs(direction) >= EPSILON)
    {
        *tmin = tmin_numerator / direction;
        *tmax = tmax_numerator / direction;
    }
    else
    {
        *tmin = tmin_numerator * __FLT_MAX__;
        *tmax = tmax_numerator * __FLT_MAX__;
    }
    
    // Ensure tmin is less than tmax
    if (*tmin > *tmax)
    {
        double temp = *tmin;
        *tmin = *tmax;
        *tmax = temp;
    }
}
t_inter cube_intersect(t_cube *cube, t_ray *ray)
{
    // Transform ray to object space
	t_inter	it;
    t_vec oc = vec_sub(ray->origin, cube->origin);
    
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
double get_obj_reflect(t_object *o)
{
	if (o->type == SP_OBJ)
		return ((t_sphere *)o->data)->reflect;
	else if (o->type == PL_OBJ)
		return ((t_plane *)o->data)->reflect;
	else if (o->type == CY_OBJ)
		return ((t_cylinder *)o->data)->reflect;
	return 0.f;
}
