/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:26:52 by sgouzi            #+#    #+#             */
/*   Updated: 2023/12/02 09:52:54 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*get_next_line(int fd)
{
	char		*t_line;
	static char	*str;
	char		*buff;
	int			bytes;

	if (we_have_a_problem(fd, &str))
		return (NULL);
	buff = malloc((100) * sizeof(char));
	if (!buff)
		return (free(buff), free(str), NULL);
	bytes = 1;
	while (!ft_strchr(str, '\n') && bytes != 0)
	{
		bytes = read(fd, buff, 100);
		if (bytes == -1)
			return (free(buff), free(str), NULL);
		buff[bytes] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	if (!str)
		return (free(str), NULL);
	t_line = ft_get_line(str);
	str = get_rest(str);
	return (t_line);
}
