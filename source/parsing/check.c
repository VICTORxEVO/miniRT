/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:21:35 by ysbai-jo          #+#    #+#             */
/*   Updated: 2025/04/11 17:25:19 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	readfile(int fd, char *filename)
{
	char	*line;
	int		n_line;

	n_line = 1;
	line = get_next_line(fd);
	gc_add_node(line);
	if (!line || !*line)
		pexit(ft_strjoin(ft_strjoin(RED, filename), EMPTFILE_ERR), 3);
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		loadline(line, n_line, filename);
		clear_1data(line);
		line = get_next_line(fd);
		n_line++;
	}
	if (!getengine()->w->lights)
		pexit(ft_strjoin(ft_strjoin(RED, filename), NOLIGHT_ERR), 4);
	if (!getengine()->w->cam)
		pexit(ft_strjoin(ft_strjoin(RED, filename), NOCAM_ERR), 5);
	if (!getengine()->w->ambient)
		pexit(ft_strjoin(ft_strjoin(RED, filename), NOAMB_ERR), 6);
}

int	check_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	return (fd);
}
