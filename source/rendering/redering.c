# include "miniRT.h"

t_vector get_obj_norm(t_object	*o, t_point	pt_on_sphere)
{
	t_sphere *s;

	if (o->type == PL_OBJ)
		return (((t_plane *)o)->normal);
	else if (o->type == SP_OBJ)
	{
		s = (t_sphere *)o->data;
		return (sub_points(pt_on_sphere, s->origin));
	}
	return (t_vector) {0,0,0};
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

inline t_vector	reflect (t_vector	light, t_vector	norm)
{
	return sub_vectors(light, scale_vector(norm, 2 * dot(norm, light))); 
}

t_color	sp_light(t_sphere	*hit_sph, t_ray	*cam_ray, float smallest_t)
{
	t_color	color;
	t_color	speclar_color;
	t_color	diffuse_color;
	t_color	ambient_color;
	t_light		*light;
	t_ambient	*ambient;
	t_vector	pt_light_vec;
	float light_dot_norm;
	float refl_dot_cam;
	t_vector	sph_norm_vec;
	t_vector	pt_cam_vec;
	t_vector	light_ref;
	t_point inter_point;
	light = getengine()->w->lights->data;
	ambient = getengine()->w->ambient;
	color = zero_color();
	speclar_color = zero_color();
	diffuse_color = zero_color();
	ambient_color = zero_color();
	inter_point = position_at(cam_ray, smallest_t);
	ambient_color = scale_color(ambient->c, ambient->ratio * 0.2);
	sph_norm_vec = normal(sub_points(inter_point, hit_sph->origin));
	pt_light_vec = normal(sub_points(light->p, inter_point));
	pt_cam_vec = normal(sub_points(inter_point, cam_ray->origin));
	light_dot_norm = dot(sph_norm_vec, pt_light_vec);
	if (light_dot_norm >= 0)
	{
		diffuse_color = scale_color(hit_sph->c, light_dot_norm * light->brightness);
		light_ref = reflect(neg_vector(pt_light_vec), sph_norm_vec);
        refl_dot_cam = dot(normal(light_ref), pt_cam_vec);
        if (refl_dot_cam > 0 && light->brightness > 0)
			speclar_color = scale_color(scale_color(light->c, light->brightness), powf(refl_dot_cam, light->brightness * 100));
    }
	
	color = clamp_color(sum_colors(speclar_color ,diffuse_color, ambient_color));
	return color;
}

t_color	pl_light(t_plane	*hit_pl, t_ray	*cam_ray, float smallest_t)
{
	t_vector	pt_vec;
	t_vector	light_vec;
	t_vector	light_ref;
	t_point	intersec_ptr;
	t_light	*light;
	float	light_dot_norm;
	t_ambient	*ambient;

	ambient = getengine()->w->ambient;
	light = getengine()->w->lights->data;
	intersec_ptr = position_at(cam_ray, smallest_t);
	light_vec = normal(sub_points(light->p, intersec_ptr)); // from point to light 
	pt_vec = normal(sub_points(hit_pl->origin, intersec_ptr));
	light_dot_norm = dot(hit_pl->normal, light_vec);
	light_ref = reflect(neg_vector(light_vec), hit_pl->normal);

	return (scale_color(hit_pl->c, light_dot_norm));
}

t_color	lighting(t_world *w, t_ray *cam_ray, t_object *hit_obj, float smallest_t)
{
	if (!hit_obj)
		return ((t_color) {20, 20, 20});
	if (hit_obj->type == PL_OBJ)
		return (pl_light(hit_obj->data, cam_ray, smallest_t));
	if (hit_obj->type == SP_OBJ)
		return (sp_light(hit_obj->data, cam_ray, smallest_t));
	return ((t_color) {20, 20, 20});

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
	if (d < 0 || (a == 0))
		return -1;
    t1 = (-b - sqrtf(d)) / (2.0f * a);
    t2 = (-b + sqrtf(d)) / (2.0f * a);
    return (maxf(t1, t2));
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
	if (d_dot_n == 0)
		return -1; // no intersection   divide by zero
	t = dot(p0_o, n) / d_dot_n;
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
			if (t < smallest_t && t >= 0)
			{
				hit_obj = node;
				smallest_t = t;
			}
 		}
		else if (node->type == PL_OBJ)
		{
			t = pl_intersect(node->data, cam_ray);
			if (t < smallest_t && t >= 0)
			{
				hit_obj = node;
				smallest_t = t;
			}
		}
		node = node->next;
	}
	return lighting(w, cam_ray, hit_obj, smallest_t);
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
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(engine->m.mlx, engine->m.win, engine->img.img, 0, 0);
    mlx_hook(engine->m.win, KeyPress, KEY_PRESS, key_press, engine);
    mlx_hook(engine->m.win, KeyRelease, KEY_RELEASE, key_release, engine);
	mlx_loop(engine->m.mlx);
    return ;
}