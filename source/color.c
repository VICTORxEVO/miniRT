#include "miniRT.h"

int get_color_value(t_color c)
{
    // Ensure values are clamped between 0 and 1
    float r = fmaxf(0.0f, fminf(1.0f, c.r));
    float g = fmaxf(0.0f, fminf(1.0f, c.g));
    float b = fmaxf(0.0f, fminf(1.0f, c.b));

    // Convert to 8-bit integer values (0-255 range)
    int r_int = (int)(r * 255.0f);
    int g_int = (int)(g * 255.0f);
    int b_int = (int)(b * 255.0f);

    // Combine into a single integer using bit shifting
    // Typical MLX pixel format is 0xAARRGGBB (Alpha, Red, Green, Blue)
    // We'll use 0xFF (full opacity) for the alpha channel
    return (0xFF << 24 | r_int << 16 | g_int << 8 | b_int);
}

inline t_color add_colors(t_color c1, t_color c2)
{
    t_color res_color;

    res_color.r = c1.r + c2.r;
    res_color.g = c1.g + c2.g;
    res_color.b = c1.b + c2.b;

    return res_color;
}

inline t_color clamp_color(t_color c1)
{
    t_color res_color;
	res_color.r = c1.r > 1 ? 1 : c1.r;
	res_color.g = c1.g > 1 ? 1 : c1.g;
	res_color.b = c1.b > 1 ? 1 : c1.b;


    return res_color;
}

inline t_color sub_colors(t_color c1, t_color c2)
{
    t_color res_color;

    res_color.r = c1.r - c2.r;
    res_color.g = c1.g - c2.g;
    res_color.b = c1.b - c2.b;
    return res_color;
}

inline t_color mul_colors(t_color c1, t_color c2)
{
    t_color res_color;

    res_color.r = c1.r * c2.r;
    res_color.g = c1.g * c2.g;
    res_color.b = c1.b * c2.b;
    return res_color;
}

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
