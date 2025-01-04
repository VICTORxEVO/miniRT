/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:44:25 by ysbai-jo          #+#    #+#             */
/*   Updated: 2025/01/03 12:44:20 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free2d(void **array)
{
	int	i;

	i = -1;
	while (array && array[++i])
		free(array[i]);
	free(array);
}

void	clear_1data(void *data)
{
	t_gc	*list;

	list = getcore()->gc;
	while (list)
	{
		if (list->data == data)
		{
			safe_free((void **)&list->data);
			return ;
		}
		list = list->next;
	}
	return (pexit(PTR_ERR, 101, EXIT));
}

static void	clear_t_vat(t_var *list)
{
	t_var	*tmp;

	while (list)
	{
		tmp = list->next;
		clear_1data(list);
		list = tmp;
	}
	getcore()->var_list = NULL;
}

void	clear_1list(void *list, char *list_type)
{
	if (!ft_strncmp(list_type, "t_var", -1))
		clear_t_vat((t_var *)list);
}
