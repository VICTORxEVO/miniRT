/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:44:25 by ysbai-jo          #+#    #+#             */
/*   Updated: 2025/01/04 10:36:44 by ysbai-jo         ###   ########.fr       */
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

	list = getengine()->gc;
	while (list)
	{
		if (list->data == data)
		{
			safe_free((void **)&list->data);
			return ;
		}
		list = list->next;
	}
	return (pexit(PTR_CLEAR_ERR, 101));
}

void	clear_1list(void *list, char *list_type)
{
	return ;
}
