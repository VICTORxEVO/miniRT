# include "miniRT.h"

static bool validated_type(char *name, unsigned args_count)
{
    if ((!ft_strcmp(name, "A") && args_count == e_ambient) || 
    (!ft_strcmp(name, "C") && args_count == e_color) || 
    (!ft_strcmp(name, "L") && args_count == e_light) || 
    (!ft_strcmp(name, "l") && args_count == e_light) ||
    (!ft_strcmp(name, "pl") && args_count == e_plain) || 
    (!ft_strcmp(name, "pl") && args_count == e_plain_pattern) || 
    (!ft_strcmp(name, "sp") && args_count == e_sphere) || 
    (!ft_strcmp(name, "sp") && args_count == e_sphere_texture) || 
    (!ft_strcmp(name, "sp") && args_count == e_sphere_pattern) || 
    (!ft_strcmp(name, "cy") && args_count == e_cylinder) || 
    (!ft_strcmp(name, "cu") && args_count == e_cube) ||
    (!ft_strcmp(name, "co") && args_count == e_cone))
        return (true);
    return (false);
}

bool    starts_with(char    *s, char    *start)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (s[i] && start[i] && start[i] == s[i])
    {
        if (s[i] != start[j])
            return false;
        i++;
        j++;
    }
    if (i != j)
        return false;
    if (start[j])
        return false;
    return (true);
}

void    loadline(char *line, int n_line, char *filename)
{
    char    **words;
    unsigned args_count;

    if (is_wspace(line) || starts_with(line, "#"))
        return ;
    words = ft_split(line, " \n\v\t");
    args_count = count_args(words);
    if (args_count < 1)
        pexit(err_msg(filename, n_line), 3);
    if (!validated_type(words[0], args_count))
        pexit(ft_strjoin("unknown type  -> ", words[0]), 1);
    if (!elem_added(getengine(), words))
        pexit("error !", 1);
}

void setup_cam_dir(t_camera	*cam)
{
	t_vec	temp_up;
	// calc up, right vectors for where the cam is lookin (forward)
	temp_up = (t_vec) {0, 1, 0};
	cam->right = normal(cross(temp_up, cam->forward)); 
	cam->up = normal(cross(cam->forward, cam->right)); // now reset up
    cam->aspect = (SCREEN_WIDTH / SCREEN_HEIGHT);

}

bool    ends_with(char *small, char *big)
{
    int i;
    int j;
    i = strlen(small) - 1;
    j = strlen(big) - 1;
    if (j < i)
        return false;
    while (i > 0)
    {
        if (small[i] != big[j])
            return false;
        i--;
        j--;
    }
    return (i == 0);
}

void parsing(int ac, char *filename)
{
    int fd;
    t_core  *engine;

    srand((unsigned int)time(NULL));
    engine = getengine();
    engine->w = galloc(sizeof(t_world));
    engine->m.mlx = mlx_init();
	engine->m.win = mlx_new_window(engine->m.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "miniRT");
    engine->m.ctrl_pressed = false;
    if (ac != 2)
        pexit(YELLOW USAGE_WARN, 1);
    fd = check_file(filename);
    if (fd < 0)
        pexit(filename, 2);
    readfile(fd, filename);
	setup_cam_dir(engine->w->cam);
    engine->w->gray_on = false;
    engine->cmd_on = true;
    engine->rays_px = 1.f;
    engine->aa_on = false;
    engine->iter = 1;
	engine->png = galloc(SCREEN_WIDTH * SCREEN_HEIGHT * 3);
    engine->refl_on = true;
	engine->counter = 0;

    close(fd);
}