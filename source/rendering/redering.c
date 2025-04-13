/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redering.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:10:12 by sgouzi            #+#    #+#             */
/*   Updated: 2025/04/13 22:19:27 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_smallest_if(double *smallest, t_inter it)
{
	if (it.t1 < *smallest && it.t1 > 0)
		*smallest = it.t1;
}

t_color	get_anti_aliased_color(double x, double y)
{
	t_color		final;
	int			i;
	t_ray		ray;
	double		offset_x;
	double		offset_y;

	final = zero_color();
	ray.origin = getengine()->w->cam->origin;
	i = 0;
	while (i < RAYS_PX)
	{
		offset_x = (double)rand() / RAND_MAX - 0.5;
		offset_y = (double)rand() / RAND_MAX - 0.5;
		ray.direction = get_cam_dir(x + offset_x, y + offset_y, i);
		final = rgb_add(final, intersect_world(getengine()->w, &ray), 0);
		i++;
	}
	final = rgb_scl(final, 1.0 / RAYS_PX);
	return (final);
}

double	get_smallest_t(t_object *node, t_ray *ray)
{
	t_inter	it;
	double	smallest_t;

	it.t1 = -1;
	it.t2 = -1;
	smallest_t = __FLT_MAX__;
	if (node->type == SP_OBJ)
	{
		it = sp_intersect((t_sphere *)(node->data), ray);
		set_smallest_if(&smallest_t, it);
	}
	else if (node->type == PL_OBJ)
	{
		it = pl_intersect((t_plane *)(node->data), ray);
		set_smallest_if(&smallest_t, it);
	}
	else if (node->type == CY_OBJ)
	{
		it = cy_intersect((t_cylinder *)(node->data), ray);
		set_smallest_if(&smallest_t, it);
	}
	return (smallest_t);
}

t_color	get_nonanti_aliased_color(double x, double y)
{
	t_core		*engine;
	t_color		final_clr;
	t_camera	*cam;
	t_ray		ray;

	engine = getengine();
	cam = engine->w->cam;
	final_clr = zero_color();
	ray.origin = cam->origin;
	ray.direction = get_cam_dir(x, y, 0);
	final_clr = rgb_add(final_clr, intersect_world(engine->w, &ray), 0);
	return (final_clr);
}

t_color	get_px_color(double x, double y)
{
	t_color	final_clr;
	t_core	*engine;

	engine = getengine();
	if (RAYS_PX < 2)
		final_clr = get_nonanti_aliased_color(x, y);
	else
		final_clr = get_anti_aliased_color(x, y);
	return (final_clr);
}
