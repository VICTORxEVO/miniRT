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

void    loadline(char *line, int n_line, char *filename)
{
    char    **words;
    unsigned args_count;

    if (s_is_whitespace(line))
        return (true);
    words = ft_split(line, ' ');
    args_count = count_args(words);
    if (args_count < 1)
        return (false);
    if (!validated_type(words[0], args_count))
        pexit("unknown type !", 1);
    if (!elem_added(getengine(), words))
        pexit("error !", 1);
}

bool parsing(int ac, char *filename)
{
    int fd;
    char *line;

    if (ac != 2)
        pexit(YELLOW USAGE_WARN, 1);
    fd = check_file(filename);
    if (fd < 0)
        pexit(filename, 2);
    readfile(fd);
    close(fd);
    return (true);
}