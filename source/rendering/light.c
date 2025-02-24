#include "miniRT.h"

t_color	calc_diffuse(t_vec point, t_light *light, t_object	*hit_obj, t_color	obj_clr, t_vec obj_norm)
{
	double light_dot_norm;
	double light_point_dist;
	double light_factor;
	t_color	diffuse_color;
	t_vec	pt_light_vec; // ray from point to light
	t_vec	pt_light_vec_norm; // ray from point to light
	pt_light_vec = vec_sub(light->p, point);
	pt_light_vec_norm = normal(pt_light_vec);
	diffuse_color = zero_color();
	light_dot_norm = vec_dot(obj_norm, pt_light_vec_norm);
	if (light_dot_norm >= 0)
	{
		light_point_dist = vec_len(pt_light_vec);
		light_factor = light_dot_norm * light->brightness * LIGHT_FACTOR / light_point_dist;
		diffuse_color = rgb_mul(obj_clr, light->c);
		diffuse_color = rgb_scl(diffuse_color, light_factor);
	}
	return diffuse_color;
}

t_color	calc_specular(t_vec point, t_vec	pt_cam_vec_norm,  t_light	*light, t_object	*obj, t_color	obj_clr, t_vec obj_norm)
{
	t_color	speclar_color;
	t_color	light_color;
	double light_dist;
	double specular_factor;
	double light_dot_norm;
	double brightness_factor;
	double refl_dot_cam;
	t_vec	pt_light_vec; // ray from point to light
	t_vec	pt_light_vec_norm;
	t_vec	light_ref;

	speclar_color = zero_color();
	pt_light_vec = vec_sub(light->p, point);
	pt_light_vec_norm = normal(pt_light_vec);
	light_ref = reflect(pt_light_vec_norm, obj_norm);
	refl_dot_cam = vec_dot(normal(light_ref), pt_cam_vec_norm) ;
	light_dot_norm = vec_dot(obj_norm, pt_light_vec_norm);
	// just added light_dot_norm >= 0 && please be careful
	if (light_dot_norm >= 0 && refl_dot_cam > 0 && light->brightness > 0)
	{
		brightness_factor = get_brightness(obj_clr) / 255.f;
		light_dist = vec_len(pt_light_vec);
		brightness_factor  = brightness_factor * 100 / light_dist;
		light_color = rgb_scl(light->c, light->brightness * brightness_factor);
		specular_factor = powf(refl_dot_cam, light->brightness * 100);
		speclar_color = rgb_mul(light_color, obj_clr);
		speclar_color = rgb_scl(speclar_color, specular_factor);
 	}
	return (speclar_color);
}

t_vec	prepare_obj_norm(t_object	*hit_obj, t_vec	point, t_vec	pt_cam_vec_norm)
{
	double cam_ray_surf_norm_dot;
	t_vec	obj_norm;

	obj_norm = hit_obj->get_norm(hit_obj, point);
	cam_ray_surf_norm_dot = vec_dot(pt_cam_vec_norm, obj_norm);
	if (cam_ray_surf_norm_dot > 0)
		obj_norm = vec_neg(obj_norm);
	return obj_norm;
}

t_color	lighting(t_ray *cam_ray, t_object *hit_obj, double smallest_t, t_light	*light, bool *lighted, t_color *obj_clr_with_pat)
{
	t_color	color;
    t_color ambient_color;
	t_color	speclar_color;
	t_color	diffuse_color;
	t_color	obj_clr;
	t_world	*w;
	t_vec	pt_cam_vec_norm; // ray from camera to a point
	t_vec	obj_norm; // ray from object origin to a point
	t_vec	point;

	w = getengine()->w;
	ambient_color = rgb_scl(w->ambient->c, w->ambient->ratio * 0.1);
	speclar_color = zero_color();
	point = position_at(cam_ray, smallest_t);
	obj_clr = handle_object_pat(hit_obj, point);
	*obj_clr_with_pat = obj_clr;
	pt_cam_vec_norm = normal(vec_sub(point, cam_ray->origin)); 
	obj_norm = prepare_obj_norm(hit_obj, point, pt_cam_vec_norm);
	if (is_shadowed(w, position_at(cam_ray, smallest_t), light))
		return rgb_scl(rgb_mul(obj_clr, ambient_color), 0.1);
	*lighted = true;
	diffuse_color = calc_diffuse(point, light, hit_obj, obj_clr, obj_norm);
	speclar_color = calc_specular(point, pt_cam_vec_norm, light, hit_obj, obj_clr, obj_norm);
	color = rgb_add(speclar_color , diffuse_color, false);
	return color;
}
