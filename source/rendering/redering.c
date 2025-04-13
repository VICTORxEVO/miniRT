/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redering.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:10:12 by sgouzi            #+#    #+#             */
/*   Updated: 2025/04/13 12:09:28 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_smallest_if(double *smallest, t_inter it)
{
	if (it.t1 < *smallest && it.t1 > 0)
		*smallest = it.t1;
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

t_color	get_anti_aliased_color(double x, double y)
{
	t_core		*engine;
	t_color		final_clr;
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
		final_clr = rgb_add(final_clr, intersect_world(engine->w, &ray), 0);
	}
	final_clr = rgb_scl(final_clr, 1 / i);
	return (final_clr);
}

t_color	get_px_color(double x, double y)
{
	t_color	final_clr;

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
