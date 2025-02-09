#include "miniRT.h"

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
t_vector get_cylinder_normal(t_cylinder *cy, t_point world_point) {
    t_point camera_pos = getengine()->w->cam->origin;
	t_vector local_point_v = sub_points(world_point, cy->origin);
    t_point local_point = v_to_p(local_point_v);
    t_vector local_camera_v = sub_points(camera_pos, cy->origin);
    t_point local_camera = v_to_p(local_camera_v);
    
    // Check if camera is inside cylinder
	double vector_len = get_len_vector(sub_points(
        local_camera,
        v_to_p(scale_vector(cy->normal, dot(local_camera_v, cy->normal)))
    ));
    double camera_dist_sq = vector_len * vector_len;
    bool camera_inside = camera_dist_sq < (cy->diameter * cy->diameter / 4.0f);
    
    // Cap distances
    double dist_to_top = dot(local_point_v, cy->normal) - cy->height;
    double dist_to_bottom = dot(local_point_v, cy->normal);
    
    t_vector norm;
    
    // Cap normals
    if (fabs(dist_to_top) < EPSILON) {
        norm = cy->normal;
    } else if (fabs(dist_to_bottom) < EPSILON) {
        norm = neg_vector(cy->normal);
    } else {
        // Body norm
        t_vector projected = scale_vector(cy->normal, dot(local_point_v, cy->normal));
        norm = normal(sub_points(local_point, v_to_p(projected)));
    }

    // Flip normal if camera is inside
    if (camera_inside) {
        norm = neg_vector(norm);
    }

    return norm;
}

t_vector get_obj_norm(t_object	*o, t_point	pt_on_obj)
{
	t_sphere 	*s;
	t_cylinder *cy;

	if (o->type == PL_OBJ)
		return (normal(((t_plane *)o->data)->normal));
	else if (o->type == SP_OBJ)
	{
		s = (t_sphere *)o->data;
		return (normal(sub_points(pt_on_obj, s->origin)));
	}
	else if (o->type == CB_OBJ)
        return cube_normal_at((t_cube *)o->data, pt_on_obj);
	else if (o->type == CY_OBJ)
		return (get_cylinder_normal(o->data, pt_on_obj));
	return (t_vector) {0,0,0};
}

t_color	get_obj_color(t_object *o)
{
	if (o->type == SP_OBJ)
		return ((t_sphere *)o->data)->c;
	else if (o->type == PL_OBJ)
		return ((t_plane *)o->data)->c;
	else if (o->type == CY_OBJ)
		return ((t_cylinder *)o->data)->c;
	else return ((t_cube *)o->data)->c;
}
void set_obj_color(t_object *o, t_color c)
{
	if (o->type == SP_OBJ)
		((t_sphere *)o->data)->c = c;
	else if (o->type == PL_OBJ)
		((t_plane *)o->data)->c = c;
	else
		((t_cube *)o->data)->c = c;

}

t_point get_obj_origin(t_object *o)
{
	if (o->type == SP_OBJ)
		return ((t_sphere *)o->data)->origin;
	else
		return ((t_plane *)o->data)->origin;
}

t_pattern	*get_obj_pattern(t_object	*o)
{
	if (o->type == SP_OBJ)
		return ((t_sphere *)o->data)->pattern;
	else if (o->type == PL_OBJ)
		return ((t_plane *)o->data)->pattern;
	else if (o->type == CY_OBJ)
		return (NULL);
	else return (NULL);
}
void set_obj_pattern(t_object *o, t_pattern *p)
{
	if (o->type == SP_OBJ)
		((t_sphere *)o->data)->pattern = p;
	else
		((t_plane *)o->data)->pattern = p;

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
