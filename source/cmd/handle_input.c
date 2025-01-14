#include "miniRT.h"

void handle_input()
{
    t_core *engine;
    char    *line;
    t_sphere *s;

    engine = getengine();
    if (!engine->cmd_on)
        return;
    line = get_next_line(0);
    if (!line || !line[0])
    {
        engine->cmd_on = true;
        return ;
    }
    if (ft_strcmp(line, "s\n") == 0 || ft_strcmp(line, "s") == 0)
    {
        s = galloc(sizeof(t_sphere));
        s->c = (t_color) {255,255,255};
        s->origin = (t_point ) {0,0,0};
        s->diameter = 2;
        s->radius_squared = 4;
        add_obj(engine, &engine->w->objects, s, SP_OBJ);
    }
}