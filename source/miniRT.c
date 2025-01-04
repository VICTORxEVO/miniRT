#include "miniRT.h"

int main(int ac, char **av)
{
    getengine();
    parsing(ac, av[1]);
    rendering();
    clear();
    return 0;
}
