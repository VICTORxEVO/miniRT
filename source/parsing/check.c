#include "miniRT.h"

void    readfile(int fd, char *filename)
{
    char *line;
    int n_line;

    n_line = 1;
    line = get_next_line(fd);
    gc_add_node(line);
    if (!line || !*line)
        pexit(ft_strjoin(ft_strjoin(RED, filename), EMPTFILE_ERR), 3);
    while(line)
    {
        loadline(line, n_line, filename);
        clear_1data(line);
        line = get_next_line(fd);
        n_line++;
    }
}


int check_file(char *filename)
{
    char *dot_pos;
    int fd;

    dot_pos = ft_strchr(filename, '.');
    if (!dot_pos || *dot_pos == filename[0] 
        || ft_strncmp(dot_pos, ".rt", -1) != 0)
        pexit(RED FILEEXT_ER, 1);
    fd = open(filename, O_RDONLY);
    return(fd);
}
