#ifndef miniRT_H
#define miniRT_H

#include "gc.h"

#define KEY_PRESS 2
#define KEY_RELEASE 3



typedef struct s_node
{
    void *data;
    struct s_node *next;
	char	type;
} t_node;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_pattern
{
	t_color c1;
	t_color c2;
	char	PATTERN_TYPE;
}	t_pattern;

typedef struct s_object
{
    void *data;
    struct s_object *next;
	char	type;
	t_vector (*get_norm ) (struct s_object *o, t_point pt_on_sp);
	t_color	(*get_color) (struct s_object *o);
	void (*set_color) (struct s_object *o, t_color new_color); 
	t_pattern *(*get_pattern) (struct s_object *o); 
	void (*set_pattern) (struct s_object *o, t_pattern	*p); 
} t_object;


typedef struct s_mlx
{
	void *mlx;
	void *win;
	bool	ctrl_pressed;
}  t_mlx;

enum e_types
{
	e_ambient = 3,
	e_camera = 4,
	e_color = 4,
	e_light = 4,
	e_plain = 4,
	e_plain_pattern = 6,
	e_sphere = 4,
	e_sphere_pattern = 6,
	e_cylinder = 6,
};

/* pixel color -> ambient, diffuse, specular */
typedef struct s_px_color
{
	t_color a;
	t_color d;
	t_color s;
} 
t_px_color ;

typedef struct s_ambient
{
	t_color		c;
	float	ratio;
}	t_ambient;


typedef struct s_light
{
	t_point	p;
	float	brightness; // 0 -> 1
	t_color	c;
}	t_light;

typedef struct s_camera
{
	t_point		origin;
    t_vector	forward; // normalized
    t_vector	right; // should be calculated
    t_vector	up; // should be calculated
	t_vector	direction;
	unsigned  fov; // field of view angle (how much of the cam we can see) when fov is small view is zoomed in
	float		aspect;
} t_camera;

typedef struct s_world
{
	t_node 		*lights;
	t_node 		*planes;
	t_node 		*cylinders;
	t_node 		*spheres;
	t_ambient	*ambient;
	t_camera 	*cam;
	t_object	*objects;
	bool		gray_on;
} t_world;


typedef struct s_sphere
{
	t_point		origin;
	float		diameter;
	float		radius_squared;
	t_color		c;
	t_pattern	*pattern;
} t_sphere;

typedef struct s_plane
{
	t_point		origin;
	t_vector	normal;
	t_color		c;
	t_pattern *pattern;
} t_plane;

typedef struct s_cylinder
{
	t_point		origin;
	t_vector	normal;
	float		diameter;
	float		height;
	t_color		c;
} t_cylinder;

typedef struct s_intersect
{
	float t;
	t_object	*obj;
}	t_intersect;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}   t_img;

typedef struct s_core
{
	t_mlx m;
	t_world *w;
	t_gc	*gc;
	t_img	img;
	bool	cmd_on; // maybe add a command line to handle adding spheres and light ... ?
	int		iter; // if 1 it iterates throught each pixel, as big as it gets, the quality goes down
} t_core;



/**
 * @brief Returns global raytracing engine instance
 * @return t_core* Engine instance containing scene data and render settings
 * @note Singleton pattern - single engine instance
 */
t_core			*getengine(void);

/*     >>>>>Parsing Funtions Section<<<<<     */
void parsing(int ac, char *filename);
unsigned count_args(char   **args);
bool	between(float n, float min, float max);
float	ft_atof(const char *s, bool *err);
void	loadline(char *line, int n_line, char *filename);
void	readfile(int fd, char *filename);
int		check_file(char *filename);





/*     >>>>>Rendering Funtions Section<<<<<     */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
float get_intersect_dist(t_world *w, t_ray *ray);
// t_color	sp_light(t_sphere	*hit_sph, t_ray	*cam_ray, float smallest_t);
t_color	sp_light(t_object	*hit_sph, t_ray	*cam_ray, float smallest_t);
// t_color	pl_light(t_plane	*hit_pl, t_ray	*cam_ray, float smallest_t);
t_color	pl_light(t_object	*hit_obj, t_ray	*cam_ray, float smallest_t);
bool is_shadowed(t_world *w, t_point p);
t_color	lighting(t_ray *cam_ray, t_object *hit_obj, float smallest_t);
t_vector	generate_cam_dir(t_camera	*cam, float scale, float ndcx, float ndcy);
float sp_intersect(t_sphere *s, t_ray *ray);
float pl_intersect(t_plane *pl, t_ray *ray);
t_color intersect_world(t_world *w, t_ray *cam_ray);
int input(int key, void *d);
void    rendering(void);




/*
	linked list
*/
t_node* create_node(t_core *d, void *t_core);
void add_node(t_core *d, t_node **head, void *data, char type_macro);
int remove_node(t_core *d, t_node **head, void *data);
void add_float_node_sorted(t_core *d, t_node **head, float value);

t_object* create_obj(t_core *d, void *data);
void add_obj(t_core *d, t_object **head, void *data, char type_macro);
void add_float_object_sorted(t_core *d, t_object **head, float value);
int remove_obj(t_core *d, t_object **head, void *data);


void setup_cam_dir(t_camera	*cam);


float maxf(float a, float b);
float minf(float a, float b);
float maxi(float a, float b);
float mini(float a, float b);

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
t_color add_colors(t_color c1, t_color c2, bool is_clampt);
t_color clamp_color(t_color c1);
t_color sub_colors(t_color c1, t_color c2);
t_color abs_sub_colors(t_color c1, t_color c2);
t_color mul_colors(t_color c1, t_color c2);
t_color increment_color(t_color c1, int amount);
t_color neg_color(t_color c1);
t_color zero_color();
t_color scale_color(t_color v, float scale);
t_color lerp_colors(t_color c1, t_color c2, float t);
void print_color(t_color c, bool newline);
t_color sum_colors(t_color amb, t_color dif, t_color   spc);
t_color rgb_to_gray(t_color c);


/* matrices */
float **create_matrix_2x2(float a, float b, float c, float d);
float **create_matrix_3x3(float a, float b, float c, float l, float m, float n, float x, float y, float z);
float **create_matrix_4x4(float a, float b, float c, float d, 
    float e, float f, float g, float h,
    float i, float j, float k, float l,
    float m, float n, float o, float q);
void init_matrix_n(float **matrix, int n);
void print_matrix_n(float **matrix, int n);
void print_matrix_row_col(float **matrix, int row, int col);
float **submatrix(float **matrix, int row, int col, int n);
float  **get_new_matrix_n(int n);
float  **get_new_matrix_row_col(int row, int col);
float **mul_matrix_n(float **m1, float **m2, int n);
float **mul_matrix_row_col(float **m1, float **m2, int row1, int col2);
float **get_transposed(float **m, int n);
void transpose(float **m, int n);
float get_determinant_2(float **m);
float get_determinant_n(float **m, int n);
float **get_identity_matrix_n(int n);
float get_minor_n(float **matrix, int row, int col, int n);
float get_cofactor_n(float **matrix, int row, int col, int n);
float **get_inverted_n(float **matrix, int n);
float **get_4_1_matrix(float x, float y, float z, float w);
float **from_n_to_4_1_matrix(float **matrix_n);
float **from_4_1_to_n_matrix(float **matrix_4_1);
float **get_translation_matrix(float x, float y, float z);
float **get_scaling_matrix(float x, float y, float z, float w);
float deg_to_rad(float deg);
float rad_to_deg(float rad);
float **rotate_x(float rad);
float **rotate_y(float rad);
float **rotate_z(float rad);
t_ray transform_ray(t_ray old_r, float **transformation_mx);
float **get_orientation_view_matrix(t_vector left, t_vector true_up, t_vector forward);
t_sphere transform_sphere(t_sphere s, float **transformation_mx);
t_point translate_mx_to_point(float **m);
t_vector translate_mx_to_vector(float **m);


/*     >>>>>Utils funtions section<<<<<     */
bool	is_wspace(char *s);
char	*err_msg(const char *filename, const int n_line);

int key_press(int keycode, t_core *engine);
int key_release(int keycode, t_core *engine);
void init_hooks(t_core *engine);
int input(int key, void *d);
void handle_input();
int mouse_input(int key, int x, int y, void *d);

int get_rgb(t_color color);
t_vector	reflect (t_vector	light, t_vector	norm);
t_vector add_vectors(t_vector v1, t_vector v2);
t_vector sub_vectors(t_vector v1, t_vector v2);
t_vector sub_points(t_point p1, t_point p2);
t_vector neg_vector(t_vector v1);
t_point add_points(t_point v1, t_point v2);
t_vector p_to_v(t_point p);
t_point v_to_p(t_vector v);
t_vector scale_vector(t_vector v, float scale);
t_vector shrink_vector(t_vector v, float shrink);
float get_len_vector(t_vector v1);
void print_vector(t_vector v);
void print_point(t_point p);
t_point	position_at(t_ray	*r, float t);
t_vector normal(t_vector v);
float dot(t_vector v1, t_vector v2);
t_vector cross(t_vector v1, t_vector v2);
t_vector normal_at(t_sphere s, t_point p);
float deg_to_rad(float deg);
float rad_to_rad(float rad);
t_vector get_obj_norm(t_object	*o, t_point	pt_on_sphere);
t_color get_obj_color(t_object *o);
t_pattern	*get_obj_pattern(t_object	*o);
void set_obj_pattern(t_object *o, t_pattern *p);
void set_obj_color(t_object *o, t_color c);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);












#endif
