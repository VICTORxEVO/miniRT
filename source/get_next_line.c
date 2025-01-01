
#include "miniRT.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(t_data *d, char *str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*res;

	if (!str)
	{
		str = (char *)gc_malloc(d, 1 * sizeof(char));
		str[0] = '\0';
	}
	if (!buff)
		return (NULL);
	res = gc_malloc(d, sizeof(char) * ((ft_strlen(str) + ft_strlen(buff)) + 1));
	if (res == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (str)
		while (str[++i] != '\0')
			res[i] = str[i];
	while (buff[j] != '\0')
		res[i++] = buff[j++];
	res[ft_strlen(str) + ft_strlen(buff)] = '\0';
	return (res);
}

char	*ft_get_line(t_data *d, char *str)
{
	int		i;
	char	*t_line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	t_line = (char *)gc_malloc(d, sizeof(char) * (i + 1));
	i = -1;
	while (++i >= 0 && str[i] && str[i] != '\n')
		t_line[i] = str[i];
	t_line[i] = '\0';
	return (t_line);
}

char	*get_rest(t_data *d, char *str)
{
	int		i;
	int		j;
	char	*buff;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (NULL);
	buff = (char *)gc_malloc(d, sizeof(char) * (ft_strlen(str) - i + 1));
	if (!buff)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		buff[j++] = str[i++];
	buff[j] = '\0';
	return (buff);
}

char	*get_next_line(t_data *d, int fd)
{
	char		*t_line;
	static char	*str;
	char		*buff;
	int			bytes;

	buff = gc_malloc(d, (100) * sizeof(char));
	bytes = 1;
	while (!ft_strchr(str, '\n') && bytes != 0)
	{
		bytes = read(fd, buff, 100);
		if (bytes == -1)
			return (NULL);
		buff[bytes] = '\0';
		str = ft_strjoin(d, str, buff);
	}
	if (!str)
		return (NULL);
	t_line = ft_get_line(d, str);
	str = get_rest(d, str);
	return (t_line);
}
