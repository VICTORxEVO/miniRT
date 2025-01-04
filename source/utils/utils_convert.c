#include "miniRT.h"

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

unsigned count_args(char   **args)
{
    unsigned i;

    i = 0;
    while (args[i])
        i++;
    return i;
}