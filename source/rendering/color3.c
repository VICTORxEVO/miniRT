/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:09:55 by sgouzi            #+#    #+#             */
/*   Updated: 2025/04/09 18:11:37 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

inline t_color	rgb_mul(t_color c1, t_color c2)
{
	t_color	res_color;

	res_color.r = c1.r * c2.r / 255;
	res_color.g = c1.g * c2.g / 255;
	res_color.b = c1.b * c2.b / 255;
	return (clamp_color(res_color));
}

inline t_color	rgb_mad(t_color c1, t_color c2)
{
	t_color	res_color;

	if (c1.r == 0 || c2.r == 0)
		res_color.r = (c1.r + c2.r) / 2;
	else
		res_color.r = c1.r * c2.r / 255;
	if (c1.g == 0 || c2.g == 0)
		res_color.g = (c1.g + c2.g) / 2;
	else
		res_color.g = c1.g * c2.g / 255;
	if (c1.b == 0 || c2.b == 0)
		res_color.b = (c1.b + c2.b) / 2;
	else
		res_color.b = c1.b * c2.b / 255;
	return (clamp_color(res_color));
}

inline t_color	rgb_to_gray(t_color c)
{
	int	gray;

	gray = (0.299 * c.r + 0.587 * c.g + 0.114 * c.b);
	return ((t_color){gray, gray, gray});
}
