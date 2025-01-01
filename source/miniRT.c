#include "miniRT.h"

bool    color_struct_filled(t_color	*c, char  **args)
{
    bool error;

    error = false;
	c->r = ft_atof(args[0], &error);
	if (error || !between(c->r, 0, 255))
		return (error);
	c->g = ft_atof(args[1], &error);
	if (error || !between(c->g, 0, 255))
		return (error);
	c->b = ft_atof(args[2], &error);
	if (error || !between(c->b, 0, 255))
		return false;
	return (true);
}

bool    point_struct_filled(t_point	*p, char  **args)
{
    bool error;

    error = false;
	p->x = ft_atof(args[0], &error);
	if (error)
		return (false);
	p->y = ft_atof(args[1], &error);
	if (error)
		return (false);
	p->z = ft_atof(args[2], &error);
	if (error)
		return (false);
	return (true);
}

bool    vector_struct_filled(t_vector	*v, char  **args)
{
    bool error;
    // for camera , one at least should be 1
    error = false;
	v->x = ft_atof(args[0], &error);
	if (error || (v->x != 0.0f && v->x != 1.0f && v->x != -1.0f))
		return (false);
	v->y = ft_atof(args[1], &error);
	if (error || (v->y != 0.0f && v->y != 1.0f && v->y != -1.0f))
		return (false);
	v->z = ft_atof(args[2], &error);
	if (error || (v->z != 0.0f && v->z != 1.0f && v->z != -1.0f))
		return (false);
    if (fabsf(v->x) == 1.0f || fabsf(v->y) == 1.0f || fabsf(v->z) == 1.0f)
	    return (true);
    return false;
}

bool    camera_handled(t_data *d, t_pars *p, char **args)
{
    char		**cord;
    char		**vctr;
    float   	FOV;
    t_vector	vec3d;
    t_point		pcord;
    bool		err;

    err = p->camera_exist;
    if (err)
    {
        return (false);
    }
    cord = ft_split(d, args[1], ',');
    if (count_args(cord) != 3 || !point_struct_filled(&pcord, cord))
    {
        return (printf("Error\nbad camera point coordinates\n"), false);
    }
	vctr = ft_split(d, args[2], ',');
	if (count_args(vctr) != 3 || !vector_struct_filled(&vec3d, vctr))
    {
        return (printf("Error\nbad camera 3d vector"), false);
    }
    FOV = ft_atof(args[3], &err);
    if (err || (FOV < 0 || FOV > 180))
    {
        return (printf("Error\nbad fov value for camera"), false);
    }
	d->w->cam.cam_ray.direction = vec3d;
	d->w->cam.cam_ray.origin = pcord;
	d->w->cam.fov = FOV;
	return (true);
}

bool    ambient_handled(t_data *d, t_pars *p, char **args)
{
    char		**clrs;
    float   	ambient_ratio;
    t_ambient	ambient;
    t_color	    ambient_color;
    bool		err;

    err = false;
    ambient_color = zero_color();
    if (p->ambient_exist)
        return (printf("Error\nambient already exists\n"), false);
    ambient_ratio = ft_atof(args[1], &err);
    if (err || !between(ambient_ratio, 0, 1))
        return (printf("Error\nambient ratio invalid\n"), false);
    clrs = ft_split(d, args[2], ',');
    if (count_args(clrs) != 3 || !color_struct_filled(&ambient_color, clrs))
    {
        return (printf("Error\nambient color invalid\n"), false);
    }
	ambient.ratio = ambient_ratio;
	ambient.c = ambient_color;
	d->w->ambient = ambient;
	return (true);
}

bool    light_handled(t_data *d, char **args)
{
    char		**clrs;
    float	    light_value;
    t_color		light_color;
    t_point		light_cord;
	t_light		*light;
    char		**cord;
    bool		err;

    err = false;
    cord = ft_split(d, args[1], ',');
    if (count_args(cord) != 3 || !point_struct_filled(&light_cord, cord))
        return (printf("Error\nbad light point coordinates\n"), false);
    if (err)
        return (false);
    light_value = ft_atof(args[2], &err);
    if (err || !between(light_value, 0, 1))
        return (printf("Error\nlight value invalid\n"), false);
    clrs = ft_split(d, args[3], ',');
    if (count_args(clrs) != 3 || !color_struct_filled(&light_color, clrs))
        return (printf("Error\nlight color invalid\n"), false);
    light = gc_malloc(d, sizeof(t_light));
    light->brightness = light_value;
    light->c = light_color;
    light->p = light_cord;
	add_node(d, &d->w->lights, create_node(d, light));
	return (true);
}

bool    plane_handled(t_data *d, char **args)
{
    char		**clrs;
    char		**vctr;
    t_color		plane_color;
    t_point		plane_cord;
    t_vector	plane_norm;
	t_plane		*plane;
    char		**cord;
    bool		err;

    err = false;
    cord = ft_split(d, args[1], ',');
    if (count_args(cord) != 3 || !point_struct_filled(&plane_cord, cord))
        return (false);
    if (err)
        return (false);
   
    vctr = ft_split(d, args[2], ',');
	if (count_args(vctr) != 3 || !vector_struct_filled(&plane_norm, vctr))
    {
        return (printf("bad plane 3d vector"), false);
    }

    clrs = ft_split(d, args[3], ',');
    if (count_args(clrs) != 3 || !color_struct_filled(&plane_color, clrs))
        return (false);
    plane = gc_malloc(d, sizeof(t_plane));
   
    plane->c = plane_color;
    plane->origin = plane_cord;
    plane->normal = plane_norm;
	add_node(d, &d->w->planes, create_node(d, plane));
	return (true);
}

bool    cylinder_handled(t_data *d, char **args)
{
    char		**clrs;
    char		**vctr;
    t_color		cylinder_color;
    t_point		cylinder_cord;
    t_vector	cylinder_norm;
    float       diameter;
    float       height;
	t_cylinder  *cylinder;
    char		**cord;
    bool		err;

    err = false;
    cord = ft_split(d, args[1], ',');
    if (count_args(cord) != 3 || !point_struct_filled(&cylinder_cord, cord))
        return (printf("Error\ncylinder point invalid\n"), false);
    if (err)
        return (false);
   
    vctr = ft_split(d, args[2], ',');
	if (count_args(vctr) != 3 || !vector_struct_filled(&cylinder_norm, vctr))
    {
        return (printf("Error\nbad cylinder 3d normal cords\n"), false);
    }
    diameter = ft_atof(args[3], &err);
    if (err)
    {
        return (printf("Error\ncylinder diameter invalid\n"), false);
    }
    height = ft_atof(args[4], &err);
    if (err)
    {
        return (printf("Error\ncylinder height invalid\n"), false);
    }
    clrs = ft_split(d, args[5], ',');
    if (count_args(clrs) != 3 || !color_struct_filled(&cylinder_color, clrs))
        return (printf("Error\ncylinder color invalid\n"), false);
    cylinder = gc_malloc(d, sizeof(t_cylinder));
    cylinder->c = cylinder_color;
    cylinder->origin = cylinder_cord;
    cylinder->normal = cylinder_norm;
    cylinder->diameter = diameter;
    cylinder->height = height;

	add_node(d, &d->w->cylinders, create_node(d, cylinder));
	return (true);
}

bool    sphere_handled(t_data *d, char **args)
{
    char		**clrs;
    t_color		sphere_color;
    t_point		sphere_cord;
    float       diameter;
	t_sphere  *sphere;
    char		**cord;
    bool		err;

    err = false;
    cord = ft_split(d, args[1], ',');
    if (count_args(cord) != 3 || !point_struct_filled(&sphere_cord, cord))
        return (printf("Error\nsphere point invalid\n"), false);
    if (err)
        return (false);
    diameter = ft_atof(args[2], &err);
    clrs = ft_split(d, args[3], ',');
    if (count_args(clrs) != 3 || !color_struct_filled(&sphere_color, clrs))
        return (false);
    sphere = gc_malloc(d, sizeof(t_sphere));
    sphere->c = sphere_color;
    sphere->origin = sphere_cord;
    sphere->diameter = diameter;

	add_node(d, &d->w->spheres, create_node(d, sphere));
	return (true);
}

bool    elem_added(t_data *d, t_pars *p, char **args)
{
    bool	    good;

    good = false;
    if (strcmp(args[0], "A") == 0)
        good = ambient_handled(d, p, args);
	else if (strcmp(args[0], "C") == 0)
		good = camera_handled(d, p, args);
	else if (strcmp(args[0], "L") == 0)
		good = light_handled(d, args);
	else if (strcmp(args[0], "pl") == 0)
		good = plane_handled(d, args);
	else if (strcmp(args[0], "sp") == 0)
		good = sphere_handled(d, args);
	else if (strcmp(args[0], "cy") == 0)
		good = cylinder_handled(d, args);
    return (good);
}

void init_pars(t_pars *p)
{
    p->ambient_exist = false;
    p->camera_exist = false;
    p->light_exist = false;
}

bool validated_type(char *name, unsigned args_count)
{
    if ((!ft_strcmp(name, "A") && args_count == e_ambient) || 
    (!ft_strcmp(name, "C") && args_count == e_color) || 
    (!ft_strcmp(name, "L") && args_count == e_light) || 
    (!ft_strcmp(name, "pl") && args_count == e_plain) || 
    (!ft_strcmp(name, "sp") && args_count == e_sphere) || 
    (!ft_strcmp(name, "cy") && args_count == e_cylinder))
        return (true);
    return (false);
}

bool line_handled(t_data *d, t_pars *p, char *line)
{
    char    **words;
    unsigned args_count;

    if (s_is_whitespace(line))
        return (true);
    words = ft_split(d, line, ' ');
    args_count = count_args(words);
    if (args_count < 1)
        return (false);
    if (!validated_type(words[0], args_count))
        return (printf("Error\ntype unkown\n"), false);
    if (!elem_added(d, p, words))
        return (false);
    return (true);
}

bool parsed(t_data *d, char *file)
{
    t_pars p;
    int fd;
    char *line;

    d->gc = NULL;
	d->w = gc_malloc(d, sizeof(t_world));
    init_pars(&p);
    fd = open(file, O_RDONLY);
    if (fd == -1)
        return (printf("Error\nerror opening the file %s\n", file), false);
    line = get_next_line(d, fd);
    while (line)
    {
        if (!line_handled(d, &p, line))
            return (false);
        line = get_next_line(d, fd);
    }
    return (true);
}

int main(int ac, char **av)
{
    t_data d;

    if (ac != 2)
        return (printf("Error\ninvalid form, please enter ./miniRT map.rt\n"), 1);
    if (!parsed(&d, av[1]))
        return (1);
    return 0;
}
