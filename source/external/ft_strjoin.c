/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:55:29 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/12/11 12:19:38 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ext_libs.h"
#include "gc.h"

char	*ft_strjoin_m(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!new)
		return (NULL);
	ft_memcpy(new, s1, s1_len);
	ft_strlcpy(&new[s1_len], s2, s2_len + 1);
	return (new);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new = galloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!new)
		return (NULL);
	ft_memcpy(new, s1, s1_len);
	ft_strlcpy(&new[s1_len], s2, s2_len + 1);
	return (new);
}
