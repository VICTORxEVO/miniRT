#include "miniRT.h"

bool    camera_handled(t_core *d, char **args)
{
    char		**cord;
    char		**vctr;
    float   	FOV;
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
    float	    light_value;
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
    t_color		plane_pattern_color;
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
    plane->reflect = 1;
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
    float       diameter;
    float       height;
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
	add_obj(d, &d->w->objects, cylinder, CY_OBJ);
	return (true);
}

bool    sphere_handled(t_core *d, char **args)
{
    char		**clrs;
    t_color		sphere_color;
    t_color		sphere_pattern_color;
    t_point		sphere_cord;
    float       diameter;
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
    sphere->reflect = 0.6;
    sphere->pattern = NULL;
    if (args[4])
        handle_pat(args[4], args[5], &sphere->pattern, sphere->c);
	add_obj(d, &d->w->objects, sphere, SP_OBJ);
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