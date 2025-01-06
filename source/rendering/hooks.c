#include "miniRT.h"

int input(int key, void *d)
{
	t_core *engine;

	engine = getengine();
	// move first light
	if (key == XK_Right)
	{
		((t_light *)engine->w->lights->data)->p.x -= 2;
		rendering();
	}
	if (key == XK_Left)
	{
		((t_light *)engine->w->lights->data)->p.x += 2;
		rendering();
	}
	if (key == XK_Up)
	{
		((t_light *)engine->w->lights->data)->p.y += 2;
		rendering();
	}
	if (key == XK_Down)
	{
		((t_light *)engine->w->lights->data)->p.y -= 2;
		rendering();
	}
	if (key == XK_Escape)
	{
		clear();
		exit(0);
	}
	
	return 1;
}
