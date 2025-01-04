/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:24:19 by ysbai-jo          #+#    #+#             */
/*   Updated: 2025/01/04 10:21:57 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	*get_next_line(int fd)
{
	static char	*q_res;
	char		*buff;
	int			nl_ind;
	ssize_t		rd;

	buff = malloc((size_t)BUFFER_SIZE + 1);
	if (!buff || BUFFER_SIZE <= 0)
		return (free_all(&q_res, &buff));
	rd = read(fd, buff, BUFFER_SIZE);
	buff[rd] = 0;
	while (rd >= 0)
	{
		q_res = ft_gstrjoin(&q_res, buff, rd);
		nl_ind = check_nl(q_res);
		if (nl_ind != -1)
			return (handle_it(&q_res, nl_ind + 1, &buff));
		if (!q_res || (!rd && !(*q_res)))
			break ;
		if (!rd)
			return (get_last_line(&q_res, &buff));
		rd = read(fd, buff, BUFFER_SIZE);
	}
	return (free_all(&q_res, &buff));
}

char	*handle_it(char **q_res, int nl_ind, char **buff)
{
	char	*line;
	char	*tmp;

	free(*buff);
	line = ft_substr(*q_res, 0, (size_t)(nl_ind));
	tmp = ft_substr(*q_res, nl_ind, ft_strlen(*q_res + nl_ind));
	free(*q_res);
	if (!tmp[0])
	{
		free(tmp);
		*q_res = NULL;
		return (line);
	}
	*q_res = tmp;
	return (line);
}

char	*get_last_line(char **q_res, char **buff)
{
	char	*line;

	line = ft_substr(*q_res, 0, ft_strlen(*q_res));
	free(*q_res);
	free(*buff);
	*q_res = NULL;
	return (line);
}

int	check_nl(char *str)
{
	int	m;

	m = 0;
	while (str && str[m])
	{
		if (str[m] == '\n')
			return (m);
		m++;
	}
	return (-1);
}

void	*free_all(char **q_res, char **buff)
{
	free(*buff);
	free(*q_res);
	*q_res = NULL;
	return (NULL);
}
