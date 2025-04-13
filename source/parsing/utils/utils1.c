/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:10:13 by ysbai-jo          #+#    #+#             */
/*   Updated: 2025/04/13 20:59:27 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	elem_added(t_core *d, char **args)
{
	bool	good;

	good = false;
	if (ft_strncmp(args[0], "A", -1) == 0)
		good = ambient_handled(d, args);
	else if (ft_strncmp(args[0], "C", -1) == 0)
		good = camera_handled(d, args);
	else if (ft_strncmp(args[0], "l", -1) == 0)
		good = light_handled(d, args);
	else if (ft_strncmp(args[0], "L", -1) == 0)
		good = light_handled(d, args);
	else if (ft_strncmp(args[0], "pl", -1) == 0)
		good = plane_handled(d, args);
	else if (ft_strncmp(args[0], "sp", -1) == 0)
		good = sphere_handled(d, args);
	else if (ft_strncmp(args[0], "cy", -1) == 0)
		good = cylinder_handled(d, args);
	return (good);
}

bool	ambient_handled(t_core *d, char **args)
{
	char		**clrs;
	double		ambient_ratio;
	t_ambient	*ambient;
	t_color		ambient_color;
	bool		err;

	err = false;
	ambient_color = zero_color();
	if (d->w->ambient)
		return (pexit("Error\nambient already exists!", 1), false);
	ambient_ratio = ft_atof(args[1], &err);
	if (err || !between(ambient_ratio, 0, 1))
		return (pexit("Error\nambient ratio invalid!", 1), false);
	clrs = ft_split(args[2], ",");
	if (count_args(clrs) != 3 || !color_struct_filled(&ambient_color, clrs))
	{
		return (pexit("Error\nambient color invalid!", 1), false);
	}
	ambient = galloc(sizeof(t_ambient));
	ambient->ratio = ambient_ratio;
	ambient->c = ambient_color;
	d->w->ambient = ambient;
	return (true);
}
