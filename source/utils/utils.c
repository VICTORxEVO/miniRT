#include "miniRT.h"

t_core  *getengine(void)
{
    static t_core engine;

    return (&engine);
}