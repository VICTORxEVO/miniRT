#include "miniRT.h"

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

bool line_handled(t_data *d, char *line)
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
    if (!elem_added(d, words))
        return (false);
    return (true);
}

bool parsed(t_data *d, char *file)
{
    int fd;
    char *line;

    d->gc = NULL;
	d->w = gc_malloc(d, sizeof(t_world));
    fd = open(file, O_RDONLY);
    if (fd == -1)
        return (printf("Error\nerror opening the file %s\n", file), close(fd), false);
    line = get_next_line(d, fd);
    while (line)
    {
        if (!line_handled(d, line))
            return (false);
        line = get_next_line(d, fd);
    }
    if (!d->w->cam)
        return (printf("Error\nno camera found\n"), close(fd), false);
    close(fd);
    return (true);
}

bool    rendered(t_data *d)
{
    (void) d;
    return (true);
}

int main(int ac, char **av)
{
    t_data d;

    if (ac != 2)
        return (printf("Error\ninvalid form, please enter ./miniRT map.rt\n"), 1);
    if (!parsed(&d, av[1])) /* parsing logic */
        return (1);
    rendered(&d); /* rendering logic */
    gc_void(&d); /* cleanup logic */
    return 0;
}
