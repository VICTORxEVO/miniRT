#include "miniRT.h"

inline t_color zero_color()
{
	t_color zero;

	zero.r = 0;
	zero.g = 0;
	zero.b = 0;

	return zero;
}

inline t_color rgb_scl(t_color v, double scale)
{
    t_color scaled;

    scaled.r = v.r * scale;
    scaled.g = v.g * scale;
    scaled.b = v.b * scale;

    return scaled;
}

inline t_color sclamp_color(t_color v, double scale)
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

inline t_color rgb_sum(t_color amb, t_color dif, t_color   spc)
{
    t_color res;
    res.r = amb.r + dif.r + spc.r;
    res.g = amb.g + dif.g + spc.g;
    res.b = amb.b + dif.b + spc.b;
    // clamp_color(res);
    return res;
}

inline double get_brightness(t_color c)
{
    return sqrtf( powf(0.299*c.r, 2.f) + powf(0.587*c.g, 2.f) + powf(0.114*c.b, 2.f) );
}