#ifndef miniRT_H
#define miniRT_H

#include "gc.h"

typedef struct s_node
{
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
	t_node 		*lights;
	t_node 		*planes;
	t_node 		*cylinders;
	t_node 		*spheres;
	t_ambient	*ambient;
	t_camera 	*cam;
} t_world;


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
} t_pars;

typedef struct s_core
{
	t_mlx m;
	t_world *w;
	t_gc	*gc;
} t_core;

/**
 * @brief Returns global raytracing engine instance
 * @return t_core* Engine instance containing scene data and render settings
 * @note Singleton pattern - single engine instance
 */
t_core			*getengine(void);

/*     >>>>>Parsing Funtions Section<<<<<     */
bool parsing(int ac, char *filename);
unsigned count_args(char   **args);
bool between(float n, float min, float max);
float	 ft_atof(const char *s, bool *err);
void    loadline(char *line, int n_line, char *filename);





/*     >>>>>Rendering Funtions Section<<<<<     */
void    rendering(void);








/*
	linked list
*/
t_node* create_node(t_core *d, void *t_core);
void add_node(t_core *d, t_node **head, void *t_core);
int remove_node(t_core *d, t_node **head, void *t_core);
void add_float_node_sorted(t_core *d, t_node **head, float value);


/*
	shapes handling 
*/
bool    light_handled(t_core *d, char **args);
bool    plane_handled(t_core *d, char **args);
bool    cylinder_handled(t_core *d, char **args);
bool    sphere_handled(t_core *d, char **args);
bool    camera_handled(t_core *d, char **args);
bool    ambient_handled(t_core *d, char **args);
bool    color_struct_filled(t_color	*c, char  **args);
bool    point_struct_filled(t_point	*p, char  **args);
bool    vector_struct_filled(t_vector	*v, char  **args);
bool    elem_added(t_core *d,char **args);


int get_color_value(t_color c);
t_color add_colors(t_color c1, t_color c2);
t_color clamp_color(t_color c1);
t_color sub_colors(t_color c1, t_color c2);
t_color mul_colors(t_color c1, t_color c2);
t_color neg_color(t_color c1);
t_color zero_color();
t_color scale_color(t_color v, float scale);
void print_color(t_color c, bool newline);




/*     >>>>>Utils funtions section<<<<<     */
bool	is_wspace(char *s);



















#endif
