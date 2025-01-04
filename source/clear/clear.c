/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:44:22 by ysbai-jo          #+#    #+#             */
/*   Updated: 2025/01/04 18:43:00 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	safe_free(void **data)
{
	if (*data)
	{
		free(*data);
		*data = NULL;
	}
}

static void	gc_lstclear(void)
{
	t_core	*engine;
	t_gc	*tmp;

	engine = getengine();
	if (!engine->gc)
		return ;
	while (engine->gc)
	{
		tmp = engine->gc->next;
		safe_free((void **)&engine->gc->data);
		safe_free((void **)&engine->gc);
		engine->gc = tmp;
	}
}

void	clear(void)
{
	return ;
	gc_lstclear();
}
