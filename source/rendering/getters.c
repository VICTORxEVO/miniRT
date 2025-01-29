#include "miniRT.h"

t_vector get_obj_norm(t_object	*o, t_point	pt_on_sphere)
{
	t_sphere *s;

	if (o->type == PL_OBJ)
		return (normal(((t_plane *)o->data)->normal));
	else if (o->type == SP_OBJ)
	{
		s = (t_sphere *)o->data;
		return (normal(sub_points(pt_on_sphere, s->origin)));
	}
	return (t_vector) {0,0,0};
}

t_color	get_obj_color(t_object *o)
{
	if (o->type == SP_OBJ)
		return ((t_sphere *)o->data)->c;
	else
		return ((t_plane *)o->data)->c;
}
void set_obj_color(t_object *o, t_color c)
{
	if (o->type == SP_OBJ)
		((t_sphere *)o->data)->c = c;
	else
		((t_plane *)o->data)->c = c;

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
	else return (NULL);
}
void set_obj_pattern(t_object *o, t_pattern *p)
{
	if (o->type == SP_OBJ)
		((t_sphere *)o->data)->pattern = p;
	else
		((t_plane *)o->data)->pattern = p;

}

float get_obj_reflect(t_object *o)
{
	if (o->type == SP_OBJ)
		return ((t_sphere *)o->data)->reflect;
	else if (o->type == PL_OBJ)
		return ((t_plane *)o->data)->reflect;
	return 0.f;
}
