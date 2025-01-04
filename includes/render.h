#ifndef DRAW_H
#define DRAW_H

#include "miniRT.h"

typedef struct s_camera t_camera;
typedef struct s_data t_data;
typedef struct s_mlx t_mlx;
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}   t_img;


typedef struct s_mlx
{
    void    *con;
    void    *win;
}   t_mlx;

void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void print_cam(t_camera *cam);
bool    rendered(t_data *d, t_img	*img);
bool initialized(t_data *d, t_img	*img);
#endif