/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:19:33 by ysbai-jo          #+#    #+#             */
/*   Updated: 2025/04/11 18:42:32 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	*err_msg(const char *filename, const int n_line)
{
	char	*str;
	char	*str1;

	str = ft_strjoin(RED, filename);
	str1 = ft_strjoin(":", "error in line ");
	str = ft_strjoin(str, str1);
	str = ft_strjoin(str, ft_itoa(n_line));
	return (str);
}

bool	is_wspace(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] < 9 || s[i] > 13) && s[i] != 32)
			return (false);
		i++;
	}
	return (true);
}

bool	color_struct_filled(t_color *c, char **args)
{
	bool	error;

	error = false;
	c->r = ft_atof(args[0], &error);
	if (error || !between(c->r, 0, 255))
		return (false);
	c->g = ft_atof(args[1], &error);
	if (error || !between(c->g, 0, 255))
		return (false);
	c->b = ft_atof(args[2], &error);
	if (error || !between(c->b, 0, 255))
		return (false);
	return (true);
}

bool	point_struct_filled(t_vec *p, char **args)
{
	bool	error;

	error = false;
	p->x = ft_atof(args[0], &error);
	if (error)
		return (false);
	p->y = ft_atof(args[1], &error);
	if (error)
		return (false);
	p->z = ft_atof(args[2], &error);
	if (error)
		return (false);
	return (true);
}

bool    vector_struct_filled(t_vec	*v, char  **args)
{
    bool error;

    error = false;
	v->x = ft_atof(args[0], &error);
	if (error || !between(v->x, -1, 1))
		return (false);
	v->y = ft_atof(args[1], &error);
	if (error || !between(v->y, -1, 1))
		return (false);
	v->z = ft_atof(args[2], &error);
	if (error || !between(v->z, -1, 1))
		return (false);
    return (true);
}