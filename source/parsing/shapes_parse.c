#include "miniRT.h"

bool    camera_handled(t_core *d, char **args)
{
    char		**cord;
    char		**vctr;
    double   	FOV;
    t_vector	vec3d;
    t_point		pcord;
    bool		err;

    err = false;
    if (d->w->cam)
    {
        return (printf("Error\ncant have more than 1 camera"), false);
    }
    cord = ft_split(args[1], ',');
    if (count_args(cord) != 3 || !point_struct_filled(&pcord, cord))
    {
        return (printf("Error\nbad camera point coordinates\n"), false);
    }
	vctr = ft_split(args[2], ',');
	if (count_args(vctr) != 3 || !vector_struct_filled(&vec3d, vctr))
    {
        return (printf("Error\nbad camera 3d vector"), false);
    }
    FOV = ft_atof(args[3], &err);
    if (err || (FOV < 0 || FOV > 180))
    {
        return (printf("Error\nbad fov value for camera"), false);
    }
    d->w->cam = galloc(sizeof(t_camera));
	d->w->cam->forward = normal(vec3d);
	d->w->cam->origin = pcord;
	d->w->cam->fov = FOV;
	return (true);
}

bool    light_handled(t_core *d, char **args)
{
    char		**clrs;
    double	    light_value;
    t_color		light_color;
    t_point		light_cord;
	t_light		*light;
    char		**cord;
    bool		err;

    err = false;
    cord = ft_split(args[1], ',');
    if (count_args(cord) != 3 || !point_struct_filled(&light_cord, cord))
        return (printf("Error\nbad light point coordinates\n"), false);
    light_value = ft_atof(args[2], &err);
    if (err || !between(light_value, 0, 1))
        return (printf("Error\nlight value invalid\n"), false);
    clrs = ft_split(args[3], ',');
    if (count_args(clrs) != 3 || !color_struct_filled(&light_color, clrs))
        return (printf("Error\nlight color invalid\n"), false);
    light = galloc(sizeof(t_light));
    light->brightness = light_value;
    light->c = light_color;
    light->p = light_cord;
	add_node(d, &d->w->lights, light, e_light);
	return (true);
}

bool    plane_handled(t_core *d, char **args)
{
    char		**clrs;
    char		**vctr;
    t_color		plane_color;
    t_point		plane_cord;
    t_vector	plane_norm;
	t_plane		*plane;
    char		**cord;

    cord = ft_split(args[1], ',');
    if (count_args(cord) != 3 || !point_struct_filled(&plane_cord, cord))
        return (printf("bad plane origin point\n"), false);
    vctr = ft_split(args[2], ',');
	if (count_args(vctr) != 3 || !vector_struct_filled(&plane_norm, vctr))
        return (printf("bad plane 3d vector\n"), false);
    clrs = ft_split(args[3], ',');
    if (count_args(clrs) != 3 || !color_struct_filled(&plane_color, clrs))
        return (printf("bad plane color\n"), false);
    plane = galloc(sizeof(t_plane));
    plane->pattern = NULL;
    plane->c = plane_color;
    plane->origin = plane_cord;
    plane->normal = plane_norm;
    plane->reflect = 0;
    if (args[4])
        handle_pat(args[4], args[5], &plane->pattern, plane->c);

    add_obj(d, &d->w->objects, plane, PL_OBJ);
	return (true);
}

bool    cylinder_handled(t_core *d, char **args)
{
    char		**clrs;
    char		**vctr;
    t_color		cylinder_color;
    t_point		cylinder_cord;
    t_vector	cylinder_norm;
    double       diameter;
    double       height;
	t_cylinder  *cylinder;
    char		**cord;
    bool		err;

    err = false;
    cord = ft_split(args[1], ',');
    if (count_args(cord) != 3 || !point_struct_filled(&cylinder_cord, cord))
        return (printf("Error\ncylinder point invalid\n"), false);
   
    vctr = ft_split(args[2], ',');
	if (count_args(vctr) != 3 || !vector_struct_filled(&cylinder_norm, vctr))
        return (printf("Error\nbad cylinder 3d normal cords\n"), false);
    diameter = ft_atof(args[3], &err);
    if (err)
        return (printf("Error\ncylinder diameter invalid\n"), false);
    height = ft_atof(args[4], &err);
    if (err)
        return (printf("Error\ncylinder height invalid\n"), false);
    clrs = ft_split(args[5], ',');
    if (count_args(clrs) != 3 || !color_struct_filled(&cylinder_color, clrs))
        return (printf("Error\ncylinder color invalid\n"), false);
    cylinder = galloc(sizeof(t_cylinder));
    cylinder->c = cylinder_color;
    cylinder->origin = cylinder_cord;
    cylinder->normal = cylinder_norm;
    cylinder->diameter = diameter;
    cylinder->height = height;
    cylinder->reflect = 0;
	add_obj(d, &d->w->objects, cylinder, CY_OBJ);
	return (true);
}

bool    sphere_handled(t_core *d, char **args)
{
    char		**clrs;
    t_color		sphere_color;
    t_point		sphere_cord;
    double       diameter;
	t_sphere  *sphere;
    char		**cord;
    bool		err;

    err = false;
    cord = ft_split(args[1], ',');
    if (count_args(cord) != 3 || !point_struct_filled(&sphere_cord, cord))
        return (printf("Error\nsphere point invalid\n"), false);
    diameter = ft_atof(args[2], &err);
    clrs = ft_split(args[3], ',');
    if (count_args(clrs) != 3 || !color_struct_filled(&sphere_color, clrs))
        return (printf("Error\nsphere color invalid\n"), false);
    sphere = galloc(sizeof(t_sphere));
    sphere->c = sphere_color;
    sphere->origin = sphere_cord;
    sphere->diameter = diameter;
    sphere->radius_squared = (diameter / 2) * (diameter / 2);
    sphere->reflect = 0;
    sphere->pattern = NULL;
    if (args[4])
        handle_pat(args[4], args[5], &sphere->pattern, sphere->c);

    add_obj(d, &d->w->objects, sphere, SP_OBJ);
	return (true);
}
t_vector get_cube_norm(t_object *o, t_point pt_on_cube)
{
    t_cube *cube = (t_cube *)o->data;
    t_point local_point = v_to_p(sub_points(pt_on_cube, cube->origin));
    
    double maxc = maxf(fabs(local_point.x), maxf(fabs(local_point.y), fabs(local_point.z)));
    
    if (maxc == fabs(local_point.x))
        return (t_vector){local_point.x > 0 ? 1 : -1, 0, 0};
    else if (maxc == fabs(local_point.y))
        return (t_vector){0, local_point.y > 0 ? 1 : -1, 0};
    return (t_vector){0, 0, local_point.z > 0 ? 1 : -1};
}

t_point get_cube_origin(t_object *o)
{
    return ((t_cube *)o->data)->origin;
}

t_color get_cube_color(t_object *o)
{
    return ((t_cube *)o->data)->c;
}

t_pattern *get_cube_pattern(t_object *o)
{
    return ((t_cube *)o->data)->pattern;
}

void set_cube_pattern(t_object *o, t_pattern *p)
{
    ((t_cube *)o->data)->pattern = p;
}

void set_cube_color(t_object *o, t_color c)
{
    ((t_cube *)o->data)->c = c;
}

double get_cube_reflect(t_object *o)
{
    return ((t_cube *)o->data)->reflect;
}
bool cube_handled(t_core *d, char **args)
{
    t_cube *cube;
    unsigned count;
    char		**cord;
    char		**clrs;

    cord = ft_split(args[1], ',');
    clrs = ft_split(args[2], ',');
    count = count_args(args);
    if (count != e_cube)
        return (false);
    cube = galloc(sizeof(t_cube));
    if (!point_struct_filled(&cube->origin, cord))
        return (false);
    if (!color_struct_filled(&cube->c, clrs))
        return (false);
    cube->pattern = NULL;
    cube->reflect = 0;
    t_object *obj = create_obj(d, cube);
    obj->type = CB_OBJ;
    obj->get_norm = get_cube_norm;
    obj->get_origin = get_cube_origin;
    obj->get_color = get_cube_color;
    obj->get_pattern = get_cube_pattern;
    obj->set_pattern = set_cube_pattern;
    obj->set_color = set_cube_color;
    obj->get_reflect = get_cube_reflect;
    add_obj(d, &d->w->objects, cube, CB_OBJ);
    return (true);
}


void handle_pat(char *patt_name, char *patt_clrs, t_pattern  **pat, t_color main_clr)
{
    t_color scnd_clr;
    char    **clrs;

    if ((ft_strcmp(patt_name, "checkered")) != 0 && 
        (ft_strcmp(patt_name, "striped_x")) != 0 && 
        (ft_strcmp(patt_name, "gradient_y")) != 0 &&
        (ft_strcmp(patt_name, "ring_z")) != 0 &&
        (ft_strcmp(patt_name, "swirl") != 0 ) && 
        (patt_clrs) && (patt_clrs[0]))
        pexit("Error\n pattern settings invalid\n", BadValue);
        
    else
    {
        clrs = ft_split(patt_clrs, ',');
        if (count_args(clrs) != 3 || !color_struct_filled(&scnd_clr, clrs))
            pexit("Error\n pattern color invalid\n", BadValue);
        (*pat) = galloc(sizeof(t_pattern));
        if (ft_strcmp(patt_name, "checkered") == 0)
            (*pat)->type = CHECKER_PAT;
        else if (ft_strcmp(patt_name, "striped_x") == 0)
            (*pat)->type = STRIPE_X_PAT;
        else if (ft_strcmp(patt_name, "gradient_y") == 0)
            (*pat)->type = GRADIANT_Y;
        else if (ft_strcmp(patt_name, "ring_z") == 0)
            (*pat)->type = RING_Z_PAT;
        else if (ft_strcmp(patt_name, "swirl") == 0)
            (*pat)->type = SWIRL;
        else
            pexit("Error\n pattern type invalid\n", BadValue);
        (*pat)->c1 = main_clr;
        (*pat)->c2 = scnd_clr;
    }
}