# include "miniRT.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

float get_intersect_dist(t_world *w, t_ray *ray, t_object *obj_in_way_of_light)
{
	t_object	*node;
	t_sphere	*sphere;
	t_plane		*plane;
	float smallest_t;
	float t;
	node = w->objects;
	obj_in_way_of_light = NULL;
	smallest_t = __FLT_MAX__;
	while (node)
	{
		if (node->type == SP_OBJ)
		{
			sphere = (t_sphere *)(node->data);
			t = sp_intersect(sphere, ray);
			if (t < smallest_t && t >= 0)
			{
				smallest_t = t;
				obj_in_way_of_light = node;
			}
 		}
		else if (node->type == PL_OBJ)
		{
			plane = (t_plane *)(node->data);
			t = pl_intersect(plane, ray);
			if (t < smallest_t && t >= 0)
			{
				smallest_t = t;
				obj_in_way_of_light = node;
			}
		}
		node = node->next;
	}
	return smallest_t;
}

inline t_vector	reflect (t_vector	light, t_vector	norm)
{
	return sub_vectors(light, scale_vector(norm, 2 * dot(norm, light))); 
}

bool	is_shadowed(t_world	*w, t_ray	*ray, float distance_t) // still not implemented
{
	return false;
}

t_vector	get_norm_of_obj(t_object *o, t_ray	*ray, float pt)
{
	t_vector	obj_norm;
	t_sphere	*sp;
	t_plane		*pl;
	if (o->type == SP_OBJ)
	{
		sp = ((t_sphere *) o->data);
		obj_norm = normal(sub_points(position_at(ray, pt), sp->origin));
		return obj_norm;
	}
	else if (o->type == PL_OBJ)
	{
		pl = (t_plane *) o->data;
		return pl->normal;
	}
	else return (t_vector) {0,0,0};
}

t_vector	get_norm_of_obj2(t_object *o, t_point	p)
{
	t_vector	obj_norm;
	t_sphere	*sp;
	t_plane		*pl;
	if (o->type == SP_OBJ)
	{
		sp = ((t_sphere *) o->data);
		obj_norm = normal(sub_points(p, sp->origin));
		return obj_norm;
	}
	else if (o->type == PL_OBJ)
	{
		pl = (t_plane *) o->data;
		return pl->normal;
	}
	else return (t_vector) {0,0,0};
}

t_color	apply_shadow( t_color	c, t_object *src_obj, t_point	p)
{
	t_ray	pt_light_ray ;
	t_vector	pt_light_vec;
	t_vector	obj_norm;
	t_world *w;
	t_light	*l;
	t_object	*obj_inter;
	float inters_dist;
	w = getengine()->w;
	l = w->lights->data;

	obj_norm = get_norm_of_obj2(src_obj, p);
	pt_light_vec = sub_points(l->p, p);
	pt_light_ray.origin = p;
	pt_light_ray.origin.x += scale_vector(obj_norm, EPSILON * 1000).x;
	pt_light_ray.origin.y += scale_vector(obj_norm, EPSILON * 1000).y;
	pt_light_ray.origin.z += scale_vector(obj_norm, EPSILON * 1000).z;
	pt_light_ray.direction = normal(pt_light_vec);
	inters_dist = get_intersect_dist(w, &pt_light_ray, obj_inter);
	if (inters_dist < get_len_vector(pt_light_vec))
		return clamp_color(decrease_color(c, 200));
	return c;
}

t_color	lighting(t_world *w, t_ray *cam_ray, t_object *hit_obj, float smallest_t)
{
	t_color	color;
	t_color	speclar_color;
	t_color	diffuse_color;
	t_color	ambient_color;
	t_light		*light;
	t_ambient	*ambient;
	t_vector	pt_light_vec_norm;
	t_vector	pt_light_vec;
	float refl_dot_cam;
	float pt_light_dis;
	t_vector	pt_cam_vec;
	t_point inter_point;
	t_vector	surf_normal;
	t_vector	light_ref;
	t_color	obj_color;
	float	light_dot_norm;

	// add length of light playing a role on the lighting
	// lets say if its close bt 1, its at its fullest, but 20 is no light reached 
	if (!hit_obj)
		return ((t_color) {0, 0, 0}); // sky
	color = scale_color(w->ambient->c, w->ambient->ratio);
	light = getengine()->w->lights->data;
	inter_point = position_at(cam_ray, smallest_t);
	speclar_color = zero_color();
	diffuse_color = zero_color();
	// works until here
	ambient = getengine()->w->ambient;
	ambient_color = scale_color(ambient->c, ambient->ratio * 0.1);
	pt_light_vec = sub_points(light->p, inter_point); // from point to light 
	pt_light_dis = get_len_vector(pt_light_vec);
	pt_light_vec_norm = normal(pt_light_vec);
	surf_normal = get_norm_of_obj(hit_obj, cam_ray, smallest_t);
	pt_cam_vec = normal(sub_points(cam_ray->origin ,inter_point));
	light_dot_norm = dot(surf_normal, pt_light_vec_norm);
	light_ref = reflect(neg_vector(pt_light_vec_norm), surf_normal);
	refl_dot_cam = dot(light_ref, pt_cam_vec);
	if (hit_obj->type == PL_OBJ)
	{
		obj_color = ((t_plane *)hit_obj->data)->c;
		speclar_color = zero_color();
	}
	if (hit_obj->type == SP_OBJ)
	{
		obj_color = ((t_sphere *)hit_obj->data)->c;
		speclar_color = scale_color(light->c, powf(maxf(0, refl_dot_cam), light->brightness * 100));
	}
	diffuse_color = scale_color(obj_color, maxf(0, light_dot_norm)); // maxf gets 0 if less than 0
	color = sum_phong(speclar_color ,diffuse_color, ambient_color);
	// color = decrease_color(color, pt_light_dis);
	color = clamp_color(apply_shadow(color, hit_obj, inter_point));
	return color;
}

t_ray	generate_cam_ray(t_camera	*cam, float ndcx, float ndcy)
{
	t_vector	dir;
	t_ray		ray;
	float 		scale;

	scale = cam->scale;
	dir = cam->forward;
	dir.x += (ndcx * scale * cam->aspect * cam->right.x) + (ndcy * scale * cam->up.x);
	dir.y += (ndcx * scale * cam->aspect * cam->right.y) + (ndcy * scale * cam->up.y);
	dir.z += (ndcx * scale * cam->aspect * cam->right.z) + (ndcy * scale * cam->up.z);
	ray.direction = normal(dir);
	ray.origin = cam->origin;
	return ray;
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

    if (t1 > t2)
        return t2;
	else
		return t1;
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
	t_color	color;
	t_object	*node;
	t_sphere	*sphere;
	t_plane	*plane;
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
			sphere = (t_sphere *)(node->data);
			t = sp_intersect(sphere, cam_ray);
			if (t < smallest_t && t >= 0)
			{
				hit_obj = node;
				smallest_t = t;
			}
 		}
		else if (node->type == PL_OBJ)
		{
			plane = (t_plane *)(node->data);
			t = pl_intersect(plane, cam_ray);
			if (t < smallest_t && t >= 0)
			{
				hit_obj = node;
				smallest_t = t;
			}
		}
		node = node->next;
	}
	color = lighting(w, cam_ray, hit_obj, smallest_t);
	return color;
}

int move_by_mouse(int mouse_key, int x, int y, void *param)
{
	t_core *engine;

	engine = param;
	printf("mouse click [%d, %d] -> %d\n",x, y, mouse_key);
	return 1;
}

void    rendering(void)
{
    t_camera    *cam;
	t_ray		ray;
    t_core      *engine;
	int	x;
	int	y;
	float ndc_x;
	float ndc_y;

    engine = getengine();
	cam = engine->w->cam;
	x = -1;
	y = -1;
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		ndc_y = 1 - (2.f * (y + 0.5) / SCREEN_HEIGHT);			
		while (++x < SCREEN_WIDTH)
		{
			ndc_x = (2.f * (x + 0.5) / SCREEN_WIDTH) - 1.f;
			ray = generate_cam_ray(cam, ndc_x, ndc_y);
			my_mlx_pixel_put(&engine->img, x, y, get_rgb(intersect_world(engine->w, &ray)));
		}
	}
	mlx_put_image_to_window(engine->m.mlx, engine->m.win, engine->img.img, 0, 0);
	mlx_hook(engine->m.win, 5, (1L<<0 | 1L<<1 | 1L<<2 | 1L<<3), move_by_mouse, engine);
	mlx_key_hook(engine->m.win, input, engine);
	mlx_loop(engine->m.mlx);
}
