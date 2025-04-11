/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:24:24 by sgouzi            #+#    #+#             */
/*   Updated: 2025/04/11 18:24:55 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	validate_body_height(t_cylinder *cy, t_ray *r, double body_hit)
{
	t_vec	hit_point;
	double	height;

	hit_point = vec_add(r->origin, (vec_scl(r->direction, body_hit)));
	height = vec_dot(vec_sub(hit_point, cy->origin), cy->normal);
	if (height < 0 || height > cy->height)
		return (-1);
	return (body_hit);
}

double	calculate_body_intersection(t_cylinder *cy, t_ray *r)
{
	t_eq	eq;
	t_vec	x;
	double	radius;
	double	body_hit;
	t_inter	it;

	body_hit = -1;
	radius = cy->diameter / 2;
	x = vec_sub(r->origin, cy->origin);
	eq = calc_equation(radius, cy, r, x);
	if (eq.d >= 0)
	{
		it.t1 = (-eq.b - sqrt(eq.d)) / (2 * eq.a);
		it.t2 = (-eq.b + sqrt(eq.d)) / (2 * eq.a);
		if (it.t1 > 0)
			body_hit = it.t1;
		else if (it.t2 > 0)
			body_hit = it.t2;
		if (body_hit > 0)
			body_hit = validate_body_height(cy, r, body_hit);
	}
	return (body_hit);
}

double	calculate_cap_intersection(t_ray *r, t_vec center, t_vec normal,
		double radius)
{
	t_vec	x;
	double	denom;
	double	cap_hit;
	double	t;
	t_vec	point;

	x = vec_sub(r->origin, center);
	denom = vec_dot(r->direction, normal);
	cap_hit = -1;
	if (fabs(denom) > EPSILON)
	{
		t = -vec_dot(x, normal) / denom;
		if (t > 0)
		{
			point = vec_add(r->origin, (vec_scl(r->direction, t)));
			if (vec_len(vec_sub(point, center)) <= radius)
				cap_hit = t;
		}
	}
	return (cap_hit);
}

double	find_closest_hit(t_cylinder *cy, t_ray *r, double radius,
		double top_hit)
{
	double	hits[3];
	double	min_hit;
	int		i;
	double	body_hit;
	double	bottom_hit;

	body_hit = calculate_body_intersection(cy, r);
	bottom_hit = calculate_cap_intersection(r, cy->origin, cy->normal, radius);
	hits[0] = body_hit;
	hits[1] = bottom_hit;
	hits[2] = top_hit;
	min_hit = __FLT_MAX__;
	i = 0;
	while (i < 3)
	{
		if (hits[i] > 0 && hits[i] < min_hit)
			min_hit = hits[i];
		i++;
	}
	if (min_hit == __FLT_MAX__)
		return (-1);
	return (min_hit);
}

t_inter	cy_intersect(t_cylinder *cy, t_ray *r)
{
	double	radius;
	double	top_hit;
	double	closest_hit;
	t_vec	top_center;
	t_inter	it;

	radius = cy->diameter / 2;
	top_hit = -1;
	it.t1 = -1;
	it.t2 = -1;
	top_center = vec_add(cy->origin, (vec_scl(cy->normal, cy->height)));
	top_hit = calculate_cap_intersection(r, top_center, cy->normal, radius);
	closest_hit = find_closest_hit(cy, r, radius, top_hit);
	if (closest_hit > 0)
	{
		it.t1 = closest_hit;
		it.t2 = closest_hit;
	}
	return (it);
}
