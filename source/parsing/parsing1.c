/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 09:54:30 by ysbai-jo          #+#    #+#             */
/*   Updated: 2025/04/13 22:12:00 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	setup_cam_dir(t_camera *cam)
{
	t_vec	temp_up;

	if (fabs(cam->forward.y) > 0.999 && fabs(cam->forward.x) < 0.001
		&& fabs(cam->forward.z) < 0.001)
		temp_up = (t_vec){0, 0, 1};
	else
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
	srand(time(NULL));
	readfile(fd, filename);
	setup_cam_dir(engine->w->cam);
	engine->w->gray_on = false;
	close(fd);
}
