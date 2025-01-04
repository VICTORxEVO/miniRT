/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:55:45 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/11/29 17:14:38 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ext_libs.h"
#include "gc.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_l;

	if (!s)
		return (NULL);
	s_l = ft_strlen(s);
	if (start >= s_l)
		return (galloc(sizeof(char)));
	if (start + len >= s_l)
	{
		sub = galloc(sizeof(char) * (s_l - start + 1));
		if (!sub)
			return (NULL);
		ft_strlcpy(sub, &s[start], (s_l - start + 1));
	}
	else
	{
		sub = galloc(sizeof(char) * (len + 1));
		if (!sub)
			return (NULL);
		ft_strlcpy(sub, &s[start], (len + 1));
	}
	return (sub);
}
