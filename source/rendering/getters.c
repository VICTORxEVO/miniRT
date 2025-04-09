#include "miniRT.h"

t_vec	cy_normal(t_cylinder *cy, t_vec world_point)
{
	t_vec	camera_pos;
	t_vec	local_point;
	t_vec	local_camera;
	double	vector_len;
	double	camera_dist_sq;
	bool	camera_inside;
	double	dist_to_top;
	double	dist_to_bottom;
	t_vec	norm;
	t_vec	projected;

	camera_pos = getengine()->w->cam->origin;
	local_point = vec_sub(world_point, cy->origin);
	local_camera = vec_sub(camera_pos, cy->origin);
	// Check if camera is inside cylinder
	vector_len = vec_len(vec_sub(local_camera, (vec_scl(cy->normal,
						vec_dot(local_camera, cy->normal)))));
	camera_dist_sq = vector_len * vector_len;
	camera_inside = camera_dist_sq < (cy->diameter * cy->diameter / 4.0f);
	// Cap distances
	dist_to_top = vec_dot(local_point, cy->normal) - cy->height;
	dist_to_bottom = vec_dot(local_point, cy->normal);
	// Cap normals
	if (fabs(dist_to_top) < EPSILON)
	{
		norm = cy->normal;
	}
	else if (fabs(dist_to_bottom) < EPSILON)
	{
		norm = vec_neg(cy->normal);
	}
	else
	{
		// Body norm
		projected = vec_scl(cy->normal, vec_dot(local_point, cy->normal));
		norm = normal(vec_sub(local_point, (projected)));
	}
	// Flip normal if camera is inside
	if (camera_inside)
	{
		norm = vec_neg(norm);
	}
	return (norm);
}

t_vec	get_obj_norm(t_object *o, t_vec pt_on_obj)
{
	t_sphere	*s;

	if (o->type == PL_OBJ)
		return (normal(((t_plane *)o->data)->normal));
	else if (o->type == SP_OBJ)
	{
		s = (t_sphere *)o->data;
		return (normal(vec_sub(pt_on_obj, s->origin)));
	}
	else if (o->type == CY_OBJ)
		return (cy_normal(o->data, pt_on_obj));
	return ((t_vec){0, 0, 0});
}

t_color	get_obj_color(t_object *o)
{
	if (o->type == SP_OBJ)
		return (((t_sphere *)o->data)->c);
	else if (o->type == PL_OBJ)
		return (((t_plane *)o->data)->c);
	else
		return (((t_cylinder *)o->data)->c);
}

void	set_obj_color(t_object *o, t_color c)
{
	if (o->type == SP_OBJ)
		((t_sphere *)o->data)->c = c;
	else if (o->type == PL_OBJ)
		((t_plane *)o->data)->c = c;
	else
		((t_cylinder *)o->data)->c = c;
}

t_vec	get_obj_origin(t_object *o)
{
	if (o->type == SP_OBJ)
		return (((t_sphere *)o->data)->origin);
	else if (o->type == PL_OBJ)
		return (((t_plane *)o->data)->origin);
	else
		return (((t_cylinder *)o->data)->origin);
}
