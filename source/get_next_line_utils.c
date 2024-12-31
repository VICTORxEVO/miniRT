/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:27:59 by sgouzi            #+#    #+#             */
/*   Updated: 2023/11/29 13:28:00 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

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

char	*ft_strjoin(char *str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*res;

	if (!str)
	{
		str = (char *)malloc(1 * sizeof(char));
		str[0] = '\0';
	}
	if (!buff)
		return (free(str), free(buff), NULL);
	res = malloc(sizeof(char) * ((ft_strlen(str) + ft_strlen(buff)) + 1));
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
	free(str);
	return (res);
}

char	*ft_get_line(char *str)
{
	int		i;
	char	*t_line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] && str[i] == '\n')
		i++;
	t_line = (char *)malloc(sizeof(char) * (i + 1));
	if (!t_line)
		return (free(str), NULL);
	i = -1;
	while (++i >= 0 && str[i] && str[i] != '\n')
		t_line[i] = str[i];
	if (str[i] == '\n')
	{
		t_line[i] = str[i];
		i++;
	}
	t_line[i] = '\0';
	return (t_line);
}

char	*get_rest(char *str)
{
	int		i;
	int		j;
	char	*buff;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	buff = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!buff)
		return (free(buff), free(str), NULL);
	i++;
	j = 0;
	while (str[i])
		buff[j++] = str[i++];
	buff[j] = '\0';
	free(str);
	return (buff);
}
