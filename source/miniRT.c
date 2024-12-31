#include "miniRT.h"

bool    elem_added(t_data *d, t_pars *p, char **args)
{

    if (strcmp(args[0], "A"))
    {
        if (p->ambient_exist)
            return (false);
        
    }
}

void init_pars(t_pars *p)
{
    p->ambient_exist = false;
    p->camera_exist = false;
    p->light_exist = false;
}

bool validated_type(t_pars *p, char *name, unsigned args_count)
{
    if (ft_strcmp(name, "A" && args_count == e_ambient) || 
    ft_strcmp(name, "C" && args_count == e_color) || 
    ft_strcmp(name, "L" && args_count == e_light) || 
    ft_strcmp(name, "pl" && args_count == e_plain) || 
    ft_strcmp(name, "sp" && args_count == e_sphere) || 
    ft_strcmp(name, "cy" && args_count == e_cylinder))
        return (true);
    return (false);
}

bool line_handled(t_data *d, t_pars *p, char *line)
{
    char    **words;
    unsigned args_count;

    words = ft_split(line, ' ');
    // count for newline only in line
    args_count = count_args(words);
    if (!words || args_count < 1)
        return (false);
    if (!validated_type(p, words[0], args_count))
        return (false);
    if (!elem_added(d, p, words))
        return (false);
    return (true);
}

bool parsed(t_data *d, char *file)
{
    t_pars p;
    int fd;

    init_pars(&p);
    fd = open(file, O_RDONLY);
    if (fd == -1)
        return (false);
    char *line;

    line = get_next_line(fd);
    while (line)
    {
        if (!line_handled(&p, line))
            return (false);
        free(line);
        line = get_next_line(fd);
    }
    get_next_line(-1);
}

int main(int ac, char **av, char **env)
{
    t_data d;

    if (ac != 2)
        return (printf("Error\ninvalid form, please enter ./miniRT map.rt"), 1);
    if (!parsed(&d, av[1]))
        return (printf("Error\nerror parsing the file %s\n", av[1]), 1);
    return 0;
}
