/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:09:57 by sgouzi            #+#    #+#             */
/*   Updated: 2025/04/13 18:53:17 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	calc_diffuse(t_vec point, t_light *light, t_color obj_clr,
		t_vec obj_norm)
{
	double	light_dot_norm;
	double	light_factor;
	t_color	diffuse_color;
	t_vec	pt_light_vec;
	t_vec	pt_light_vec_norm;

	pt_light_vec = vec_sub(light->p, point);
	pt_light_vec_norm = normal(pt_light_vec);
	diffuse_color = zero_color();
	light_dot_norm = vec_dot(obj_norm, pt_light_vec_norm);
	if (light_dot_norm >= 0)
	{
		light_factor = light_dot_norm * light->brightness * LIGHT_FACTOR
			/ vec_len(pt_light_vec);
		diffuse_color = rgb_mul(obj_clr, light->c);
		diffuse_color = rgb_scl(diffuse_color, light_factor);
	}
	return (diffuse_color);
}

t_color	get_specular(t_light *light, t_color obj_clr, t_vec pt_light_vec,
		double refl_dot_cam)
{
	t_color	speclar_color;
	t_color	light_color;
	double	light_dist;
	double	specular_factor;
	double	brightness_factor;

	brightness_factor = get_brightness(obj_clr) / 255.f;
	light_dist = vec_len(pt_light_vec);
	brightness_factor = brightness_factor * pow(LIGHT_FACTOR, 2) / light_dist;
	light_color = rgb_scl(light->c, light->brightness * brightness_factor);
	specular_factor = powf(refl_dot_cam, light->brightness * pow(LIGHT_FACTOR,
				2));
	speclar_color = rgb_mul(light_color, obj_clr);
	speclar_color = rgb_scl(speclar_color, specular_factor);
	speclar_color = clamp_color(speclar_color);
	return (speclar_color);
}

t_color	calc_specular(t_vec point, t_vec pt_cam_vec_norm, t_light *light,
		t_object *obj)
{
	double	light_dot_norm;
	double	refl_dot_cam;
	t_vec	pt_light_vec;
	t_vec	light_ref;
	t_vec	obj_norm;

	obj_norm = prepare_obj_norm(obj, point, pt_cam_vec_norm);
	pt_light_vec = vec_sub(light->p, point);
	light_ref = reflect(normal(pt_light_vec), obj_norm);
	refl_dot_cam = vec_dot(normal(light_ref), pt_cam_vec_norm);
	light_dot_norm = vec_dot(obj_norm, normal(pt_light_vec));
	if (light_dot_norm >= 0 && refl_dot_cam > 0 && light->brightness > 0)
		return (get_specular(light, get_obj_color(obj), pt_light_vec,
				refl_dot_cam));
	return (zero_color());
}

t_vec	prepare_obj_norm(t_object *hit_obj, t_vec point, t_vec pt_cam_vec_norm)
{
	double	cam_ray_surf_norm_dot;
	t_vec	obj_norm;

	obj_norm = get_obj_norm(hit_obj, point);
	cam_ray_surf_norm_dot = vec_dot(pt_cam_vec_norm, obj_norm);
	if (cam_ray_surf_norm_dot > 0)
		obj_norm = vec_neg(obj_norm);
	return (obj_norm);
}

t_color	lighting(t_ray *cam_ray, t_object *hit_obj, t_calc *calc)
{
	t_phong	phong;
	t_world	*w;
	t_vec	p;
	t_vec	pt_cam_vec_norm;
	t_vec	obj_norm;

	w = getengine()->w;
	phong.ambient = rgb_scl(w->ambient->c, w->ambient->ratio * 0.1);
	phong.specular = zero_color();
	p = position_at(cam_ray, calc->smallest_t);
	pt_cam_vec_norm = normal(vec_sub(p, cam_ray->origin));
	obj_norm = prepare_obj_norm(hit_obj, p, pt_cam_vec_norm);
	calc->obj_clr = get_obj_color(hit_obj);
	if (is_shadowed(w, position_at(cam_ray, calc->smallest_t), calc->light))
		return (rgb_scl(rgb_mul(calc->obj_clr, phong.ambient), 0.1));
	calc->lighted = true;
	phong.diffuse = calc_diffuse(p, calc->light, calc->obj_clr, obj_norm);
	phong.specular = calc_specular(p, pt_cam_vec_norm, calc->light, hit_obj);
	return (rgb_add(phong.specular, phong.diffuse, false));
}
