/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:44:22 by ysbai-jo          #+#    #+#             */
/*   Updated: 2025/01/03 12:44:23 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	re_zero(void)
{
	t_all	*core;
	void	*data;
	void	**data2d[2];
	int		value[1];

	core = getcore();
	value[0] = core->exit_code;
	data = (void *)core->env_list;
	data2d[0] = (void **)core->path;
	data2d[1] = (void **)core->env;
	ft_bzero(getcore(), sizeof(t_all));
	core->exit_code = value[0];
	core->env_list = (t_env *)data;
	core->path = (char **)data2d[0];
	core->env = (char **)data2d[1];
}

void	safe_free(void **data)
{
	if (*data)
	{
		free(*data);
		*data = NULL;
	}
}

static void	env_lstclear(void)
{
	t_env	*env_list;
	t_env	*tmp;

	env_list = getcore()->env_list;
	while (env_list)
	{
		tmp = env_list->next;
		safe_free((void **)&env_list->key);
		safe_free((void **)&env_list->value);
		safe_free((void **)&env_list);
		env_list = tmp;
	}
}

static void	gc_lstclear(void)
{
	t_all	*core;
	t_gc	*tmp;

	core = getcore();
	if (!core->gc)
		return ;
	while (core->gc)
	{
		tmp = core->gc->next;
		safe_free((void **)&core->gc->data);
		safe_free((void **)&core->gc);
		core->gc = tmp;
	}
	core->gc = NULL;
}

void	clear(char flag)
{
	gc_lstclear();
	re_zero();
	if (flag == FREE_ALL)
	{
		env_lstclear();
		free2d((void **)getcore()->path);
		free2d((void **)getcore()->env);
	}
}
