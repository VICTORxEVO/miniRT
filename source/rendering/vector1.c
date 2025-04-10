/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:10:29 by sgouzi            #+#    #+#             */
/*   Updated: 2025/04/10 11:27:26 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

inline t_vec	vec_add(t_vec v1, t_vec v2)
{
	t_vec	res_v;

	res_v.x = v1.x + v2.x;
	res_v.y = v1.y + v2.y;
	res_v.z = v1.z + v2.z;
	return (res_v);
}

inline t_vec	vec_sub(t_vec p1, t_vec p2)
{
	t_vec	res_p;

	res_p.x = p1.x - p2.x;
	res_p.y = p1.y - p2.y;
	res_p.z = p1.z - p2.z;
	return (res_p);
}

inline t_vec	vec_neg(t_vec v1)
{
	t_vec	neg;

	neg.x = 0 - v1.x;
	neg.y = 0 - v1.y;
	neg.z = 0 - v1.z;
	return (neg);
}

inline t_vec	vec_scl(t_vec v, double scale)
{
	t_vec	scaled;

	scaled.x = v.x * scale;
	scaled.y = v.y * scale;
	scaled.z = v.z * scale;
	return (scaled);
}

inline double	vec_len(t_vec v1)
{
	double	len;

	len = sqrtf(pow(v1.x, 2) + pow(v1.y, 2) + pow(v1.z, 2));
	return (len);
}
