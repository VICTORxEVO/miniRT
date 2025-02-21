# include "miniRT.h"

void save_to_img(t_color px_color, int x, int y)
{
    t_core      *engine;

	engine = getengine();
	int index = (y * SCREEN_WIDTH + x) * 3;
	engine->png[index] = px_color.r;
	engine->png[index + 1] = px_color.g;
	engine->png[index + 2] = px_color.b;
}