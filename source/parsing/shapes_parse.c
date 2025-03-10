#include "miniRT.h"

bool    camera_handled(t_core *d, char **args)
{
    char		**cord;
    char		**vctr;
    double   	FOV;
    t_vec	vec3d;
    t_vec		pcord;
    bool		err;

    err = false;
    if (d->w->cam)
    {
        return (printf("Error\ncant have more than 1 camera"), false);
    }
    cord = ft_split(args[1], ",");
    if (count_args(cord) != 3 || !point_struct_filled(&pcord, cord))
    {
        return (printf("Error\nbad camera point coordinates\n"), false);
    }
	vctr = ft_split(args[2], ",");
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
    t_vec		light_cord;
	t_light		*light;
    char		**cord;
    bool		err;

    err = false;
    cord = ft_split(args[1], ",");
    if (count_args(cord) != 3 || !point_struct_filled(&light_cord, cord))
        return (printf("Error\nbad light point coordinates\n"), false);
    light_value = ft_atof(args[2], &err);
    if (err || !between(light_value, 0, 1))
        return (printf("Error\nlight value invalid\n"), false);
    clrs = ft_split(args[3], ",");
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
    t_vec		plane_cord;
    t_vec	plane_norm;
	t_plane		*plane;
    char		**cord;

    cord = ft_split(args[1], ",");
    if (count_args(cord) != 3 || !point_struct_filled(&plane_cord, cord))
        return (printf("bad plane origin point\n"), false);
    vctr = ft_split(args[2], ",");
	if (count_args(vctr) != 3 || !vector_struct_filled(&plane_norm, vctr))
        return (printf("bad plane 3d vector\n"), false);
    clrs = ft_split(args[3], ",");
    if (count_args(clrs) != 3 || !color_struct_filled(&plane_color, clrs))
        return (printf("bad plane color\n"), false);
    plane = galloc(sizeof(t_plane));
    plane->pattern = NULL;
    plane->c = plane_color;
    plane->origin = plane_cord;
    plane->normal = plane_norm;
    plane->reflect = 0;
    if (args[4])
        handle_pat(args, plane, PL_OBJ);
    add_obj(d, &d->w->objects, plane, PL_OBJ);
	return (true);
}

bool    cylinder_handled(t_core *d, char **args)
{
    char		**clrs;
    char		**vctr;
    t_color		cylinder_color;
    t_vec		cylinder_cord;
    t_vec	cylinder_norm;
    double       diameter;
    double       height;
	t_cylinder  *cylinder;
    char		**cord;
    bool		err;

    err = false;
    cord = ft_split(args[1], ",");
    if (count_args(cord) != 3 || !point_struct_filled(&cylinder_cord, cord))
        return (printf("Error\ncylinder point invalid\n"), false);
   
    vctr = ft_split(args[2], ",");
	if (count_args(vctr) != 3 || !vector_struct_filled(&cylinder_norm, vctr))
        return (printf("Error\nbad cylinder 3d normal cords\n"), false);
    diameter = ft_atof(args[3], &err);
    if (err)
        return (printf("Error\ncylinder diameter invalid\n"), false);
    height = ft_atof(args[4], &err);
    if (err)
        return (printf("Error\ncylinder height invalid\n"), false);
    clrs = ft_split(args[5], ",");
    if (count_args(clrs) != 3 || !color_struct_filled(&cylinder_color, clrs))
        return (printf("Error\ncylinder color invalid\n"), false);
    cylinder = galloc(sizeof(t_cylinder));
    cylinder->c = cylinder_color;
    cylinder->origin = cylinder_cord;
    cylinder->normal = normal(cylinder_norm);
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
    t_vec		sphere_cord;
    double       diameter;
	t_sphere  *sphere;
    char		**cord;
    bool		err;

    err = false;
    cord = ft_split(args[1], ",");
    if (count_args(cord) != 3 || !point_struct_filled(&sphere_cord, cord))
        return (printf("Error\nsphere point invalid\n"), false);
    diameter = ft_atof(args[2], &err);
    clrs = ft_split(args[3], ",");
    if (count_args(clrs) != 3 || !color_struct_filled(&sphere_color, clrs))
        return (printf("Error\nsphere color invalid\n"), false);
    sphere = galloc(sizeof(t_sphere));
    sphere->c = sphere_color;
    sphere->origin = sphere_cord;
    sphere->diameter = diameter;
    sphere->radius_squared = (diameter / 2) * (diameter / 2);
    sphere->reflect = 0;
    sphere->pattern = NULL;
    sphere->texture = NULL;
    valid_pat(args);
    if (args[4])
    {
        handle_pat(args, sphere, SP_OBJ);
    }
    add_obj(d, &d->w->objects, sphere, SP_OBJ);
	return (true);
}

t_vec get_cube_origin(t_object *o)
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

    cord = ft_split(args[1], ",");
    clrs = ft_split(args[2], ",");
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

bool cone_handled(t_core *d, char **args)
{
    t_cone *cone;
    double count;
    bool		err;
    char		**cord;
    char		**clrs;
    char		**norm;

    count = count_args(args);
    if (count != e_cone)
        return (false);
    cord = ft_split(args[1], ",");
    norm = ft_split(args[2], ",");
    clrs = ft_split(args[3], ",");
    cone = galloc(sizeof(t_cone));
    // printf("-> after galloec \n");
    if (!point_struct_filled(&cone->tip, cord))
        return (false);
    if (!point_struct_filled(&cone->norm, norm))
        return (false);
    cone->norm = normal(cone->norm);
    if (!color_struct_filled(&cone->c, clrs))
        return (false);
    cone->height = ft_atof(args[4], &err);
    cone->angle = 45 * (M_PI / 180.0) / 2.0;
    cone->cosangle = cos(cone->angle);
    cone->cosangle2 = cone->cosangle * cone->cosangle;
    cone->sec_squared = 1.0 / cone->cosangle2;
    t_object *obj = create_obj(d, cone);
    obj->type = CO_OBJ;
    add_obj(d, &d->w->objects, cone, CO_OBJ);
    return (true);
}

void    valid_pat(char **args)
{
    
    char *patt_name;
    char *patt_clrs;

    patt_name = args[4];
    if (patt_name)
        patt_clrs = args[5];
    else
        patt_clrs = NULL;
    if (patt_name && !patt_clrs && !ends_with(".xpm", patt_name))
        pexit("Error\n texture settings invalid\n", BadValue);
    if (patt_name && (ft_strcmp(patt_name, "checkered")) != 0 && 
    (ft_strcmp(patt_name, "striped_x")) != 0 && 
    (ft_strcmp(patt_name, "gradient_y")) != 0 &&
    (ft_strcmp(patt_name, "ring_z")) != 0 &&
    (ft_strcmp(patt_name, "swirl") != 0 ) && 
    (patt_clrs) && (patt_clrs[0]))
        pexit("Error\n pattern settings invalid\n", BadValue);
    return ;
}

int get_pixel_color(char *img_data, int x, int y, int w, int h, int size_line, int bits_per_pixel)
{
    // Boundary checks

    if (!img_data || x < 0 || y < 0)
        return (0);  // Return black or some default color
    
    int bytes_per_pixel = bits_per_pixel / 8;
    int index = y * size_line + (w - x) * bytes_per_pixel;
    
    // Safety check - don't read beyond data
    if (index < 0)
        return (0);
    
    // For RGBA format, read each byte separately to avoid alignment issues
    unsigned char b = img_data[index];
    unsigned char g = img_data[index + 1];
    unsigned char r = img_data[index + 2];
    
    // Combine into a single integer
    return (r << 16) | (g << 8) | b;
}

void handle_texture(t_sphere *sphere, char *texture_name)
{
    int fd = open(texture_name, O_RDONLY);
    if (fd < 0)
        pexit("Error\n bad texture file\n", BadValue);
    close(fd);
    sphere->texture = galloc(sizeof(t_texture));
    void *img_ptr;
    char *img_data;
    int w;
    int h;
    img_ptr = mlx_xpm_file_to_image(getengine()->m.mlx, texture_name, &w, &h);
    if (!img_ptr)
        pexit("problem loading the texture\n", BadAlloc);
    int bits_per_pixel, size_line, endian;
    img_data = mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);
    sphere->texture->img_ptr = img_ptr;
    sphere->texture->img_data = img_data;
    sphere->texture->height = h;
    sphere->texture->width = w;
    sphere->texture->bpp = bits_per_pixel;
    sphere->texture->size_line = size_line;
    sphere->texture->endian = endian;
}

void handle_pat(char **args, void *obj, int type)
{
    t_color scnd_clr;
    t_color main_clr;
    t_pattern   *pat;
    char    **clrs;
    if (args[4] && !args[5] && type == SP_OBJ)
        handle_texture(obj, args[4]);
    else
    {
        char    *patt_clrs = args[5];
        char    *patt_name = args[4];
        if (type == SP_OBJ)
            main_clr = ((t_sphere *)obj)->c;
        else 
            main_clr = ((t_plane *)obj)->c;
        clrs = ft_split(patt_clrs, ",");
        if (count_args(clrs) != 3 || !color_struct_filled(&scnd_clr, clrs))
            pexit("Error\n pattern color invalid\n", BadValue);
        pat = galloc(sizeof(t_pattern));
        if (ft_strcmp(patt_name, "checkered") == 0)
            pat->type = CHECKER_PAT;
        else if (ft_strcmp(patt_name, "striped_x") == 0)
            pat->type = STRIPE_X_PAT;
        else if (ft_strcmp(patt_name, "gradient_y") == 0)
            pat->type = GRADIANT_Y;
        else if (ft_strcmp(patt_name, "ring_z") == 0)
            pat->type = RING_Z_PAT;
        else if (ft_strcmp(patt_name, "swirl") == 0)
            pat->type = SWIRL;
        else
            pexit("Error\n pattern type invalid\n", BadValue);
        pat->c1 = main_clr;
        pat->c2 = scnd_clr;
        if (type == SP_OBJ)
            ((t_sphere *)obj)->pattern = pat;
        else 
            ((t_plane *)obj)->pattern = pat;
    }
}