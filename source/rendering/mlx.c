/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:10:11 by sgouzi            #+#    #+#             */
/*   Updated: 2025/04/13 18:24:37 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	close_window(t_core *engine)
{
	printf("here\n");
	
	mlx_destroy_window(engine->m.mlx, engine->m.win);
	mlx_destroy_image(engine->m.mlx, engine->img.img);
	mlx_destroy_display(engine->m.mlx);
	free(engine->m.mlx);
	clear();
	exit(0);
	return (0);
}

void mlx_hooks()
{
	t_core	*engine;
	engine = getengine();

	mlx_clear_window(engine->m.mlx, engine->m.win);
	mlx_put_image_to_window(engine->m.mlx, engine->m.win, engine->img.img, 0,
		0);
	mlx_hook(engine->m.win, 17, 0, close_window, engine);
	mlx_key_hook(engine->m.win, key_press, engine);
	mlx_loop(engine->m.mlx);
}


int	key_press(int key, t_core *engine)
{
	if (key == XK_Escape)
		close_window(engine);
	return (0);
}

void	init_hooks(t_core *engine)
{
	engine->m.ctrl_pressed = false;
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
