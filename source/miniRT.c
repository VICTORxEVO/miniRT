/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:27:49 by sgouzi            #+#    #+#             */
/*   Updated: 2025/04/11 18:27:50 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_core	*getengine(void)
{
	static t_core	engine;

	return (&engine);
}

int	main(int ac, char **av)
{
	getengine();
	parsing(ac, av[1]);
	rendering();
	clear();
	return (0);
}
