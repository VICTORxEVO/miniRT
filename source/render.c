#include "miniRT.h"

inline t_vector	reflect(t_vector	norm, t_vector	light)
{
	return sub_vectors(light, scale_vector(norm, 2 * dot(norm, light))); 
}

void print_cam(t_camera *cam)
{
    printf("camera at [%f, %f, %f], direction for (%f, %f, %f)\n", cam->origin.x, cam->origin.y, cam->origin.z, cam->direction.x, cam->direction.y, cam->direction.z);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int input(int key, void *d)
{
	t_data *data;

	data = (t_data *)d;
	if (key == XK_Escape)
	{
		gc_void(data);
		exit(0);
	}
	return 1;
}

void setup_cam_dir(t_camera	*cam)
{
	t_vector	temp_up;
	// calc up, right vectors for where the cam is lookin (forward)
	temp_up = (t_vector) {0, 1, 0};
	cam->right = get_normalized(cross(temp_up, cam->forward)); 
	cam->up = get_normalized(cross(cam->forward, cam->right)); // now reset up
}
/*
Let me derive the sphere intersection formula step by step.

Sphere equation: x² + y² + z² = r² for a sphere at origin
For sphere at point C(Cx,Cy,Cz): (x-Cx)² + (y-Cy)² + (z-Cz)² = r²
Ray equation: P + tD where

P = ray origin (Px,Py,Pz)
D = ray direction (Dx,Dy,Dz)
t = distance along ray
So any point on ray is:
x = Px + tDx
y = Py + tDy
z = Pz + tDz


Substitute ray equations into sphere equation:
(Px + tDx - Cx)² + (Py + tDy - Cy)² + (Pz + tDz - Cz)² = r²
Let OC = (ray origin - sphere center):

OCx = Px - Cx
OCy = Py - Cy
OCz = Pz - Cz

Expand equation:
(OCx + tDx)² + (OCy + tDy)² + (OCz + tDz)² = r²
(OCx² + 2tOCx•Dx + t²Dx²) +
(OCy² + 2tOCy•Dy + t²Dy²) +
(OCz² + 2tOCz•Dz + t²Dz²) = r²
Group t terms:

t²(Dx² + Dy² + Dz²) +               // a term
2t(OCx•Dx + OCy•Dy + OCz•Dz) +      // b term
(OCx² + OCy² + OCz² - r²) = 0       // c term

In vector form:
a = D•D            (dot product of direction with itself)
b = 2(OC•D)        (dot product of OC vector with direction)
c = OC•OC - r²     (dot product of OC with itself minus radius squared)
This is quadratic equation: at² + bt + c = 0
Solution: t = (-b ± √(b² - 4ac)) / 2a

*/



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

// white -> 255, 255, 255,  intesnsity -> .5 
// res_light = 128, 128, 128

t_color intersect_world(t_world *w, t_ray *cam_ray)
{
	t_color	color;
	t_color	light_color;
	t_color	speclar_color;
	t_color	diffuse_color;
	t_color	ambient_color;
	t_node	*node;
	t_sphere	*sphere;
	t_sphere	*hit_sph;
	t_light		*light;
	t_ambient	*ambient;
	t_vector	light_cam;
	float smallest_t;
	float light_dot_eye;
	float t;
	t_vector	sph_norm;
	t_point inter_point;
	hit_sph = NULL;
	node = w->spheres;
	light = w->lights->data;
	ambient = w->ambient;
	color = zero_color();
	smallest_t = __FLT_MAX__;
	while (node)
	{
		if (node->type == e_sphere)
		{
			sphere = (t_sphere	*)(node->data);
			t = intersect(sphere, cam_ray);
			if (t < smallest_t && t >= 0)
			{
				hit_sph = sphere;
				smallest_t = t;
			}
 		}
		node = node->next;
	}
	if (hit_sph)
	{
		light_color = scale_color(light->c, light->brightness); // currently white
		inter_point = position_at(cam_ray, smallest_t);
		sph_norm = get_normalized(sub_points(inter_point, sphere->origin));
		light_cam = get_normalized(sub_points(light->p, inter_point));
	
		light_dot_eye = dot(light_cam, sph_norm);
		
		ambient_color = scale_color(ambient->c, ambient->ratio); // its color * ratio
		diffuse_color = scale_color(sphere->c, light_dot_eye);
		color = mul_colors(sphere->c, light->c);
		color = scale_color(add_colors(ambient->c, hit_sph->c), light_dot_eye);
	}
	return color;
}



bool initialized(t_data *d, t_img	*img)
{
	d->m.con = mlx_init();
    d->m.win = mlx_new_window(d->m.con, SCREEN_WIDTH, SCREEN_HEIGHT, "Hello world!");
	img->img = mlx_new_image(d->m.con, SCREEN_WIDTH, SCREEN_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&img->endian);
	setup_cam_dir(d->w->cam);
	return (true);
	
}

t_vector	generate_cam_dir(t_camera	*cam, float scale, float ndcx, float ndcy)
{
	t_vector	dir;

	dir = cam->forward;
	dir.x += (ndcx * scale * cam->aspect * cam->right.x) + (ndcy * scale * cam->up.x);
	dir.y += (ndcx * scale * cam->aspect * cam->right.y) + (ndcy * scale * cam->up.y);
	dir.z += (ndcx * scale * cam->aspect * cam->right.z) + (ndcy * scale * cam->up.z);
	return (get_normalized(dir));
}

bool    rendered(t_data *d, t_img *img)
{
    t_camera    *cam;
	t_sphere	*s;
	t_ray		ray;
	t_node		*node;
	node = (t_node *)(d->w->spheres); // first sphere
	s = (t_sphere *)(node->data);
    print_point(s->origin);
	int	x;
	int	y;
	float scale;
	float ndc_x;
	float ndc_y;

	cam = d->w->cam;
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
			// send ray from cam origin to the pixel
			my_mlx_pixel_put(img, x, y, get_rgb(intersect_world(d->w, &ray)));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(d->m.con, d->m.win, img->img, 0, 0);
    return (true);
}