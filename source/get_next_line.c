
#include "miniRT.h"

int	we_have_a_problem(int fd, char **str)
{
	if (fd < 0 || read(fd, 0, 0) < 0)
	{
		if (str)
		{
			free(*str);
			*str = NULL;
		}
		return (1);
	}
	return (0);
}

char	*get_next_line(t_data *d, int fd)
{
	char		*t_line;
	static char	*str;
	char		*buff;
	int			bytes;

	if (we_have_a_problem(fd, &str))
		return (NULL);
	buff = gc_malloc(d, (100) * sizeof(char));
	bytes = 1;
	while (!ft_strchr(str, '\n') && bytes != 0)
	{
		bytes = read(fd, buff, 100);
		if (bytes == -1)
			return (free(buff), free(str), NULL);
		buff[bytes] = '\0';
		str = ft_strjoin(d, str, buff);
	}
	if (!str)
		return (free(str), NULL);
	t_line = ft_get_line(d, str);
	str = get_rest(d, str);
	return (t_line);
}
