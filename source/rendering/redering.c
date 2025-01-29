# include "miniRT.h"

float get_intersect_dist(t_world *w, t_ray *ray)
{
	t_object	*node;
	t_sphere	*sphere;
	t_plane		*plane;
	float smallest_t;
	float t;
	node = w->objects;
	smallest_t = __FLT_MAX__;
	while (node)
	{
		if (node->type == SP_OBJ)
		{
			sphere = (t_sphere *)(node->data);
			t = sp_intersect(sphere, ray);
			if (t < smallest_t && t > 0)
				smallest_t = t;
 		}
		else if (node->type == PL_OBJ)
		{
			plane = (t_plane *)(node->data);
			t = pl_intersect(plane, ray);
			if (t < smallest_t && t > 0)
				smallest_t = t;
		}
		node = node->next;
	}
	return smallest_t;
}

t_color handle_object_pat(t_object *hit_obj, t_point inter_point)
{
	t_color	obj_color;
	float scale;
	float scaled_x;
	t_vector	moved_p;
	t_point p;
	t_pattern	*pattern;
	t_point	origin_p;
	float	diameter;

	if (hit_obj->type == SP_OBJ)
	{
		origin_p = ((t_sphere *)hit_obj->data)->origin;
		diameter = ((t_sphere *)hit_obj->data)->diameter;
	}
	else
	{
		origin_p = ((t_plane *)hit_obj->data)->origin;
		diameter = 5;
	}

	obj_color = hit_obj->get_color(hit_obj);
	if (hit_obj->get_pattern)
		pattern = hit_obj->get_pattern(hit_obj);
	if (pattern && pattern->type == CHECKER_PAT)
	{
		moved_p = sub_points(inter_point, origin_p);
		if (hit_obj->type == SP_OBJ)
			p = v_to_p(moved_p);
		else
			p = inter_point;
		if (hit_obj->type == PL_OBJ)
		{
			if (((int)floor(p.x * 0.5) + (int)floor(p.y * 0.5) + (int)floor(p.z * 0.5)) % 2 == 0)
				return pattern->c1;
			return pattern->c2;
		}
		// Normalize point to get direction vector
		float length = get_len_vector(moved_p);
		// Convert to UV coordinates
		float nx = p.x / length;
		float ny = p.y / length;
		float nz = p.z / length;

		float u = 0.5f + (atan2f(nz, nx) / (2.0f * M_PI));
		float v = 0.5f - (asinf(ny) / M_PI);
		
		// Create checkerboard pattern
		float scale = diameter * diameter;  // Adjust for checker size
		int check_u = (int)(u * scale);
		int check_v = (int)(v * scale);
		
		if ((check_u + check_v) % 2 == 0)
			obj_color = pattern->c1;
		else
			obj_color = pattern->c2;
	}
	else if (pattern && pattern->type == STRIPE_X_PAT)
	{
		p = (v_to_p(sub_points(inter_point, origin_p)));
		scale = 10;
		scaled_x = (int)((p.x / diameter) * scale);
		if ((int)scaled_x % 2 == 0)
			obj_color = pattern->c1;
		else
			obj_color = pattern->c2;
	}
	else if (pattern && pattern->type == GRADIANT_Y)
	{
		float fraction;
		p = v_to_p(sub_points(inter_point, origin_p));
		// Map to [-1,1] range first, then to [0,1]
		fraction = p.x / diameter;     // This gives us [-0.5, 0.5]
		fraction = fraction + 0.5;                     // Now [0,1]
		// Clamp fraction between 0 and 1
		fraction = fraction < 0 ? 0 : (fraction > 1 ? 1 : fraction);
		
		obj_color.r = (int)(pattern->c1.r * (1 - fraction) + pattern->c2.r * fraction);
		obj_color.g = (int)(pattern->c1.g * (1 - fraction) + pattern->c2.g * fraction);
		obj_color.b = (int)(pattern->c1.b * (1 - fraction) + pattern->c2.b * fraction);
	}
	else if (pattern && pattern->type == SWIRL)
	{
		moved_p = sub_points(inter_point, origin_p);
		p = v_to_p(moved_p);

		// Compute angle and distance for the swirl
		float angle = atan2f(p.y, p.x);
		float dist = sqrtf(p.x * p.x + p.y * p.y);
		
		// Swirl pattern factor
		float swirl = sinf(5.0f * angle + 3.0f * dist);
		// map swirl [-1,1] to [0,1]
		swirl = 0.5f * (swirl + 1.0f);

		// Blend colors
		obj_color.r = (int)(pattern->c1.r * (1.0f - swirl) + pattern->c2.r * swirl);
		obj_color.g = (int)(pattern->c1.g * (1.0f - swirl) + pattern->c2.g * swirl);
		obj_color.b = (int)(pattern->c1.b * (1.0f - swirl) + pattern->c2.b * swirl);
	}
	return obj_color;
}

t_color	get_reflect_color(int remaining, t_object *hit_obj, t_vector pt_cam_vec, t_point	inter_point)
{
	t_vector	obj_norm;
	t_ray	reflect_ray;
	t_point offseted_p;
	t_color reflected_clr;
	t_color obj_clr;
	t_vector offset;

	reflected_clr = zero_color();
	// handle_object_pat()
	if (getengine()->refl_on && remaining > 0)
	{
		obj_clr = hit_obj->get_color(hit_obj);
		obj_norm = hit_obj->get_norm(hit_obj, inter_point);
		offset = scale_vector(obj_norm, EPSILON);
		offseted_p = add_points(inter_point, v_to_p(offset));
		reflect_ray.origin = offseted_p;
		reflect_ray.direction = reflect(pt_cam_vec, obj_norm);
		reflected_clr = intersect_world(getengine()->w, &reflect_ray, remaining - 1);
		float reflect_strength = hit_obj->get_reflect(hit_obj) * (get_brightness(obj_clr) / 255.f);
		reflected_clr = scale_color(reflected_clr, reflect_strength);
	}
	return reflected_clr;
}

t_color	lighting(t_ray *cam_ray, t_object *hit_obj, float smallest_t, int remaining)
{
	if (!hit_obj)
		return ((t_color) {10, 10, 10});
	t_color	color;
	t_color	speclar_color;
	t_color	diffuse_color;
	t_color	ambient_color;
	t_color reflected_clr;
	t_light		*light;
	t_ambient	*ambient;
	float light_dot_norm;
	t_color	obj_clr;
	float cam_ray_surf_norm_dot;
	float refl_dot_cam;
	t_vector	pt_cam_vec;   // ray from camera to a point
	t_vector	obj_norm; // ray from object origin to a point
	t_vector	pt_light_vec; // ray from point to light
	t_vector	light_ref;
	t_point inter_point;
	light = getengine()->w->lights->data;
	ambient = getengine()->w->ambient;
	color = zero_color();
	speclar_color = zero_color();
	diffuse_color = zero_color();
	ambient_color = zero_color();
	inter_point = position_at(cam_ray, smallest_t);
	obj_clr = handle_object_pat(hit_obj, inter_point);
	ambient_color = scale_color(mul_colors(ambient->c, obj_clr), ambient->ratio * 0.1);
	if (is_shadowed(getengine()->w, inter_point))
		return ambient_color;
	pt_cam_vec = normal(sub_points(inter_point, cam_ray->origin)); 
	obj_norm = hit_obj->get_norm(hit_obj, inter_point);
	cam_ray_surf_norm_dot = dot(pt_cam_vec, obj_norm);
	if (cam_ray_surf_norm_dot > 0)
		obj_norm = neg_vector(obj_norm);
	reflected_clr = get_reflect_color(remaining, hit_obj, pt_cam_vec, inter_point);  // ! new
	pt_light_vec = normal(sub_points(light->p, inter_point));
	light_dot_norm = dot(obj_norm, pt_light_vec);
	if (light_dot_norm >= 0)
	{
		diffuse_color = scale_color(obj_clr, light_dot_norm * light->brightness);
		light_ref = reflect(pt_light_vec, obj_norm);
        refl_dot_cam = dot(normal(light_ref), pt_cam_vec);
        if (refl_dot_cam > 0 && light->brightness > 0)
			speclar_color = scale_color(scale_color(light->c, light->brightness * (get_brightness(obj_clr) / 255.f)), powf(refl_dot_cam, light->brightness * 100));
    }
	color = sum_colors(speclar_color ,diffuse_color, ambient_color);
	color = add_colors(color, reflected_clr, 1);
	if (getengine()->w->gray_on)
		return (rgb_to_gray(color));
	return color;
}

t_color	get_px_color(double x, double y, int remaining)
{
	t_core *engine;
	t_color	final_clr;
	t_color	temp_clr;
	t_camera	*cam;
	double i;
	double scale;
	double ndc_x;
	double ndc_y;
	t_ray		ray;

	engine = getengine();
	cam = engine->w->cam;
	scale = tan(deg_to_rad(cam->fov) / 2.f);
	ray.origin = cam->origin;
	i = 0;
	final_clr = zero_color();
	if (!engine->aa_on)
	{
		ndc_x = (2.f * ((x + (i + 0.5f)) / SCREEN_WIDTH)) - 1.f;
		ndc_y = 1 - (2.f * (y + 0.5) / SCREEN_HEIGHT);			
		ray.direction = generate_cam_dir(cam, scale, ndc_x, ndc_y);
		final_clr = intersect_world(engine->w, &ray, remaining);
		final_clr = clamp_color(final_clr);
	}
	else
	{
		while (i < engine->rays_px)
		{
			double rand_x = x + ((double)rand() / RAND_MAX);
			double rand_y = y + ((double)rand() / RAND_MAX);
			ndc_x = (2.f * (rand_x / SCREEN_WIDTH)) - 1.f;
			ndc_y = 1 - (2.f * (rand_y / SCREEN_HEIGHT));
			ray.direction = generate_cam_dir(cam, scale, ndc_x, ndc_y);
			temp_clr = intersect_world(engine->w, &ray, remaining);
			final_clr = add_colors(final_clr, temp_clr, false);
			i++;
		}
		final_clr = scale_color(final_clr, 1.f / engine->rays_px);
	}
	return (final_clr);
}

void save_to_img(t_color px_color, int x, int y)
{
    t_core      *engine;

	engine = getengine();
	int index = (y * SCREEN_WIDTH + x) * 3;
	engine->png[index] = px_color.r;
	engine->png[index + 1] = px_color.g;
	engine->png[index + 2] = px_color.b;
}

void    rendering(void)
{
    t_core      *engine;
	int	x;
	int	y;
	t_color     px_color;

    engine = getengine();
	init_hooks(engine);
	engine->img.img = mlx_new_image(engine->m.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	engine->img.addr = mlx_get_data_addr(engine->img.img, &engine->img.bits_per_pixel, &engine->img.line_length,
								&engine->img.endian);
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			px_color = get_px_color(x, y, 2);
			my_mlx_pixel_put(&engine->img, x, y, get_rgb(px_color));
			save_to_img(px_color, x, y);
			x += engine->iter;
		}
		y += engine->iter;
	}
	mlx_clear_window(engine->m.mlx, engine->m.win);
	mlx_put_image_to_window(engine->m.mlx, engine->m.win, engine->img.img, 0, 0);
    mlx_hook(engine->m.win, KeyPress, KEY_PRESS, key_press, engine);
    mlx_hook(engine->m.win, KeyRelease, KEY_RELEASE, key_release, engine);
	mlx_loop(engine->m.mlx);
    return ;
}
