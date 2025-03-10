#include "miniRT.h"


double maxf(double a, double b)
{
    if (a > b)
        return (a);
    return (b);
}

double minf(double a, double b)
{
    if (a < b)
        return (a);
    return (b);
}

int maxi(int a, int b)
{
    if (a > b)
        return (a);
    return (b);
}

int mini(int a, int b)
{
    if (a > b)
        return (a);
    return (b);
}

int clampi(int val, int min, int max)
{
    if (val > max)
        val = max;
    else if (val < min)
        val = min;
    return val;
}