/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:44:59 by ysbai-jo          #+#    #+#             */
/*   Updated: 2025/04/13 21:40:57 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

long	ft_atoi(const char *str, bool *err)
{
	long (res), (prev);
	int (sign), (i);
	res = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			*err = true;
			return (0);
		}
		prev = res;
		res = res * 10 + (str[i++] - 48);
		if (res / 10 != prev)
			return (*err = true, 0);
	}
	return (res * sign);
}
