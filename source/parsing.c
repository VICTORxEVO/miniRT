#include "miniRT.h"

bool s_is_whitespace(char	*s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!((s[i] >= 9 && s[i] <= 13) || s[i] == 32))
			return (false);
		i++;
	}
	return (true);
}

bool between(float n, float min, float max)
{
	return (n >= min && n <= max);
}

float	ft_atof(const char *s, bool *err)
{
	float	res;
	int		sign;
	float	dot_pow;
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
		if (*s != '.' && (*s < '0' || *s > '9'))
		{
			*err = true;
			return 0;
		}
		if (*s == '.')
		{
			if (dot_pow != 0)
			{
				*err = true;
				return 0;
			}
			dot_pow++;
			s++;
			continue;
		}
		if (dot_pow)
		{
			res = res + (*s - '0') / powf(10.f, dot_pow);
			dot_pow++;
		}
		else
			res = (res * 10) + (*s - '0');
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
    while (args[i])
        i++;
    return i;
}