#include "miniRT.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int mouse_input(int key, int y, int x, void *d)
{
    t_core  *engine;
    t_sphere    *s;
    engine = getengine();

    printf("x -> %d     y -> %d\n", x, y);
    s = galloc(sizeof(t_sphere));
    s->c = (t_color) {0,0,255};
    s->origin = (t_vec ) {x,y,5};
    s->diameter = 10;
    s->radius_squared = 25;
    add_obj(engine, &engine->w->objects, s, SP_OBJ);
    rendering();
    return 1;
}

int key_press(int key, t_core *engine)
{
    t_camera *cam = engine->w->cam;
    t_vec cam_dir = engine->w->cam->forward;
    t_vec cam_pos = engine->w->cam->origin;
    t_vec light_pos = ((t_light *)(engine->w->lights->data))->p;
    double **cam_pos_mx;
    double **cam_dir_mx;
    double **trans_mx;
    double **mul_res;

    if (key == XK_RIGHT_CTRL)
    {
        engine->m.ctrl_pressed = true;
        printf("Control pressed - ctrl_state: %d\n", engine->m.ctrl_pressed);
    }
    else if (key == XK_1)
    {  
        trans_mx = rotate_x(0.1);  // Changed from -1 to 1
        cam_dir_mx = get_4_1_matrix(cam_dir.x, cam_dir.y, cam_dir.z, 1);
        mul_res = mul_matrix_row_col(trans_mx, cam_dir_mx, 4, 1);
        engine->w->cam->forward = translate_mx_to_vector(mul_res);
        setup_cam_dir(cam);
        rendering();
    }
    else if (key == XK_2)
    {  
        trans_mx = rotate_x(-0.1);  // Changed from -1 to 1
        cam_dir_mx = get_4_1_matrix(cam_dir.x, cam_dir.y, cam_dir.z, 1);
        mul_res = mul_matrix_row_col(trans_mx, cam_dir_mx, 4, 1);
        engine->w->cam->forward = translate_mx_to_vector(mul_res);
        setup_cam_dir(cam);
        rendering();
    }
    else if (key == XK_3)
    {  
        trans_mx = rotate_y(0.1);  // Changed from -1 to 1
        cam_dir_mx = get_4_1_matrix(cam_dir.x, cam_dir.y, cam_dir.z, 1);
        mul_res = mul_matrix_row_col(trans_mx, cam_dir_mx, 4, 1);
        engine->w->cam->forward = translate_mx_to_vector(mul_res);
        setup_cam_dir(cam);
        rendering();
    }
    else if (key == XK_4)
    {  
        trans_mx = rotate_y(-0.1);  // Changed from -1 to 1
        cam_dir_mx = get_4_1_matrix(cam_dir.x, cam_dir.y, cam_dir.z, 1);
        mul_res = mul_matrix_row_col(trans_mx, cam_dir_mx, 4, 1);
        engine->w->cam->forward = translate_mx_to_vector(mul_res);
        setup_cam_dir(cam);
        rendering();
    }
    else if (key == XK_5)
    {  
        trans_mx = rotate_z(0.1);  // Changed from -1 to 1
        cam_dir_mx = get_4_1_matrix(cam_dir.x, cam_dir.y, cam_dir.z, 1);
        mul_res = mul_matrix_row_col(trans_mx, cam_dir_mx, 4, 1);
        engine->w->cam->forward = translate_mx_to_vector(mul_res);
        setup_cam_dir(cam);
        rendering();
    }
    else if (key == XK_6)
    {  
        trans_mx = rotate_z(-0.1);  // Changed from -1 to 1
        cam_dir_mx = get_4_1_matrix(cam_dir.x, cam_dir.y, cam_dir.z, 1);
        mul_res = mul_matrix_row_col(trans_mx, cam_dir_mx, 4, 1);
        engine->w->cam->forward = translate_mx_to_vector(mul_res);
        setup_cam_dir(cam);
        rendering();
    }
    else if (key == XK_q)
    {
        trans_mx = get_translation_matrix(0,0,1);
        cam_pos_mx = get_4_1_matrix(cam_pos.x, cam_pos.y, cam_pos.z, 1);
        mul_res = mul_matrix_row_col( trans_mx, cam_pos_mx, 4, 1);
        engine->w->cam->origin = translate_mx_to_point(mul_res);
        rendering();
    }
    else if (key == XK_e)
    {
        trans_mx = get_translation_matrix(0,0,-1);
        cam_pos_mx = get_4_1_matrix(cam_pos.x, cam_pos.y, cam_pos.z, 1);
        mul_res = mul_matrix_row_col( trans_mx, cam_pos_mx, 4, 1);
        engine->w->cam->origin = translate_mx_to_point(mul_res);
        rendering();
    }
    else if (key == XK_w)
    {
        trans_mx = get_translation_matrix(0,1.f,0);
        cam_pos_mx = get_4_1_matrix(cam_pos.x, cam_pos.y, cam_pos.z, 1);
        mul_res = mul_matrix_row_col( trans_mx, cam_pos_mx, 4, 1);
        engine->w->cam->origin = translate_mx_to_point(mul_res);
        rendering();
    }
    else if (key == XK_s)
    {
        trans_mx = get_translation_matrix(0.f,-1.f,0.0f);
        cam_pos_mx = get_4_1_matrix(cam_pos.x, cam_pos.y, cam_pos.z, 1);
        mul_res = mul_matrix_row_col( trans_mx, cam_pos_mx, 4, 1);
        engine->w->cam->origin = translate_mx_to_point(mul_res);
        rendering();
    }
    else if (key == XK_d)
    {
        trans_mx = get_translation_matrix(-1,0,0);
        cam_pos_mx = get_4_1_matrix(cam_pos.x, cam_pos.y, cam_pos.z, 1);
        mul_res = mul_matrix_row_col( trans_mx, cam_pos_mx, 4, 1);
        engine->w->cam->origin = translate_mx_to_point(mul_res);
        rendering();
    }
    else if (key == XK_a)
    {
        trans_mx = get_translation_matrix(1,0,0);
        cam_pos_mx = get_4_1_matrix(cam_pos.x, cam_pos.y, cam_pos.z, 1);
        mul_res = mul_matrix_row_col( trans_mx, cam_pos_mx, 4, 1);
        engine->w->cam->origin = translate_mx_to_point(mul_res);
        rendering();
    }
    else if (key == XK_Up)
    {
        trans_mx = get_translation_matrix(0,1,0);
        cam_pos_mx = get_4_1_matrix(light_pos.x, light_pos.y, light_pos.z, 1);
        mul_res = mul_matrix_row_col( trans_mx, cam_pos_mx, 4, 1);
        ((t_light *)(engine->w->lights->data))->p = translate_mx_to_point(mul_res);
        rendering();
    }
    else if (key == XK_Down)
    {
        trans_mx = get_translation_matrix(0,-1,0);
        cam_pos_mx = get_4_1_matrix(light_pos.x, light_pos.y, light_pos.z, 1);
        mul_res = mul_matrix_row_col( trans_mx, cam_pos_mx, 4, 1);
        ((t_light *)(engine->w->lights->data))->p = translate_mx_to_point(mul_res);
        rendering();
    }
    else if (key == XK_Left)
    {
        trans_mx = get_translation_matrix(1,0,0);
        cam_pos_mx = get_4_1_matrix(light_pos.x, light_pos.y, light_pos.z, 1);
        mul_res = mul_matrix_row_col( trans_mx, cam_pos_mx, 4, 1);
        ((t_light *)(engine->w->lights->data))->p = translate_mx_to_point(mul_res);
        rendering();
    }
    else if (key == XK_Right)
    {
        trans_mx = get_translation_matrix(-1,0,0);
        cam_pos_mx = get_4_1_matrix(light_pos.x, light_pos.y, light_pos.z, 1);
        mul_res = mul_matrix_row_col( trans_mx, cam_pos_mx, 4, 1);
        ((t_light *)(engine->w->lights->data))->p = translate_mx_to_point(mul_res);
        rendering();
    }
    else if (key == XK_z)
    {
        (engine->w->ambient->ratio) -= 0.1;
        rendering();
    }
    else if (key == XK_x)
    {
        (engine->w->ambient->ratio) += 0.1;
        rendering();
    }
    else if (key == XK_c)
    {
        ((t_light *)(engine->w->lights)->data)->brightness -= 0.05;
        rendering();
    }
    else if (key == XK_v)
    {
        ((t_light *)(engine->w->lights)->data)->brightness += 0.05;
        rendering();
    }
    else if (key == XK_b)
    {
        ((t_light *)(engine->w->lights)->data)->c = increment_color(((t_light *)(engine->w->lights)->data)->c, -10);
        rendering();
    }
    else if (key == XK_n)
    {
        ((t_light *)(engine->w->lights)->data)->c = increment_color(((t_light *)(engine->w->lights)->data)->c, 10);
        rendering();
    }
    else if (key == XK_space)
    {
        engine->w->gray_on = !engine->w->gray_on;
        rendering();
    }
    else if (key == XK_Shift_L || key == XK_Shift_R)
    {
        if (engine->aa_on)
        {
            engine->aa_on = false;
            engine->rays_px = 1;
        }
        else
        {
            engine->aa_on = true;
            engine->rays_px = 20;
        }
        rendering();
    }
    else if (key == XK_l)
    {
        engine->rays_px+=10;
        rendering();
    }
    else if (key == XK_k)
    {
        if (engine->rays_px > 1)
            engine->rays_px -= 1;
        rendering();
    }
    else if (key == XK_KP_Add && engine->iter > 1)
    {
        engine->iter--;
        rendering();
    }
    else if (key == XK_KP_Subtract)
    {
        engine->iter++;
        rendering();
    }
    else if (key == XK_Escape)
    {
        clear();
        exit(0);
    }
    if (key == XK_Return) // Enter key
    {
        // Loop through spheres and planes and set pattern to NULL
        t_object *obj = engine->w->objects;
        while (obj)
        {
            if (obj->type == SP_OBJ || obj->type == PL_OBJ)
            {
                if (!obj->get_pattern)
                    obj->get_pattern = get_obj_pattern;
                else
                    obj->get_pattern = NULL;
            }
            obj = obj->next;
        }
        rendering(); // Re-render the scene
    }
    if (key == XK_p)
    {
        // save_img()
        char *name = ft_strjoin("scenes/scene", ft_itoa(engine->counter));
        engine->counter++;
        name = ft_strjoin(name, ".png");
        stbi_write_png(name, SCREEN_WIDTH, SCREEN_HEIGHT, 3, engine->png, SCREEN_WIDTH * 3);
    }
    if (key == XK_r)
    {
        // save_img()
        if (engine->refl_on)
        {
            engine->refl_on = false;
            engine->rays_px = 1;
            engine->aa_on = false;
        }
        else
        {
            engine->refl_on = true;
            engine->rays_px = 20;
            engine->aa_on = true;
        }
        rendering(); // Re-render the scene
    }
    if (key == XK_j)
    {
        // save_img()
        engine->bump++;
        rendering(); // Re-render the scene
    }
    if (key == XK_h)
    {
        // save_img()
        engine->bump--;
        rendering(); // Re-render the scene
    }
    return 0;
    return 0;
}

int key_release(int key, t_core *engine)
{
    if (key == XK_RIGHT_CTRL)
    {
        engine->m.ctrl_pressed = false;
    }
    return (0);
}

void init_hooks(t_core *engine)
{
    engine->m.ctrl_pressed = false;
}


void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
