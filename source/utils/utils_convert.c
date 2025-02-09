#include "miniRT.h"

bool between(double n, double min, double max)
{
	return (n >= min && n <= max);
}

inline	void swapf(double *t1, double *t2)
{
	double temp;

	temp = *t1;
	*t1 = *t2;
	*t2 = temp;

}

double	ft_atof(const char *s, bool *err)
{
	double	res;
	int		sign;
	double	dot_pow;
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