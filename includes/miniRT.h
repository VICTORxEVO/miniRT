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

typedef struct s_node
{
    void *data;
    struct s_node *next;
} t_node;

typedef struct s_gc
{
	void				*ptr;
	struct s_gc			*next;
}						t_gc;

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

typedef struct s_color
{
	unsigned	r;
	unsigned	g;
	unsigned	b;
}	t_color;

typedef struct s_ambient
{
	t_color		c;
	unsigned	ratio;
}	t_ambient;


typedef struct s_light
{
	t_point	p;
	float	brightness; // 0 -> 1
	t_color	c;
}	t_light;

typedef struct s_camera
{
	t_ray cam_ray;
	float hsize; // horizontal size in pixels of the canvas
	float vsize; // vertical size in pixels of the canvas
	float half_width; // in units
	float half_height; // in units
	float pixel_size;
	unsigned  fov; // field of view angle (how much of the cam we can see) when fov is small view is zoomed in
	float aspect; // 
	float half_view; // 
	float focal_len; // 
} t_camera;

typedef struct s_world
{
	t_node 	*lights;
	t_node 	*planes;
	t_node 	*cylinders;
	t_node 	*spheres;
	t_ambient	ambient;
	t_camera cam;
} t_world;

typedef struct s_data
{
	t_mlx m;
	t_world *w;
	t_gc	*gc;
} t_data;

typedef struct s_sphere
{
	t_point		origin;
	float		diameter;
	t_color		c;
} t_sphere;

typedef struct s_plane
{
	t_point		origin;
	t_vector	normal;
	t_color		c;
} t_plane;

typedef struct s_cylinder
{
	t_point		origin;
	t_vector	normal;
	float		diameter;
	float		height;
	t_color		c;
} t_cylinder;


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
char	*get_next_line(t_data *d, int fd);

size_t	ft_strlen(char *s);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(t_data *d, char *str, char *buff);
char	*ft_get_line(t_data *d, char *str);
char	*get_rest(t_data *d, char *str);

/*
	ft_split.c
*/
char	*ft_strdup(t_data *d, char *s1);
char	*ft_substr(t_data *d, char *s, unsigned int start, size_t len_);
int	count_words(char const *s1, char c);
char	**ft_split(t_data *d, char *s, char c);



int	ft_strcmp(const char *s1, const char *s2);
unsigned count_args(char   **args);
bool between(float n, float min, float max);
float	 ft_atof(const char *s, bool *err);
bool s_is_whitespace(char	*s);

/*
	linked list
*/
t_node* create_node(t_data *d, void *t_data);
void add_node(t_data *d, t_node **head, void *t_data);
int remove_node(t_data *d, t_node **head, void *t_data);
void add_float_node_sorted(t_data *d, t_node **head, float value);


/*
	gc
*/

void					*gc_malloc(t_data *d, size_t size);
void					gc_free(t_data *d, void *ptr);
void					gc_void(t_data *d);
void					*gc_realloc(t_data *d, void *ptr, size_t old_size,
							size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_bzero(void *s, size_t n);


int get_color_value(t_color c);
t_color add_colors(t_color c1, t_color c2);
t_color clamp_color(t_color c1);
t_color sub_colors(t_color c1, t_color c2);
t_color mul_colors(t_color c1, t_color c2);
t_color neg_color(t_color c1);
t_color zero_color();
t_color scale_color(t_color v, float scale);
void print_color(t_color c, bool newline);



#endif
