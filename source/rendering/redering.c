# include "miniRT.h"

t_vector get_obj_norm(t_object	*o, t_point	pt_on_sphere)
{
	t_sphere *s;

	if (o->type == PL_OBJ)
		return (((t_plane *)o->data)->normal);
	else if (o->type == SP_OBJ)
	{
		s = (t_sphere *)o->data;
		return (normal(sub_points(pt_on_sphere, s->origin)));
	}
	return (t_vector) {0,0,0};
}

t_color	get_obj_color(t_object *o)
{
	if (o->type == SP_OBJ)
		return ((t_sphere *)o->data)->c;
	else
		return ((t_plane *)o->data)->c;
}

void set_obj_color(t_object *o, t_color c)
{
	if (o->type == SP_OBJ)
		((t_sphere *)o->data)->c = c;
	else
		((t_plane *)o->data)->c = c;

}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

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
			if (t < smallest_t && t >= 0)
				smallest_t = t;
 		}
		else if (node->type == PL_OBJ)
		{
			plane = (t_plane *)(node->data);
			t = pl_intersect(plane, ray);
			if (t < smallest_t && t >= 0)
				smallest_t = t;
		}
		node = node->next;
	}
	return smallest_t;
}

inline t_vector	reflect (t_vector	light, t_vector	norm) // light is a vector from a point towards the light
{
	return sub_vectors(light, scale_vector(norm, 2 * dot(norm, light))); 
}

bool is_shadowed(t_world *w, t_point p)
{
	t_light *light;
	t_ray pt_to_light_ray;
	t_vector offset;
	float inter_dist;
	float pt_to_light_dist;
	light = w->lights->data;
	offset = scale_vector(normal(sub_points(light->p, p)), EPSILON);
	pt_to_light_ray.origin = add_points(p, v_to_p(offset));
	pt_to_light_ray.direction = normal(sub_points(light->p, p));
	pt_to_light_dist = get_len_vector(sub_points(light->p, p));
	inter_dist = get_intersect_dist(w, &pt_to_light_ray);
	if (inter_dist > EPSILON && inter_dist < pt_to_light_dist)
		return true;
	return false;
}

t_color	lighting(t_ray *cam_ray, t_object *hit_obj, float smallest_t)
{
	if (!hit_obj)
		return ((t_color) {10, 10, 10});
	t_color	color;
	t_color	speclar_color;
	t_color	diffuse_color;
	t_color	ambient_color;
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
	obj_clr = hit_obj->get_color(hit_obj);
	ambient_color = scale_color(mul_colors(ambient->c, obj_clr), ambient->ratio * 0.1); // should this be a unified color or just a color to add to my objects's colors
	inter_point = position_at(cam_ray, smallest_t);
	if (is_shadowed(getengine()->w, inter_point))
		return ambient_color;
	pt_cam_vec = normal(sub_points(inter_point, cam_ray->origin)); 
	obj_norm = hit_obj->get_norm(hit_obj, inter_point);
	cam_ray_surf_norm_dot = dot(pt_cam_vec, obj_norm);
	if (cam_ray_surf_norm_dot >= 0)
		obj_norm = neg_vector(obj_norm);
	pt_light_vec = normal(sub_points(light->p, inter_point)); // ray from point to light
	light_dot_norm = dot(obj_norm, pt_light_vec);
	if (light_dot_norm >= 0)
	{
		diffuse_color = scale_color(hit_obj->get_color(hit_obj), light_dot_norm * light->brightness);
		light_ref = reflect(pt_light_vec, obj_norm);
        refl_dot_cam = dot(normal(light_ref), pt_cam_vec);
        if (refl_dot_cam > 0 && light->brightness > 0)
			speclar_color = scale_color(scale_color(light->c, light->brightness), powf(refl_dot_cam, light->brightness * 100));
    }
	color = clamp_color(sum_colors(speclar_color ,diffuse_color, ambient_color));
	if (getengine()->w->gray_on)
		return (rgb_to_gray(color));
	return color;
}

float sp_intersect(t_sphere *s, t_ray *ray)
{
    t_vector oc;
    float a;
    float b;
    float c;
    float d;
    float t1, t2;

    oc = sub_points(ray->origin, s->origin);
    a = dot(ray->direction, ray->direction);
    b = 2.0f * dot(ray->direction, oc);
    c = dot(oc, oc) - s->radius_squared;

    d = (b * b) - (4.0f * a * c);
	if (d < 0 || (a == 0.f))
		return -1;
    t1 = (-b - sqrtf(d)) / (2.0f * a);
    t2 = (-b + sqrtf(d)) / (2.0f * a);
	if (t1 < t2 && t1 >= 0)
		return t1;
	return t2;

}

float pl_intersect(t_plane *pl, t_ray *ray)
{
	float		t;
	float		d_dot_n;
	t_vector		d;
	t_point	p0;
	t_point	o;
	t_vector	n;
	t_vector	p0_o;

	o = ray->origin;
	p0 = pl->origin;
	n = pl->normal;
	d = ray->direction;
	p0_o = sub_points(p0, o);
	d_dot_n = dot(d, n);
	if ((fabs(dot(sub_points(ray->origin, p0), n))) - EPSILON < 0)
		return 0;
	if (fabs(d_dot_n) < EPSILON)
		return -1; // no intersection   divide by zero
	t = dot(p0_o, n) / d_dot_n;
	if (t < EPSILON)
		return -1;
	return t;
}

t_color intersect_world(t_world *w, t_ray *cam_ray)
{
	t_object	*node;
	t_object	*hit_obj;
	float smallest_t;
	float t;
	hit_obj = NULL;
	node = w->objects;
	smallest_t = __FLT_MAX__;
	while (node)
	{
		if (node->type == SP_OBJ)
		{
			t = sp_intersect(node->data, cam_ray);
			if (t <= smallest_t && t > 0)
			{
				hit_obj = node;
				smallest_t = t;
			}
 		}
		else if (node->type == PL_OBJ)
		{
			t = pl_intersect(node->data, cam_ray);
			if (t <= smallest_t && t >= 0)
			{
				hit_obj = node;
				smallest_t = t;
			}
		}
		node = node->next;
	}
	return lighting(cam_ray, hit_obj, smallest_t);
}

void    rendering(void)
{
    t_camera    *cam;
	t_ray		ray;
    t_core      *engine;

    engine = getengine();
	int	x;
	int	y;
	float scale;
	float ndc_x;
	float ndc_y;
	init_hooks(engine);
	engine->img.img = mlx_new_image(engine->m.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	engine->img.addr = mlx_get_data_addr(engine->img.img, &engine->img.bits_per_pixel, &engine->img.line_length,
								&engine->img.endian);
	// mlx_clear_window(engine->m.mlx, engine->m.win);
	cam = engine->w->cam;
	// debug light
	scale = tan(deg_to_rad(cam->fov) / 2.f);
	x = 0;
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		ndc_y = 1 - (2.f * (y + 0.5) / SCREEN_HEIGHT);			
		while (x < SCREEN_WIDTH)
		{
			ndc_x = (2.f * (x + 0.5) / SCREEN_WIDTH) - 1.f;
			ray.origin = cam->origin;
			ray.direction = generate_cam_dir(cam, scale, ndc_x, ndc_y);
			my_mlx_pixel_put(&engine->img, x, y, get_rgb(intersect_world(engine->w, &ray)));
			x += engine->iter;
		}
		y += engine->iter;
	}
	mlx_clear_window(engine->m.mlx, engine->m.win);
	mlx_put_image_to_window(engine->m.mlx, engine->m.win, engine->img.img, 0, 0);
    mlx_hook(engine->m.win, KeyPress, KEY_PRESS, key_press, engine);
    mlx_hook(engine->m.win, KeyRelease, KEY_RELEASE, key_release, engine);
	mlx_mouse_hook(engine->m.win, mouse_input, engine);
	mlx_loop(engine->m.mlx);
    return ;
}