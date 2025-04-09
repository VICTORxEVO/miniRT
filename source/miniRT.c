#include "miniRT.h"

t_core	*getengine(void)
{
	static t_core	engine;

	return (&engine);
}

int	main(int ac, char **av)
{
	getengine();
	parsing(ac, av[1]);
	rendering();
	clear();
	return (0);
}
