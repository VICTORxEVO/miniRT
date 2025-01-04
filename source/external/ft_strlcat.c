/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:29:05 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/10/10 21:00:51 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ext_libs.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_l;
	size_t	dest_l;

	src_l = ft_strlen(src);
	if (!dest && !size)
		return (src_l);
	dest_l = ft_strlen(dest);
	i = 0;
	if (dest_l >= size)
		return (size + src_l);
	while (src[i] && dest_l + i < size - 1)
	{
		dest[dest_l + i] = src[i];
		i++;
	}
	dest[dest_l + i] = 0;
	return (dest_l + src_l);
}
