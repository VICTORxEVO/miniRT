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
