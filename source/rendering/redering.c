# include "miniRT.h"

double get_intersect_dist(t_world *w, t_ray *ray)
{
	t_object	*node;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	t_cone	*cone;
	t_inter it;
	double smallest_t;
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
		else if (node->type == CO_OBJ)
		{
			cone = (t_cone *)(node->data);
			it = co_intersect(cone, ray);
			if (it.t1 < smallest_t && it.t1 > 0)
				smallest_t = it.t1;
		}
		node = node->next;
	}
	return smallest_t;
}

t_color get_plane_checker_value(t_vec p, t_pattern *pattern)
{
	if (((int)floor(p.x * 0.5) + (int)floor(p.y * 0.5) + (int)floor(p.z * 0.5)) % 2 == 0)
			return pattern->c1;
		return pattern->c2;
}

t_color get_sphere_checker_value(t_vec p, double diameter, t_pattern *pattern)
{
	double scale;
	double length;
	double nx;
	double ny;
	double nz;
	double u;
	double v;
	int check_u;
	int check_v;

	length = vec_len(p);
	nx = p.x / length;
	ny = p.y / length;
	nz = p.z / length;
	u = 0.5f + (atan2f(nz, nx) / (2.0f * M_PI));
	v = 0.5f - (asinf(ny) / M_PI);
	scale = diameter * diameter;
	check_u = (int)(u * scale);
	check_v = (int)(v * scale);
	if ((check_u + check_v) % 2 == 0)
		return pattern->c1;
	else
		return pattern->c2;
}


t_color get_checker_value(t_object *hit_obj, t_pattern *pattern, t_vec	origin, t_vec inter_point)
{
	t_vec p;
	t_vec moved_p;
	double diameter;

	moved_p = vec_sub(inter_point, origin);
	if (hit_obj->type == SP_OBJ)
		p = moved_p;
	else
		p = inter_point;
	if (hit_obj->type == PL_OBJ)
		return get_plane_checker_value(p, pattern);
	else
	{
		diameter = ((t_sphere *)hit_obj->data)->diameter;
		return (get_sphere_checker_value(moved_p, diameter, pattern));
	}
}

int get_pixel_intensity(t_texture	*t, int x, int y)
{
	int w;
	int h;

	w = t->width;
	h = t->height;
	return get_pixel_color(t->img_data, x, y, w, h, t->size_line, t->bpp) & 0xFF;
}

t_color get_color_texture(t_sphere *sphere, t_vec *norm)
{
    t_texture *t = sphere->texture;
    double width = t->width;
    double height = t->height;
    int tex_x, tex_y;
	int h_center;
	int x_right;
	int y_up;
	int h_right;
	int h_up;
	float dh_dx;
	float dh_dy;
    t_color color;
	t_vec	n;
	t_vec up;
	t_vec tangent;
	t_vec bitangent;
	t_vec perturbed_normal;
	int x;
	int y;
	int color_int;
	int bump;
	bump = getengine()->bump;
	n = *norm;
    double longitude = atan2(n.z, n.x) + (M_PI / 2);
    double latitude = asin(n.y);
    double u = 1.0 - ((longitude + M_PI) / (2.0 * M_PI));
    double v = 0.5 - (latitude / (M_PI));
    tex_x = (int)(u * (width - 1));
    tex_y = (int)(v * (height - 1));
	tex_x = clampi(tex_x, 0, width - 1);
	tex_y = clampi(tex_y, 0, height - 1);
	x = (int)(u * (t->width - 1));
	y = (int)(v * (t->height - 1));
	x = clampi(x, 0, width - 1);
	y = clampi(y, 0, height - 1);
	h_center = get_pixel_intensity(t, x, y);
	x_right = clampi(x + 1, 0, width - 1);
	y_up = clampi(y + 1, 0, height - 1);
	h_right = get_pixel_intensity(t, x_right, y);
	h_up = get_pixel_intensity(t, x, y_up);
    dh_dx = (h_right - h_center) * bump / 255.0;
    dh_dy = (h_up - h_center) * bump / 255.0;
	up = getengine()->w->cam->up;
    tangent = cross(up, n);
    tangent = normal(tangent);
    bitangent = cross(n, tangent);
    bitangent = normal(bitangent);
    perturbed_normal.x = n.x - dh_dx * tangent.x - dh_dy * bitangent.x;
    perturbed_normal.y = n.y - dh_dx * tangent.y - dh_dy * bitangent.y;
    perturbed_normal.z = n.z - dh_dx * tangent.z - dh_dy * bitangent.z;
	*norm = normal(perturbed_normal);
	color_int = get_pixel_color(t->img_data, tex_x, tex_y, width, height, t->size_line, t->bpp);
    color = get_clr_struct(color_int);
	return color;
}

t_color handle_object_pat(t_object *hit_obj, t_vec inter_point, t_vec	*obj_norm)
{
	t_color	obj_color;
	t_color color;
	t_pattern	*pattern;
	t_vec	origin;

    if (hit_obj->type == SP_OBJ && ((t_sphere *)hit_obj->data)->texture)
    {
        color = get_color_texture(hit_obj->data, obj_norm);
        return color;
    }
	else
	{
		pattern = NULL;
		obj_color = hit_obj->get_color(hit_obj);
		
		if (hit_obj->type != SP_OBJ || !hit_obj->get_pattern(hit_obj))
			return (obj_color);
		origin = ((t_sphere *)hit_obj->data)->origin;
		if (hit_obj->get_pattern)
			pattern = hit_obj->get_pattern(hit_obj);
		if (pattern && pattern->type == CHECKER_PAT)
		{
			return get_checker_value(hit_obj, pattern, origin, inter_point);
		}
		return obj_color;
	}
}

t_color	get_anti_aliased_color(double x, double y, int rem)
{
	t_core *engine;
	t_color	final_clr;
	t_color	color;
	t_camera	*cam;
	double i;
	double scale;
	double ndc_x;
	double ndc_y;
	double aa_factor;

	t_ray		ray;
	i = -1;
	engine = getengine();
	cam = engine->w->cam;
	scale = tan(deg_to_rad(cam->fov) / 2.f);
	aa_factor = 1 / engine->rays_px;
	final_clr = zero_color();
	ray.origin = cam->origin;
	while (++i < engine->rays_px)
	{
		ndc_x = (2.f * ((x + ((i * aa_factor) + 0.5f)) / SCREEN_WIDTH)) - 1.f;
		ndc_y = 1 - (2.f * (y + 0.5) / SCREEN_HEIGHT);		
		ray.direction = generate_cam_dir(cam, scale, ndc_x, ndc_y);
		color = intersect_world(engine->w, &ray, rem);
		final_clr = rgb_add(final_clr, color, 0);
	}
	final_clr = rgb_scl(final_clr, 1 / i);
	return final_clr;
}

t_color get_non_aa_color(double x, double y, int rem)
{
	t_core *engine;
	t_color	final_clr;
	t_camera	*cam;
	double scale;
	double ndc_x;
	double ndc_y;
	t_ray		ray;
	engine = getengine();
	cam = engine->w->cam;
	scale = tan(deg_to_rad(cam->fov) / 2.f);
	ray.origin = cam->origin;
	ndc_x = (2.f * ((x + 0.5f) / SCREEN_WIDTH)) - 1.f;
	ndc_y = 1 - (2.f * (y + 0.5) / SCREEN_HEIGHT);			
	ray.direction = generate_cam_dir(cam, scale, ndc_x, ndc_y);
	final_clr = intersect_world(engine->w, &ray, rem);
	final_clr = clamp_color(final_clr);
	return final_clr;
}

t_color	get_px_color(double x, double y, int rem)
{
	t_core *engine;
	t_color	final_clr;
	engine = getengine();
	if (engine->aa_on)
		final_clr = get_anti_aliased_color(x, y, rem);
	else
		final_clr = get_non_aa_color(x, y, rem);
	return (final_clr);
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
			my_mlx_pixel_put(&engine->img, x, y, get_clr_int(px_color));
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
