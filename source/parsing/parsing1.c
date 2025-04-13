/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 09:54:30 by ysbai-jo          #+#    #+#             */
/*   Updated: 2025/04/13 18:53:01 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// calc up, right vectors for where the cam is lookin (forward)
void	setup_cam_dir(t_camera *cam)
{
	t_vec	temp_up;

	temp_up = (t_vec){0, 1, 0};
	cam->right = normal(cross(temp_up, cam->forward));
	cam->up = normal(cross(cam->forward, cam->right));
	cam->aspect = (SCREEN_WIDTH / SCREEN_HEIGHT);
}

bool	ends_with(char *small, char *big)
{
	int	i;
	int	j;

	i = strlen(small) - 1;
	j = strlen(big) - 1;
	if (j < i)
		return (false);
	while (i > 0)
	{
		if (small[i] != big[j])
			return (false);
		i--;
		j--;
	}
	return (i == 0);
}

void	parsing(int ac, char *filename)
{
	int		fd;
	t_core	*engine;

	engine = getengine();
	engine->w = galloc(sizeof(t_world));
	engine->m.mlx = mlx_init();
	if (!engine->m.mlx)
		(clear(), exit(1));
	engine->m.win = mlx_new_window(engine->m.mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"miniRT");
	if (!engine->m.win)
		(clear(), exit(1));
	engine->m.ctrl_pressed = false;
	if (ac != 2)
		pexit(YELLOW USAGE_WARN, 1);
	fd = check_file(filename);
	if (fd < 0)
		pexit(filename, 2);
	readfile(fd, filename);
	setup_cam_dir(engine->w->cam);
	engine->w->gray_on = false;
	engine->rays_px = 1;
	engine->aa_on = true;
	engine->iter = 1;
	close(fd);
}
