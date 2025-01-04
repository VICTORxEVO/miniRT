/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:55:33 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/10/10 21:00:51 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ext_libs.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	l_len;
	size_t	q;

	if (*little == 0)
		return ((char *)big);
	l_len = ft_strlen(little);
	q = 0;
	while (q < len && big[q])
	{
		if (len - q >= l_len && !(ft_strncmp(&big[q], little, l_len)))
			return ((char *)&big[q]);
		++q;
	}
	return (NULL);
}
