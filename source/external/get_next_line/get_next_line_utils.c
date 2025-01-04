/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:24:36 by ysbai-jo          #+#    #+#             */
/*   Updated: 2025/01/04 10:23:04 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	*ft_gstrjoin(char **s1, char const *s2, int rd)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new;

	if (!rd)
		return (*s1);
	if (!*s1)
		return (ft_substr(s2, 0, rd));
	s1_len = ft_strlen(*s1);
	s2_len = ft_strlen(s2);
	new = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!new)
		return (NULL);
	ft_memcpy(new, *s1, s1_len);
	ft_strlcpy(&new[s1_len], s2, s2_len + 1);
	free(*s1);
	return (new);
}

