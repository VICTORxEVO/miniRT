#include "miniRT.h"


t_vec co_normal(t_cone *cone, t_vec hit_point)
{
    double dist_along_axis = vec_dot(vec_sub(hit_point, cone->tip), cone->norm);
    
    // Corrected: Cap normal points OUTWARD (not inward)
    if (fabs(dist_along_axis - cone->height) < EPSILON)
        return cone->norm; // <- Changed from -cone->norm
    
    t_vec axis_point = vec_add(cone->tip, vec_scl(cone->norm, dist_along_axis));
    t_vec lateral = vec_sub(hit_point, axis_point);
    t_vec normal_dir = vec_sub(lateral, vec_scl(cone->norm, tan(cone->angle) * vec_len(lateral)));
    
    return normal(normal_dir);
}

t_vec cy_normal(t_cylinder *cy, t_vec world_point) 
{
    t_vec camera_pos = getengine()->w->cam->origin;
	t_vec local_point = vec_sub(world_point, cy->origin);
    t_vec local_camera = vec_sub(camera_pos, cy->origin);
    
    // Check if camera is inside cylinder
	double vector_len = vec_len(vec_sub(
        local_camera,(vec_scl(cy->normal, vec_dot(local_camera, cy->normal)))
    ));
    double camera_dist_sq = vector_len * vector_len;
    bool camera_inside = camera_dist_sq < (cy->diameter * cy->diameter / 4.0f);
    
    // Cap distances
    double dist_to_top = vec_dot(local_point, cy->normal) - cy->height;
    double dist_to_bottom = vec_dot(local_point, cy->normal);
    
    t_vec norm;
    
    // Cap normals
    if (fabs(dist_to_top) < EPSILON) {
        norm = cy->normal;
    } else if (fabs(dist_to_bottom) < EPSILON) {
        norm = vec_neg(cy->normal);
    } else {
        // Body norm
        t_vec projected = vec_scl(cy->normal, vec_dot(local_point, cy->normal));
        norm = normal(vec_sub(local_point, (projected)));
    }

    // Flip normal if camera is inside
    if (camera_inside) {
        norm = vec_neg(norm);
    }
    return norm;
}




t_vec get_obj_norm(t_object	*o, t_vec	pt_on_obj)
{
	t_sphere 	*s;

	if (o->type == PL_OBJ)
		return (normal(((t_plane *)o->data)->normal));
	else if (o->type == SP_OBJ)
	{
		s = (t_sphere *)o->data;
		return (normal(vec_sub(pt_on_obj, s->origin)));
	}
	else if (o->type == CB_OBJ)
        return cube_normal_at((t_cube *)o->data, pt_on_obj);
	else if (o->type == CY_OBJ)
		return (cy_normal(o->data, pt_on_obj));
	else if (o->type == CO_OBJ)
    {
		return (co_normal(o->data, pt_on_obj));
    }
	return (t_vec) {0,0,0};
}

t_color	get_obj_color(t_object *o)
{
	if (o->type == SP_OBJ)
		return ((t_sphere *)o->data)->c;
	else if (o->type == PL_OBJ)
		return ((t_plane *)o->data)->c;
	else if (o->type == CY_OBJ)
		return ((t_cylinder *)o->data)->c;
	else if (o->type == CO_OBJ)
		return ((t_cone *)o->data)->c;
	else return ((t_cube *)o->data)->c;
}
void set_obj_color(t_object *o, t_color c)
{
	if (o->type == SP_OBJ)
		((t_sphere *)o->data)->c = c;
	else if (o->type == PL_OBJ)
		((t_plane *)o->data)->c = c;
	else if (o->type == CO_OBJ)
		((t_cone *)o->data)->c = c;
    else
		((t_cube *)o->data)->c = c;

}

t_vec get_obj_origin(t_object *o)
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

