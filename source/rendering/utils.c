/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:10:14 by sgouzi            #+#    #+#             */
/*   Updated: 2025/04/09 18:10:21 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	is_shadowed(t_world *w, t_vec p, t_light *light)
{
	t_ray	offseted_p;
	t_vec	offset;
	t_vec	to_light;
	t_vec	to_light_norm;
	double	inter_dist;
	double	pt_to_light_dist;

	to_light = vec_sub(light->p, p);
	to_light_norm = normal(to_light);
	pt_to_light_dist = vec_len(to_light);
	offset = vec_scl(to_light_norm, EPSILON);
	offseted_p.origin = vec_add(p, (offset));
	offseted_p.direction = to_light_norm;
	inter_dist = get_intersect_dist(w, &offseted_p);
	if (inter_dist > EPSILON && inter_dist < pt_to_light_dist)
		return (true);
	else
		return (false);
}

inline t_hit	set_hit(double t1, double t2, t_object *o)
{
	t_hit	hit;

	hit.t2 = t2;
	hit.t1 = t1;
	hit.obj = o;
	return (hit);
}

t_hit	find_hit(t_world *w, t_ray *cam_ray)
{
	t_hit		hit;
	t_inter		it;
	t_object	*node;

	hit.obj = NULL;
	hit.t1 = __FLT_MAX__;
	hit.t2 = __FLT_MAX__;
	node = w->objects;
	while (node)
	{
		if (node->type == SP_OBJ)
			it = sp_intersect(node->data, cam_ray);
		else if (node->type == PL_OBJ)
			it = pl_intersect(node->data, cam_ray);
		else if (node->type == CY_OBJ)
			it = cy_intersect(node->data, cam_ray);
		if (it.t1 <= hit.t1 && it.t1 > 0)
			hit = set_hit(it.t1, it.t2, node);
		node = node->next;
	}
	return (hit);
}

t_color	get_ambient(bool lighted, t_world *w, t_object *obj, t_color obj_clr)
{
	t_color	ambient_color;

	if (obj_clr.r == 0 && obj_clr.r == 0 && obj_clr.b == 0)
		return (zero_color());
	if (lighted)
		ambient_color = rgb_scl(rgb_mul(w->ambient->c, obj_clr), 0.1);
	else
	{
		if (obj)
			ambient_color = rgb_scl(rgb_mul(w->ambient->c, obj_clr), 0.1);
		else
			ambient_color = rgb_scl((w->ambient->c), 0.1);
	}
	return (ambient_color);
}

inline double	deg_to_rad(double deg)
{
	return (deg * M_PI / 180);
}
