#include "miniRT.h"

int key_press(int key, t_core *engine)
{
    if (key == XK_RIGHT_CTRL)
        engine->m.ctrl_pressed = true;
    if (key == XK_Right && engine->m.ctrl_pressed)
    {
        ((t_light *)engine->w->lights->data)->p.x -= 2;
        rendering();
    }
    if (key == XK_Left && engine->m.ctrl_pressed)
    {
        ((t_light *)engine->w->lights->data)->p.x += 2;
        rendering();
    }
    if (key == XK_Up && engine->m.ctrl_pressed)
    {
        ((t_light *)engine->w->lights->data)->p.y += 2;
        rendering();
    }
    if (key == XK_Down && engine->m.ctrl_pressed)
    {
        ((t_light *)engine->w->lights->data)->p.y -= 2;
        rendering();
    }
    if (key == XK_Escape)
    {
        clear();
        exit(0);
    }
    return (0);
}

int key_release(int keycode, t_core *engine)
{
    if (keycode == XK_RIGHT_CTRL)
    {
        engine->m.ctrl_pressed = false;
        printf("release\n");
    }
    return (0);
}

// Add this to initialization:
void init_hooks(t_core *engine)
{
    engine->m.ctrl_pressed = false;

}


// int input(int key, void *d)
// {
// 	t_core *engine;

// 	engine = getengine();
// 	// move first light
// 	if (key == XK_Right)
// 	{
// 		((t_light *)engine->w->lights->data)->p.x -= 2;
// 		rendering();
// 	}
// 	if (key == XK_Left)
// 	{
// 		((t_light *)engine->w->lights->data)->p.x += 2;
// 		rendering();
// 	}
// 	if (key == XK_Up)
// 	{
// 		((t_light *)engine->w->lights->data)->p.y += 2;
// 		rendering();
// 	}
// 	if (key == XK_Down)
// 	{
// 		((t_light *)engine->w->lights->data)->p.y -= 2;
// 		rendering();
// 	}
// 	if (key == XK_Escape)
// 	{
// 		clear();
// 		exit(0);
// 	}
	
// 	return 1;
// }