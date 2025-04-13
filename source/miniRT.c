/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:27:49 by sgouzi            #+#    #+#             */
/*   Updated: 2025/04/13 22:18:58 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_core	*getengine(void)
{
	static t_core	engine;

	return (&engine);
}

void	rendering(void)
{
	t_core	*engine;
	int		x;
	int		y;
	t_color	px_color;

	engine = getengine();
	engine->img.img = mlx_new_image(engine->m.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	engine->img.addr = mlx_get_data_addr(engine->img.img,
			&engine->img.bits_per_pixel, &engine->img.line_length,
			&engine->img.endian);
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			px_color = get_px_color(x, y);
			my_mlx_pixel_put(&engine->img, x, y, get_clr_int(px_color));
			x += 1;
		}
		y += 1;
	}
	mlx_hooks();
	return ;
}

int	main(int ac, char **av)
{
	getengine();
	parsing(ac, av[1]);
	rendering();
	clear();
	return (0);
}
