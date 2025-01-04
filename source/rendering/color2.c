#include "miniRT.h"

inline t_color neg_color(t_color c1)
{
    t_color neg;

    neg.r = 0 - c1.r;
    neg.g = 0 - c1.g;
    neg.b = 0 - c1.b;
    return neg;
}

inline t_color zero_color()
{
	t_color zero;

	zero.r = 0;
	zero.g = 0;
	zero.b = 0;

	return zero;
}

inline t_color scale_color(t_color v, float scale)
{
    t_color scaled;

    scaled.r = v.r * scale;
    scaled.g = v.g * scale;
    scaled.b = v.b * scale;
    return scaled;
}

void print_color(t_color c, bool newline)
{
    printf("{%u, %u, %u}      ", c.r, c.g, c.b);
	if (newline)
		printf("\n");
}
