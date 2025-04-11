/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:11:47 by ysbai-jo          #+#    #+#             */
/*   Updated: 2025/04/11 17:25:31 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	camera_handled(t_core *d, char **args)
{
	t_parse_cam	p_cam;

	p_cam.err = false;
	if (d->w->cam)
		return (printf("Error\ncant have more than 1 camera"), false);
	p_cam.cord = ft_split(args[1], ",");
	if (count_args(p_cam.cord) != 3 || !point_struct_filled(&p_cam.pcord,
			p_cam.cord))
		return (printf("Error\nbad camera point coordinates\n"), false);
	p_cam.vctr = ft_split(args[2], ",");
	if (count_args(p_cam.vctr) != 3 || !vector_struct_filled(&p_cam.vec3d,
			p_cam.vctr))
		return (printf("Error\nbad camera 3d vector"), false);
	p_cam.FOV = ft_atof(args[3], &p_cam.err);
	if (p_cam.err || (p_cam.FOV < 0 || p_cam.FOV > 180))
		return (printf("Error\nbad fov value for camera"), false);
	d->w->cam = galloc(sizeof(t_camera));
	d->w->cam->forward = normal(p_cam.vec3d);
	d->w->cam->origin = p_cam.pcord;
	d->w->cam->fov = p_cam.FOV;
	return (true);
}

bool	light_handled(t_core *d, char **args)
{
	t_parse_light	pl;

	pl.err = false;
	pl.cord = ft_split(args[1], ",");
	if (count_args(pl.cord) != 3 || !point_struct_filled(&pl.light_cord,
			pl.cord))
		return (printf("Error\nbad light point coordinates\n"), false);
	pl.light_value = ft_atof(args[2], &pl.err);
	if (pl.err || !between(pl.light_value, 0, 1))
		return (printf("Error\nlight value invalid\n"), false);
	pl.clrs = ft_split(args[3], ",");
	if (count_args(pl.clrs) != 3 || !color_struct_filled(&pl.light_color,
			pl.clrs))
		return (printf("Error\nlight color invalid\n"), false);
	pl.light = galloc(sizeof(t_light));
	pl.light->brightness = pl.light_value;
	pl.light->c = pl.light_color;
	pl.light->p = pl.light_cord;
	add_node(&d->w->lights, pl.light, e_light);
	return (true);
}

bool	plane_handled(t_core *d, char **args)
{
	t_parse_plane	p_plane;

	p_plane.cord = ft_split(args[1], ",");
	if (count_args(p_plane.cord) != 3
		|| !point_struct_filled(&p_plane.plane_cord, p_plane.cord))
		return (printf("bad plane origin point\n"), false);
	p_plane.vctr = ft_split(args[2], ",");
	if (count_args(p_plane.vctr) != 3
		|| !vector_struct_filled(&p_plane.plane_norm, p_plane.vctr))
		return (printf("bad plane 3d vector\n"), false);
	p_plane.clrs = ft_split(args[3], ",");
	if (count_args(p_plane.clrs) != 3
		|| !color_struct_filled(&p_plane.plane_color, p_plane.clrs))
		return (printf("bad plane color\n"), false);
	p_plane.plane = galloc(sizeof(t_plane));
	p_plane.plane->c = p_plane.plane_color;
	p_plane.plane->origin = p_plane.plane_cord;
	p_plane.plane->normal = p_plane.plane_norm;
	add_obj(&d->w->objects, p_plane.plane, PL_OBJ);
	return (true);
}

bool	sphere_handled(t_core *d, char **args)
{
	t_parse_sphere	p_shpere;

	p_shpere.err = false;
	p_shpere.cord = ft_split(args[1], ",");
	if (count_args(p_shpere.cord) != 3
		|| !point_struct_filled(&p_shpere.sphere_cord, p_shpere.cord))
		return (printf("Error\nsphere point invalid\n"), false);
	p_shpere.diameter = ft_atof(args[2], &p_shpere.err);
	p_shpere.clrs = ft_split(args[3], ",");
	if (count_args(p_shpere.clrs) != 3
		|| !color_struct_filled(&p_shpere.sphere_color, p_shpere.clrs))
		return (printf("Error\nsphere color invalid\n"), false);
	p_shpere.sphere = galloc(sizeof(t_sphere));
	p_shpere.sphere->c = p_shpere.sphere_color;
	p_shpere.sphere->origin = p_shpere.sphere_cord;
	p_shpere.sphere->diameter = p_shpere.diameter;
	p_shpere.sphere->radius_squared = (p_shpere.diameter / 2)
		* (p_shpere.diameter / 2);
	add_obj(&d->w->objects, p_shpere.sphere, SP_OBJ);
	return (true);
}
