#include "miniRT.h"

int	ft_atoi(const char *s)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while (((*s <= 13 && *s >= 9) || *s == 32))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign *= -1;
		s += 1;
	}
	while (*s >= '0' && *s <= '9')
	{
		res = res * 10 + (*s - '0');
		s++;
	}
	return (res * sign);
};

int	ft_atou(const char *s)
{
	unsigned	res;
	int		sign;

	res = 0;
	sign = 1;
	while (((*s <= 13 && *s >= 9) || *s == 32))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign *= -1;
		s += 1;
	}
	while (*s >= '0' && *s <= '9')
	{
		res = res * 10 + (*s - '0');
		s++;
	}
	return (res * sign);
};

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (-1);
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}

unsigned count_args(char   **args)
{
    unsigned i;

    i = 0;
    while (args[i++])
        ;
    return i;
}