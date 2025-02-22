#ifndef miniRT_H
#define miniRT_H

#include "gc.h"

#define KEY_PRESS 2
#define KEY_RELEASE 3

typedef	struct s_inter
{
	double t1;
	double t2;
} t_inter;


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
	char	type;
}	t_pattern;

typedef struct s_object
{
    void *data;
    struct s_object *next;
	char	type;
	t_vec (*get_norm ) (struct s_object *o, t_vec pt_on_sp);
	t_vec (*get_origin ) (struct s_object *o);
	t_color	(*get_color) (struct s_object *o);
	void (*set_color) (struct s_object *o, t_color new_color); 
	t_pattern *(*get_pattern) (struct s_object *o); 
	double (*get_reflect) (struct s_object *o); 
	void (*set_pattern) (struct s_object *o, t_pattern	*p); 
} t_object;


typedef struct s_hit
{
	double t1;
	double t2;
	t_object	*obj;
}	t_hit;

typedef struct s_mlx
{
	void *mlx;
	void *win;
	bool	ctrl_pressed;
}  t_mlx;

typedef struct s_cube {
    t_vec origin;
    t_color c;
    t_pattern *pattern;
    double reflect;
} t_cube;

enum e_types
{
	e_ambient = 3,
	e_camera = 4,
	e_cube = 3,
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
	double	ratio;
}	t_ambient;


typedef struct s_light
{
	t_vec	p;
	double	brightness; // 0 -> 1
	t_color	c;
}	t_light;

typedef struct s_camera
{
	t_vec		origin;
    t_vec	forward; // normalized
    t_vec	right; // should be calculated
    t_vec	up; // should be calculated
	t_vec	direction;
	unsigned  fov; // field of view angle (how much of the cam we can see) when fov is small view is zoomed in
	double		aspect;
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
	t_vec		origin;
	double		diameter;
	double		radius_squared;
	t_color		c;
	t_pattern	*pattern;
    double reflect;

} t_sphere;

typedef struct s_plane
{
	t_vec		origin;
	t_vec	normal;
	t_color		c;
	t_pattern *pattern;
    double reflect;
} t_plane;

typedef struct s_cylinder
{
	t_vec		origin;
	t_vec	normal;
	double		diameter;
	double		height;
	double		reflect;
	t_color		c;
} t_cylinder;

typedef struct s_intersect
{
	double t;
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
	double		rays_px;
	bool	cmd_on; // maybe add a command line to handle adding spheres and light ... ?
	bool	aa_on; // maybe add a command line to handle adding spheres and light ... ?
	bool	refl_on; // maybe add a command line to handle adding spheres and light ... ?
	int		iter; // if 1 it iterates throught each pixel, as big as it gets, the quality goes down
	int		counter;

	unsigned char *png;
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
bool	between(double n, double min, double max);
double	ft_atof(const char *s, bool *err);
void	loadline(char *line, int n_line, char *filename);
void	readfile(int fd, char *filename);
int		check_file(char *filename);





/*     >>>>>Rendering Funtions Section<<<<<     */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
double get_intersect_dist(t_world *w, t_ray *ray);
// t_color	sp_light(t_sphere	*hit_sph, t_ray	*cam_ray, double smallest_t);
t_color	sp_light(t_object	*hit_sph, t_ray	*cam_ray, double smallest_t);
// t_color	pl_light(t_plane	*hit_pl, t_ray	*cam_ray, double smallest_t);
t_color	pl_light(t_object	*hit_obj, t_ray	*cam_ray, double smallest_t);
bool is_shadowed(t_world *w, t_vec p, t_light *light);
t_color	lighting(t_ray *cam_ray, t_object *hit_obj, double smallest_t, t_light	*light);
t_vec	generate_cam_dir(t_camera	*cam, double scale, double ndcx, double ndcy);
t_inter sp_intersect(t_sphere *s, t_ray *ray);
t_inter pl_intersect(t_plane *pl, t_ray *ray);
t_inter cy_intersect(t_cylinder *cy, t_ray *r);
t_color intersect_world(t_world *w, t_ray *cam_ray);
int input(int key, void *d);
void    rendering(void);




/*
	linked list
*/
t_node* create_node(t_core *d, void *t_core);
void add_node(t_core *d, t_node **head, void *data, char type_macro);
int remove_node(t_core *d, t_node **head, void *data);
void add_float_node_sorted(t_core *d, t_node **head, double value);

t_object* create_obj(t_core *d, void *data);
void add_obj(t_core *d, t_object **head, void *data, char type_macro);
void add_float_object_sorted(t_core *d, t_object **head, double value);
int remove_obj(t_core *d, t_object **head, void *data);


void setup_cam_dir(t_camera	*cam);


double maxf(double a, double b);
double minf(double a, double b);
double maxi(double a, double b);
double mini(double a, double b);

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
bool    point_struct_filled(t_vec	*p, char  **args);
bool    vector_struct_filled(t_vec	*v, char  **args);
bool    elem_added(t_core *d,char **args);


void handle_pat(char *patt_name, char *patt_clrs, t_pattern  **pat, t_color main_clr);

int get_color_value(t_color c);
t_color rgb_add(t_color c1, t_color c2, bool is_clampt);
t_color clamp_color(t_color c1);
t_color sub_colors(t_color c1, t_color c2);
t_color abs_sub_colors(t_color c1, t_color c2);
t_color rgb_mul(t_color c1, t_color c2);
t_color rgb_mad(t_color c1, t_color c2);
t_color increment_color(t_color c1, int amount);
t_color zero_color();
t_color rgb_scl(t_color v, double scale);
t_color sclamp_color(t_color v, double scale);
void print_color(t_color c, bool newline);
t_color rgb_sum(t_color amb, t_color dif, t_color   spc);
double get_brightness(t_color c);
t_color rgb_to_gray(t_color c);

/* matrices */
double **create_matrix_2x2(double a, double b, double c, double d);
double **create_matrix_3x3(double a, double b, double c, double l, double m, double n, double x, double y, double z);
double **create_matrix_4x4(double a, double b, double c, double d, 
    double e, double f, double g, double h,
    double i, double j, double k, double l,
    double m, double n, double o, double q);
void init_matrix_n(double **matrix, int n);
void print_matrix_n(double **matrix, int n);
void print_matrix_row_col(double **matrix, int row, int col);
double **submatrix(double **matrix, int row, int col, int n);
double  **get_new_matrix_n(int n);
double  **get_new_matrix_row_col(int row, int col);
double **mul_matrix_n(double **m1, double **m2, int n);
double **mul_matrix_row_col(double **m1, double **m2, int row1, int col2);
double **get_transposed(double **m, int n);
void transpose(double **m, int n);
double get_determinant_2(double **m);
double get_determinant_n(double **m, int n);
double **get_identity_matrix_n(int n);
double get_minor_n(double **matrix, int row, int col, int n);
double get_cofactor_n(double **matrix, int row, int col, int n);
double **get_inverted_n(double **matrix, int n);
double **get_4_1_matrix(double x, double y, double z, double w);
double **from_n_to_4_1_matrix(double **matrix_n);
double **from_4_1_to_n_matrix(double **matrix_4_1);
double **get_translation_matrix(double x, double y, double z);
double **get_scaling_matrix(double x, double y, double z, double w);
double deg_to_rad(double deg);
double rad_to_deg(double rad);
double **rotate_x(double rad);
double **rotate_y(double rad);
double **rotate_z(double rad);
t_ray transform_ray(t_ray old_r, double **transformation_mx);
double **get_orientation_view_matrix(t_vec left, t_vec true_up, t_vec forward);
t_sphere transform_sphere(t_sphere s, double **transformation_mx);
t_vec translate_mx_to_point(double **m);
t_vec translate_mx_to_vector(double **m);


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
t_vec	reflect (t_vec	light, t_vec	norm);
t_vec vec_sub(t_vec p1, t_vec p2);
t_vec vec_neg(t_vec v1);
t_vec vec_add(t_vec v1, t_vec v2);
t_vec p_to_v(t_vec p);
t_vec vec_scl(t_vec v, double scale);
double vec_len(t_vec v1);
void vec_log(t_vec v);
t_vec	position_at(t_ray	*r, double t);
t_vec normal(t_vec v);
double vec_dot(t_vec v1, t_vec v2);
t_vec cross(t_vec v1, t_vec v2);
t_vec normal_at(t_sphere s, t_vec p);
double deg_to_rad(double deg);
double rad_to_rad(double rad);
t_vec get_obj_norm(t_object	*o, t_vec	pt_on_sphere);
t_vec get_obj_origin(t_object	*o);
t_color get_obj_color(t_object *o);
t_pattern	*get_obj_pattern(t_object	*o);
void set_obj_pattern(t_object *o, t_pattern *p);
void set_obj_color(t_object *o, t_color c);
double get_obj_reflect(t_object *o);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);





t_vec cube_normal_at(t_cube *cube, t_vec world_point);
t_inter cube_intersect(t_cube *cube, t_ray *ray);
void check_axis(double origin, double direction, double *tmin, double *tmax);
t_vec get_obj_norm(t_object	*o, t_vec	pt_on_sphere);
t_vec get_cube_norm(t_object *o, t_vec pt_on_cube);
t_vec get_cube_origin(t_object *o);
t_color get_cube_color(t_object *o);
t_pattern *get_cube_pattern(t_object *o);
void set_cube_pattern(t_object *o, t_pattern *p);
void set_cube_color(t_object *o, t_color c);
double get_cube_reflect(t_object *o);
bool cube_handled(t_core *d, char **args);



void swapf(double *t1, double *t2);

/* will be deleted */
void save_to_img(t_color px_color, int x, int y);
t_color handle_object_pat(t_object *hit_obj, t_vec inter_point);
t_color	get_reflect_color(int remaining, t_object *hit_obj, t_vec pt_cam_vec, t_vec	inter_point);


#endif
