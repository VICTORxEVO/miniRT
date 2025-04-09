/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:09:51 by sgouzi            #+#    #+#             */
/*   Updated: 2025/04/09 18:09:52 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_clr_int(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

inline t_color	rgb_add(t_color c1, t_color c2, bool is_clampt)
{
	t_color	res_color;

	res_color.r = c1.r + c2.r;
	res_color.g = c1.g + c2.g;
	res_color.b = c1.b + c2.b;
	if (is_clampt)
		return (clamp_color(res_color));
	return (res_color);
}

inline t_color	clamp_color(t_color c1)
{
	t_color	res_color;

	if (c1.r > 255)
		c1.r = 255;
	if (c1.r < 0)
		c1.r = 0;
	if (c1.g > 255)
		c1.g = 255;
	if (c1.g < 0)
		c1.g = 0;
	if (c1.b > 255)
		c1.b = 255;
	if (c1.b < 0)
		c1.b = 0;
	res_color.r = c1.r;
	res_color.g = c1.g;
	res_color.b = c1.b;
	return (res_color);
}

inline t_color	sub_colors(t_color c1, t_color c2)
{
	t_color	res_color;

	res_color.r = c1.r - c2.r;
	res_color.g = c1.g - c2.g;
	res_color.b = c1.b - c2.b;
	return (clamp_color(res_color));
}
