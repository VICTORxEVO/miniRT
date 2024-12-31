#ifndef miniRT_H
#define miniRT_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <unistd.h>
#include "../mlx/mlx.h"
#include <X11/keysym.h>
#include "math_lib.h"

typedef struct s_node {
    void *data;
    struct s_node *next;
} t_node;

typedef struct s_mlx
{
	void *mlx;
	void *win;
}  t_mlx;

enum e_types
{
	e_ambient = 3,
	e_camera = 4,
	e_color = 4,
	e_light = 4,
	e_sphere = 4,
	e_plain = 4,
	e_cylinder = 6,
};

typedef struct s_camera
{
	t_ray camera;
	float hsize; // horizontal size in pixels of the canvas
	float vsize; // vertical size in pixels of the canvas
	float half_width; // in units
	float half_height; // in units
	float pixel_size;
	float fov; // field of view angle (how much of the cam we can see) when fov is small view is zoomed in
	float aspect; // 
	float half_view; // 
	float focal_len; // 
} t_camera;

typedef struct s_world
{
	// t_node *lights;
	t_node *spheres;
	unsigned char ambient;
	t_camera cam;
} t_world;

typedef struct s_data
{
	t_mlx m;
	t_world *w;
} t_data;

typedef struct s_sphere
{
	t_point origin;
	float radius;
} t_sphere;

typedef struct s_pars
{
	bool	camera_exist;
	bool	ambient_exist;
	bool	light_exist; // in bonus accept more than one
} t_pars;



/*
	parsing
*/
int	we_have_a_problem(int fd, char **str);
char	*get_next_line(int fd);
size_t	ft_strlen(char *s);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *str, char *buff);
char	*ft_get_line(char *str);
char	*get_rest(char *str);
char	**ft_split(char const *s, char c);
int	ft_strcmp(const char *s1, const char *s2);
unsigned count_args(char   **args);
int	ft_atoi(const char *s);







#endif
