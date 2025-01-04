#include "miniRT.h"

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

    return clamp_color(scaled);
}

void print_color(t_color c, bool newline)
{
    printf("{%u, %u, %u}      ", c.r, c.g, c.b);
	if (newline)
		printf("\n");
}

inline t_color sum_colors(t_color amb, t_color dif, t_color   spc)
{
    t_color res;
    res.r = amb.r + dif.r + spc.r;
    res.g = amb.g + dif.g + spc.g;
    res.b = amb.b + dif.b + spc.b;
    clamp_color(res);
    return res;
}

