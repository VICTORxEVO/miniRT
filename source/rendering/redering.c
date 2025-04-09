/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redering.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:10:12 by sgouzi            #+#    #+#             */
/*   Updated: 2025/04/09 18:10:13 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	get_intersect_dist(t_world *w, t_ray *ray)
{
	t_object	*node;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	t_inter		it;
	double		smallest_t;

	node = w->objects;
	smallest_t = __FLT_MAX__;
	while (node)
	{
		if (node->type == SP_OBJ)
		{
			sphere = (t_sphere *)(node->data);
			it = sp_intersect(sphere, ray);
			if (it.t1 < smallest_t && it.t1 > 0)
				smallest_t = it.t1;
		}
		else if (node->type == PL_OBJ)
		{
			plane = (t_plane *)(node->data);
			it = pl_intersect(plane, ray);
			if (it.t1 < smallest_t && it.t1 > 0)
				smallest_t = it.t1;
		}
		else if (node->type == CY_OBJ)
		{
			cylinder = (t_cylinder *)(node->data);
			it = cy_intersect(cylinder, ray);
			if (it.t1 < smallest_t && it.t1 > 0)
				smallest_t = it.t1;
		}
		node = node->next;
	}
	return (smallest_t);
}

t_vec get_cam_dir(double x, double y, int i)
{
	t_camera	*cam;
	t_vec dir;
	t_core	*engine;
	double		aa_factor;
	double		scale;
	double		ndc_x;
	double		ndc_y;

	engine = getengine();
	cam = engine->w->cam;
	aa_factor = 1 / engine->rays_px;
	scale = tan(deg_to_rad(cam->fov) / 2.f);
	ndc_x = (2.f * ((x + ((i * aa_factor) + 0.5f)) / SCREEN_WIDTH)) - 1.f;
	ndc_y = 1 - (2.f * (y + 0.5) / SCREEN_HEIGHT);
	dir = generate_cam_dir(cam, scale, ndc_x, ndc_y);
	return dir;
}

t_color	get_anti_aliased_color(double x, double y)
{
	t_core		*engine;
	t_color		final_clr;
	t_color		color;
	t_camera	*cam;
	double		i;
	t_ray		ray;

	i = -1;
	engine = getengine();
	cam = engine->w->cam;
	final_clr = zero_color();
	ray.origin = cam->origin;
	while (++i < engine->rays_px)
	{
		ray.direction = get_cam_dir(x, y, i);
		color = intersect_world(engine->w, &ray);
		final_clr = rgb_add(final_clr, color, 0);
	}
	final_clr = rgb_scl(final_clr, 1 / i);
	return (final_clr);
}

t_color	get_px_color(double x, double y)
{
	t_core	*engine;
	t_color	final_clr;

	engine = getengine();
	final_clr = get_anti_aliased_color(x, y);
	return (final_clr);
}

void	rendering(void)
{
	t_core	*engine;
	int		x;
	int		y;
	t_color	px_color;

	engine = getengine();
	init_hooks(engine);
	engine->img.img = mlx_new_image(engine->m.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	engine->img.addr = mlx_get_data_addr(engine->img.img,
			&engine->img.bits_per_pixel, &engine->img.line_length,
			&engine->img.endian);
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			px_color = get_px_color(x, y);
			my_mlx_pixel_put(&engine->img, x, y, get_clr_int(px_color));
			x += engine->iter;
		}
		y += engine->iter;
	}
	mlx_hooks();
	return ;
}
