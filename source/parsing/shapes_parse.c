/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:11:47 by ysbai-jo          #+#    #+#             */
/*   Updated: 2025/04/13 20:59:00 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	camera_handled(t_core *d, char **args)
{
	t_parse_cam	p_cam;

	p_cam.err = false;
	if (d->w->cam)
		return (pexit("Error\ncant have more than 1 camera!", 1), false);
	p_cam.cord = ft_split(args[1], ",");
	if (count_args(p_cam.cord) != 3 || !point_struct_filled(&p_cam.pcord,
			p_cam.cord))
		return (pexit("Error\nbad camera point coordinates\n!", 1), false);
	p_cam.vctr = ft_split(args[2], ",");
	if (count_args(p_cam.vctr) != 3 || !vector_struct_filled(&p_cam.vec3d,
			p_cam.vctr))
		return (pexit("Error\nbad camera 3d vector!", 1), false);
	p_cam.fov = ft_atof(args[3], &p_cam.err);
	if (p_cam.err || (p_cam.fov < 0 || p_cam.fov > 180))
		return (pexit("Error\nbad fov value for camera!", 1), false);
	d->w->cam = galloc(sizeof(t_camera));
	d->w->cam->forward = normal(p_cam.vec3d);
	d->w->cam->origin = p_cam.pcord;
	d->w->cam->fov = p_cam.fov;
	return (true);
}

bool	light_handled(t_core *d, char **args)
{
	t_parse_light	pl;

	pl.err = false;
	pl.cord = ft_split(args[1], ",");
	if (count_args(pl.cord) != 3 || !point_struct_filled(&pl.light_cord,
			pl.cord))
		return (pexit("Error\nbad light point coordinates!", 1), false);
	pl.light_value = ft_atof(args[2], &pl.err);
	if (pl.err || !between(pl.light_value, 0, 1))
		return (pexit("Error\nlight value invalid!", 1), false);
	pl.clrs = ft_split(args[3], ",");
	if (count_args(pl.clrs) != 3 || !color_struct_filled(&pl.light_color,
			pl.clrs))
		return (pexit("Error\nlight color invalid!", 1), false);
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
		return (pexit("bad plane origin point!", 1), false);
	p_plane.vctr = ft_split(args[2], ",");
	if (count_args(p_plane.vctr) != 3
		|| !vector_struct_filled(&p_plane.plane_norm, p_plane.vctr))
		return (pexit("bad plane 3d vector!", 1), false);
	p_plane.clrs = ft_split(args[3], ",");
	if (count_args(p_plane.clrs) != 3
		|| !color_struct_filled(&p_plane.plane_color, p_plane.clrs))
		return (pexit("bad plane color!", 1), false);
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
		return (pexit("Error\nsphere point invalid!", 1), false);
	p_shpere.diameter = ft_atof(args[2], &p_shpere.err);
	p_shpere.clrs = ft_split(args[3], ",");
	if (count_args(p_shpere.clrs) != 3
		|| !color_struct_filled(&p_shpere.sphere_color, p_shpere.clrs))
		return (pexit("Error\nsphere color invalid!", 1), false);
	p_shpere.sphere = galloc(sizeof(t_sphere));
	p_shpere.sphere->c = p_shpere.sphere_color;
	p_shpere.sphere->origin = p_shpere.sphere_cord;
	p_shpere.sphere->diameter = p_shpere.diameter;
	p_shpere.sphere->radius_squared = (p_shpere.diameter / 2)
		* (p_shpere.diameter / 2);
	add_obj(&d->w->objects, p_shpere.sphere, SP_OBJ);
	return (true);
}
