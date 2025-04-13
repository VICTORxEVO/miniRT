/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_parse1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:12:58 by ysbai-jo          #+#    #+#             */
/*   Updated: 2025/04/13 20:59:14 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	cylinder_helper(t_parse_cylinder *pc)
{
	pc->cylinder->c = pc->cylinder_color;
	pc->cylinder->origin = pc->cylinder_cord;
	pc->cylinder->normal = normal(pc->cylinder_norm);
	pc->cylinder->diameter = pc->diameter;
	pc->cylinder->height = pc->height;
}

bool	cylinder_handled(t_core *d, char **args)
{
	t_parse_cylinder	pc;

	pc.err = false;
	pc.cord = ft_split(args[1], ",");
	if (count_args(pc.cord) != 3 || !point_struct_filled(&pc.cylinder_cord,
			pc.cord))
		return (pexit("Error\ncylinder point invalid!", 1), false);
	pc.vctr = ft_split(args[2], ",");
	if (count_args(pc.vctr) != 3 || !vector_struct_filled(&pc.cylinder_norm,
			pc.vctr))
		return (pexit("Error\nbad cylinder 3d normal cords!", 1), false);
	pc.diameter = ft_atof(args[3], &pc.err);
	if (pc.err)
		return (pexit("Error\ncylinder diameter invalid!", 1), false);
	pc.height = ft_atof(args[4], &pc.err);
	if (pc.err)
		return (pexit("Error\ncylinder height invalid!", 1), false);
	pc.clrs = ft_split(args[5], ",");
	if (count_args(pc.clrs) != 3 || !color_struct_filled(&pc.cylinder_color,
			pc.clrs))
		return (pexit("Error\ncylinder color invalid!", 1), false);
	pc.cylinder = galloc(sizeof(t_cylinder));
	cylinder_helper(&pc);
	add_obj(&d->w->objects, pc.cylinder, CY_OBJ);
	return (true);
}
