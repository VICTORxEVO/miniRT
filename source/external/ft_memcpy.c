/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:49:00 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/10/10 21:00:51 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ext_libs.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	b;

	if (!dest && !src)
		return (NULL);
	b = 0;
	while (b < n && dest != src)
	{
		*((t_uc *)(dest + b)) = *((const t_uc *)(src + b));
		++b;
	}
	return (dest);
}
