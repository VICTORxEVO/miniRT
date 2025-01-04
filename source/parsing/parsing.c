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

static bool line_handled(t_data *d, char *line)
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

bool parsing(int ac, char *filename)
{
    int fd;
    char *line;

    if (ac != 2)
        pexit(RED USAGE_WARN, 1);
    line = get_next_line(fd);
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