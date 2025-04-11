/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_convert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:28:12 by sgouzi            #+#    #+#             */
/*   Updated: 2025/04/11 19:00:16 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	between(double n, double min, double max)
{
	return (n >= min && n <= max);
}

int	ft_atof_helper1(const char **s, bool *err, double *dot_pow)
{
	if (**s != '.' && (**s < '0' || **s > '9'))
	{
		*err = true;
		return (0);
	}
	if (**s == '.')
	{
		if ((*dot_pow)++ != 0)
		{
			*err = true;
			return (0);
		}
		(*dot_pow)++;
		(*s)++;
		return (1);
	}
	return (2);
}

void	ft_atof_helper2(const char **s, double *res, double *dot_pow)
{
	if (*dot_pow)
	{
		*res = *res + ((**s) - '0') / powf(10.f, *dot_pow);
		(*dot_pow)++;
	}
	else
		*res = (*res * 10) + ((**s) - '0');
	(*s)++;
}

double	ft_atof(const char *s, bool *err)
{
	double res;
	int sign;
	int flag;
	double dot_pow;

	dot_pow = 0;
	res = 0;
	sign = 1;
	if (*s == '-')
	{
		sign *= -1;
		s++;
	}
	while (*s)
	{
		flag = ft_atof_helper1(&s, err, &dot_pow);
		if (flag == 1)
			continue ;
		else if (flag == 0)
			return (0);
		ft_atof_helper2(&s, &res, &dot_pow);
	}
	return (res * sign);
};

unsigned	count_args(char **args)
{
	unsigned i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}