#include "miniRT.h"


t_color get_clr_struct(int color)
{
    t_color result;
    
    // The exact order depends on your MLX's endianness
    // This assumes ARGB format (typical for MLX)
    result.r = (color >> 16) & 0xFF;
    result.g = (color >> 8) & 0xFF;
    result.b = color & 0xFF;

    return result;
}

int get_clr_int(t_color color)
{
    // Bitwise shift each component to its position and combine with OR
    return (color.r << 16) | (color.g << 8) | color.b;
}

inline t_color rgb_add(t_color c1, t_color c2, bool is_clampt)
{
    t_color res_color;

    res_color.r = c1.r + c2.r;
    res_color.g = c1.g + c2.g;
    res_color.b = c1.b + c2.b;
    if (is_clampt)
        return clamp_color(res_color);
    return res_color;
}

inline t_color increment_color(t_color c1, int amount)
{
    t_color res_color;

    res_color.r = c1.r + amount;
    res_color.g = c1.g + amount;
    res_color.b = c1.b + amount;
    return clamp_color(res_color);
}

inline t_color clamp_color(t_color c1)
{
    t_color res_color;
    if (c1.r > 255)
        c1.r = 255;
    if (c1.r < 0)
        c1.r = 0;

    if (c1.g > 255)
        c1.g = 255;
    if (c1.g < 0)
        c1.g = 0;

    if (c1.b > 255)
        c1.b = 255;
    if (c1.b < 0)
        c1.b = 0;
    res_color.r = c1.r;
	res_color.g = c1.g;
	res_color.b = c1.b;
    return res_color;
}

inline t_color sub_colors(t_color c1, t_color c2)
{
    t_color res_color;

    res_color.r = c1.r - c2.r;
    res_color.g = c1.g - c2.g;
    res_color.b = c1.b - c2.b;
    return clamp_color(res_color);
}

inline t_color rgb_mul(t_color c1, t_color c2)
{
    t_color res_color;

    res_color.r = c1.r * c2.r / 255;
    res_color.g = c1.g * c2.g / 255;
    res_color.b = c1.b * c2.b / 255;
    return clamp_color(res_color);
}

inline t_color rgb_mad(t_color c1, t_color c2)
{
    t_color res_color;

    if (c1.r == 0 || c2.r == 0)
        res_color.r = (c1.r + c2.r) / 2;
    else
        res_color.r = c1.r * c2.r / 255;
    if (c1.g == 0 || c2.g == 0)
        res_color.g = (c1.g + c2.g) / 2;
    else
        res_color.g = c1.g * c2.g / 255;
    if (c1.b == 0 || c2.b == 0)
        res_color.b = (c1.b + c2.b) / 2;
    else
        res_color.b = c1.b * c2.b / 255;
    return clamp_color(res_color);
}


inline t_color abs_sub_colors(t_color c1, t_color c2)
{
    t_color res_color;

    res_color.r = abs(c1.r - c2.r);
    res_color.g = abs(c1.g - c2.g);
    res_color.b = abs(c1.b - c2.b);
    return clamp_color(res_color);
}

inline t_color rgb_to_gray(t_color c) {
    int gray = (0.299 * c.r + 0.587 * c.g + 0.114 * c.b);
    return ((t_color) {gray, gray, gray});
}