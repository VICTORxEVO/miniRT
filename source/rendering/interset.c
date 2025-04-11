/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:07:45 by sgouzi            #+#    #+#             */
/*   Updated: 2025/04/11 18:24:05 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_eq	calc_equation(double radius, t_cylinder *cy, t_ray *r, t_vec X)
{
	t_eq	eq;

	eq.a = vec_dot(r->direction, r->direction) - pow(vec_dot(r->direction,
				cy->normal), 2);
	eq.b = 2 * (vec_dot(r->direction, X) - vec_dot(r->direction, cy->normal)
			* vec_dot(X, cy->normal));
	eq.c = vec_dot(X, X) - pow(vec_dot(X, cy->normal), 2) - (radius * radius);
	eq.d = eq.b * eq.b - 4 * eq.a * eq.c;
	return (eq);
}

t_inter	sp_intersect(t_sphere *s, t_ray *ray)
{
	t_vec	oc;
	t_eq	eq;
	t_inter	it;

	it.t1 = -1;
	it.t2 = -1;
	oc = vec_sub(ray->origin, s->origin);
	eq.a = vec_dot(ray->direction, ray->direction);
	eq.b = 2.0f * vec_dot(ray->direction, oc);
	eq.c = vec_dot(oc, oc) - s->radius_squared;
	eq.d = (eq.b * eq.b) - (4.0f * eq.a * eq.c);
	if (eq.d < 0 || fabs(eq.a) < EPSILON)
		return (it);
	it.t1 = (-eq.b - sqrt(eq.d)) / (2.0f * eq.a);
	it.t2 = (-eq.b + sqrt(eq.d)) / (2.0f * eq.a);
	if (it.t1 < 0 && it.t2 > 0)
		it.t1 = it.t2;
	return (it);
}

t_inter	pl_intersect(t_plane *pl, t_ray *ray)
{
	double	denom;
	double	t;
	t_inter	it;
	t_vec	pl_to_ray;

	it.t1 = -1;
	it.t2 = -1;
	denom = vec_dot(pl->normal, ray->direction);
	if (fabs(denom) < EPSILON)
		return (it);
	pl_to_ray = vec_sub(pl->origin, ray->origin);
	t = vec_dot(pl_to_ray, pl->normal) / denom;
	if (t >= EPSILON)
	{
		it.t1 = t;
		it.t2 = t;
	}
	return (it);
}

t_color	intersect_world(t_world *w, t_ray *cam_ray)
{
	t_hit	hit;
	t_color	final;
	t_color	ambient_color;
	t_node	*light_node;
	t_calc	calc;

	light_node = w->lights;
	final = zero_color();
	hit = find_hit(w, cam_ray);
	calc.obj_clr = zero_color();
	while (light_node && hit.obj)
	{
		calc.light = light_node->data;
		calc.lighted = false;
		calc.smallest_t = hit.t1;
		final = rgb_add(final, lighting(cam_ray, hit.obj, &calc), false);
		light_node = light_node->next;
	}
	ambient_color = get_ambient(calc.lighted, w, hit.obj, calc.obj_clr);
	final = rgb_add(final, ambient_color, true);
	final = clamp_color(final);
	return (final);
}

double	get_intersect_dist(t_world *w, t_ray *ray)
{
	t_object	*node;
	double		smallest_t;

	smallest_t = __FLT_MAX__;
	node = w->objects;
	while (node)
	{
		smallest_t = get_smallest_t(node, ray);
		node = node->next;
	}
	return (smallest_t);
}
