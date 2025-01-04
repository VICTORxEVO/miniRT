#include "miniRT.h"

int main(int ac, char **av)
{
    parsing(ac, av[1]);
    rendering();
    clear();
    return 0;
}
