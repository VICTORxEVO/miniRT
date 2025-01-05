# include "miniRT.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

inline t_vector	reflect (t_vector	light, t_vector	norm)
{
	return sub_vectors(light, scale_vector(norm, 2 * dot(norm, light))); 
}

t_color	lighting(t_world *w, t_ray *cam_ray, t_sphere *hit_sph, float smallest_t)
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
	light = w->lights->data;
	ambient = w->ambient;
	color = zero_color();
	if (!hit_sph)
		return (color);
	speclar_color = zero_color();
	diffuse_color = zero_color();
	ambient_color = zero_color();
	inter_point = position_at(cam_ray, smallest_t);
	ambient_color = scale_color(ambient->c, ambient->ratio * 0.1); // its color * ratio // lower down the ambient
	sph_norm_vec = normal(sub_points(inter_point, hit_sph->origin));
	pt_light_vec = normal(sub_points(light->p, inter_point));
	pt_cam_vec = normal(sub_points(cam_ray->origin ,inter_point));
	light_dot_norm = dot(sph_norm_vec, pt_light_vec); // correct
	if (light_dot_norm >= 0)
		diffuse_color = (scale_color(hit_sph->c, light_dot_norm));
	light_ref = reflect(neg_vector(pt_light_vec), sph_norm_vec);
	refl_dot_cam = dot(light_ref, pt_cam_vec);
	if (refl_dot_cam > 0)
		speclar_color = scale_color(light->c, powf(refl_dot_cam, light->brightness * 100));
	color = clamp_color(sum_colors(speclar_color ,diffuse_color, ambient_color));
	return color;
}

t_vector	generate_cam_dir(t_camera	*cam, float scale, float ndcx, float ndcy)
{
	t_vector	dir;

	dir = cam->forward;
	dir.x += (ndcx * scale * cam->aspect * cam->right.x) + (ndcy * scale * cam->up.x);
	dir.y += (ndcx * scale * cam->aspect * cam->right.y) + (ndcy * scale * cam->up.y);
	dir.z += (ndcx * scale * cam->aspect * cam->right.z) + (ndcy * scale * cam->up.z);
	return (normal(dir));
}

float intersect(t_sphere *s, t_ray *ray)
{
    t_vector oc;
    float r;
    float a;
    float b;
    float c;
    float d;
    float t1, t2;

    r = s->diameter / 2.0f;
    oc = sub_points(ray->origin, s->origin);
    a = dot(ray->direction, ray->direction);
    b = 2.0f * dot(ray->direction, oc);
    c = dot(oc, oc) - (r * r);

    d = (b * b) - (4.0f * a * c);
	if (d < 0)
		return -1;
    t1 = (-b - sqrtf(d)) / (2.0f * a);
    t2 = (-b + sqrtf(d)) / (2.0f * a);

    if (t1 > t2)
        return t2;
	else
		return t1;
    return false;
}

t_color intersect_world(t_world *w, t_ray *cam_ray)
{
	t_color	color;
	t_node	*node;
	t_sphere	*sphere;
	t_sphere	*hit_sph;
	float smallest_t;
	float t;
	t_vector	sph_norm_vec;
	t_vector	pt_cam_vec;
	t_vector	light_ref;
	t_point inter_point;
	hit_sph = NULL;
	node = w->spheres;
	smallest_t = __FLT_MAX__;
	while (node)
	{
		if (node->type == e_sphere)
		{

			sphere = (t_sphere *)(node->data);
			t = intersect(sphere, cam_ray);
			if (t < smallest_t && t >= 0)
			{
				hit_sph = sphere;
				smallest_t = t;
			}
 		}
		node = node->next;
	}
	color = lighting(w, cam_ray, hit_sph, smallest_t);
	return color;
}

int input(int key, void *d)
{
	t_core *data;

	(void) data;
	if (key == XK_Escape)
	{
		clear();
		exit(0);
	}
	return 1;
}

void    rendering(void)
{
    t_camera    *cam;
	t_sphere	*s;
	t_ray		ray;
	t_node		*node;
    t_core      *engine;

    engine = getengine();
	node = (t_node *)(engine->w->spheres); // first sphere
	s = (t_sphere *)(node->data);
	int	x;
	int	y;
	float scale;
	float ndc_x;
	float ndc_y;

	cam = engine->w->cam;
	// debug light
	printf("light info -> %f %f %f\n", ((t_light *)(engine->w->lights->data))->p.x, ((t_light *)(engine->w->lights->data))->p.y, ((t_light *)(engine->w->lights->data))->p.z);
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
			// debug the ray direction but not every pixel
			if (x % 100 == 0)
				print_vector(ray.direction);
			// send ray from cam origin to the pixel
			my_mlx_pixel_put(&engine->img, x, y, get_rgb(intersect_world(engine->w, &ray)));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(engine->m.mlx, engine->m.win, engine->img.img, 0, 0);
	mlx_key_hook(engine->m.win, input, engine);
	mlx_loop(engine->m.mlx);
    return ;
}