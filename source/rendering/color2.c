/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:09:54 by sgouzi            #+#    #+#             */
/*   Updated: 2025/04/09 18:11:02 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

inline t_color	zero_color(void)
{
	t_color	zero;

	zero.r = 0;
	zero.g = 0;
	zero.b = 0;
	return (zero);
}

inline t_color	rgb_scl(t_color v, double scale)
{
	t_color	scaled;

	scaled.r = v.r * scale;
	scaled.g = v.g * scale;
	scaled.b = v.b * scale;
	return (scaled);
}

inline t_color	sclamp_color(t_color v, double scale)
{
	t_color	scaled;

	scaled.r = v.r * scale;
	scaled.g = v.g * scale;
	scaled.b = v.b * scale;
	return (clamp_color(scaled));
}

inline t_color	rgb_sum(t_color amb, t_color dif, t_color spc)
{
	t_color	res;

	res.r = amb.r + dif.r + spc.r;
	res.g = amb.g + dif.g + spc.g;
	res.b = amb.b + dif.b + spc.b;
	return (res);
}

inline double	get_brightness(t_color c)
{
	return (sqrtf(powf(0.299 * c.r, 2.f) + powf(0.587 * c.g, 2.f) + powf(0.114
				* c.b, 2.f)));
}
