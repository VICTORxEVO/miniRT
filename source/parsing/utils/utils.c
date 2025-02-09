#include "miniRT.h"

char *err_msg(const char *filename, const int n_line)
{
	char *str;
	char *str1;

	str = ft_strjoin(RED, filename);
	str1 = ft_strjoin(":", "error in line ");
	str = ft_strjoin(str, str1);
	str = ft_strjoin(str, ft_itoa(n_line));
	return (str);
}


bool is_wspace(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] < 9 || s[i] > 13) && s[i] != 32)
			return (false);
		i++;
	}
	return (true);
}

bool    color_struct_filled(t_color	*c, char  **args)
{
    bool error;

    error = false;
	c->r = ft_atof(args[0], &error);
	if (error || !between(c->r, 0, 255))
		return (false);
	c->g = ft_atof(args[1], &error);
	if (error || !between(c->g, 0, 255))
		return (false);
	c->b = ft_atof(args[2], &error);
	if (error || !between(c->b, 0, 255))
		return (false);
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
	if (error || !between(v->x, -1, 1))
		return (false);
	v->y = ft_atof(args[1], &error);
	if (error || !between(v->y, -1, 1))
		return (false);
	v->z = ft_atof(args[2], &error);
	if (error || !between(v->z, -1, 1))
		return (false);
    return (true);
}

bool    elem_added(t_core *d, char **args)
{
    bool	    good;

    good = false;
    if (ft_strncmp(args[0], "A", -1) == 0)
        good = ambient_handled(d, args);
	else if (ft_strncmp(args[0], "C", -1) == 0)
		good = camera_handled(d, args);
	else if (ft_strncmp(args[0], "L", -1) == 0 || ft_strncmp(args[0], "l", -1) == 0)
		good = light_handled(d, args);
	else if (ft_strncmp(args[0], "pl", -1) == 0)
		good = plane_handled(d, args);
	else if (ft_strncmp(args[0], "sp", -1) == 0)
		good = sphere_handled(d, args);
	else if (ft_strncmp(args[0], "cu", -1) == 0)
        return (cube_handled(d, args));
	else if (ft_strncmp(args[0], "cy", -1) == 0)
		good = cylinder_handled(d, args);
    return (good);
}

bool    ambient_handled(t_core *d, char **args)
{
    char		**clrs;
    double   	ambient_ratio;
    t_ambient	*ambient;
    t_color	    ambient_color;
    bool		err;

    err = false;
    ambient_color = zero_color();
    if (d->w->ambient)
        return (printf("Error\nambient already exists\n"), false);
    ambient_ratio = ft_atof(args[1], &err);
    if (err || !between(ambient_ratio, 0, 1))
        return (printf("Error\nambient ratio invalid\n"), false);
    clrs = ft_split(args[2], ',');
    if (count_args(clrs) != 3 || !color_struct_filled(&ambient_color, clrs))
    {
        return (printf("Error\nambient color invalid\n"), false);
    }
	ambient = galloc(sizeof(t_ambient));
    ambient->ratio = ambient_ratio;
	ambient->c = ambient_color;
	d->w->ambient = ambient;
	return (true);
}