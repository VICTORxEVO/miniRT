/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:09:48 by sgouzi            #+#    #+#             */
/*   Updated: 2025/04/13 22:13:37 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	generate_cam_dir(t_camera *cam, double scale, double ndcx, double ndcy)
{
	t_vec	dir;

	dir = cam->forward;
	dir.x += (ndcx * scale * cam->aspect * cam->right.x) + (ndcy * scale
			* cam->up.x);
	dir.y += (ndcx * scale * cam->aspect * cam->right.y) + (ndcy * scale
			* cam->up.y);
	dir.z += (ndcx * scale * cam->aspect * cam->right.z) + (ndcy * scale
			* cam->up.z);
	return (normal(dir));
}

t_vec	get_cam_dir(double x, double y, int i)
{
	t_camera	*cam;
	t_core		*engine;
	double		scale;
	double		ndc_x;
	double		ndc_y;

	engine = getengine();
	cam = engine->w->cam;
	scale = tan(deg_to_rad(cam->fov) / 2.f);
	if (RAYS_PX < 2)
		ndc_x = (2.f * ((x + 0.5f) / SCREEN_WIDTH)) - 1.f;
	else
		ndc_x = (2.f * ((x + ((i / RAYS_PX) + 0.5f)) / SCREEN_WIDTH)) - 1.f;
	ndc_y = 1 - (2.f * (y + 0.5) / SCREEN_HEIGHT);
	return (generate_cam_dir(cam, scale, ndc_x, ndc_y));
}
