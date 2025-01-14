# include "miniRT.h"

static bool validated_type(char *name, unsigned args_count)
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
    words = ft_split(line, ' ');
    args_count = count_args(words);
    if (args_count < 1)
        pexit(err_msg(filename, n_line), 3);
    if (!validated_type(words[0], args_count))
        pexit("unknown type !", 1);
    if (!elem_added(getengine(), words))
        pexit("error !", 1);
}

void setup_cam_dir(t_camera	*cam)
{
	t_vector	temp_up;
	// calc up, right vectors for where the cam is lookin (forward)
	temp_up = (t_vector) {0, 1, 0};
	cam->right = normal(cross(temp_up, cam->forward)); 
	cam->up = normal(cross(cam->forward, cam->right)); // now reset up
    cam->aspect = (SCREEN_WIDTH / SCREEN_HEIGHT);

}

void parsing(int ac, char *filename)
{
    int fd;
    char *line;
    t_core  *engine;
    void *d;

    engine = getengine();
    
    engine->w = galloc(sizeof(t_world));
    engine->m.mlx = mlx_init();
	engine->m.win = mlx_new_window(engine->m.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Hello world!");
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
    engine->iter = 1;
    close(fd);
}