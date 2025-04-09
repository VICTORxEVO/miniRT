/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:10:30 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/10/12 19:20:19 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	no_meaning_variable;

	no_meaning_variable = 0;
	if (fd != -1 || s)
	{
		while (*s)
			no_meaning_variable = write(fd, s++, 1);
	}
	fd = no_meaning_variable;
}
