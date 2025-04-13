/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pexit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:44:29 by ysbai-jo          #+#    #+#             */
/*   Updated: 2025/04/13 21:02:44 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	pexit(char *msg, short int exit_code)
{
	t_core	*engine;

	engine = getengine();
	if (msg[ft_strlen(msg) - 1] == '!' || msg[ft_strlen(msg) - 1] == '>')
	{
		(ft_putstr_fd(msg, 2), ft_putstr_fd("\n", 2));
	}
	else
		perror(msg);
	ft_putstr_fd(END, 2);
	mlx_destroy_window(engine->m.mlx, engine->m.win);
	mlx_destroy_display(engine->m.mlx);
	free(engine->m.mlx);
	clear();
	exit(exit_code);
}
