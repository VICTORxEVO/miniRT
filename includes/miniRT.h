/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:29:02 by sgouzi            #+#    #+#             */
/*   Updated: 2025/04/11 17:18:05 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "gc.h"

typedef struct s_inter
{
	double			t1;
	double			t2;
}					t_inter;

typedef struct s_node
{
	void			*data;
	struct s_node	*next;
	char			type;
}					t_node;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct	s_phong
{
	t_color	diffuse;
	t_color	specular;
	t_color	ambient;
}	t_phong;

typedef struct s_object
{
	void			*data;
	struct s_object	*next;
	char			type;
}					t_object;

typedef struct s_hit
{
	double			t1;
	double			t2;
	t_object		*obj;
}					t_hit;

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	bool			ctrl_pressed;
}					t_mlx;

enum				e_types
{
	e_ambient = 3,
	e_camera = 4,
	e_color = 4,
	e_light = 4,
	e_plain = 4,
	e_sphere = 4,
	e_cylinder = 6,
};

typedef struct s_ambient
{
	t_color			c;
	double			ratio;
}					t_ambient;

typedef struct s_light
{
	t_vec			p;
	double			brightness;
	t_color			c;
}					t_light;

typedef struct s_camera
{
	t_vec			origin;
	t_vec			forward;
	t_vec			right;
	t_vec			up;
	t_vec			direction;
	unsigned int	fov;
	double			aspect;
}					t_camera;

typedef struct s_world
{
	t_node			*lights;
	t_node			*planes;
	t_node			*cylinders;
	t_node			*spheres;
	t_ambient		*ambient;
	t_camera		*cam;
	t_object		*objects;
	bool			gray_on;
}					t_world;

typedef struct s_sphere
{
	t_vec			origin;
	double			diameter;
	double			radius_squared;
	t_color			c;

}					t_sphere;

typedef struct s_plane
{
	t_vec			origin;
	t_vec			normal;
	t_color			c;
}					t_plane;

typedef struct s_cylinder
{
	t_vec			origin;
	t_vec			normal;
	double			diameter;
	double			height;
	t_color			c;
}					t_cylinder;

typedef struct s_intersect
{
	double			t;
	t_object		*obj;
}					t_intersect;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img;

typedef struct s_core
{
	t_mlx			m;
	t_world			*w;
	t_gc			*gc;
	t_img			img;
	int				rays_px;
	bool			aa_on;
	int				iter;
}					t_core;

typedef struct s_calc
{
	double			smallest_t;
	t_light			*light;
	bool			lighted;
	t_color			obj_clr;
}					t_calc;

typedef struct s_parse_cam
{
	char	**cord;
	char	**vctr;
	double	FOV;
	t_vec	vec3d;
	t_vec	pcord;
	bool	err;
}	t_parse_cam;

typedef struct s_parse_light
{
	char	**clrs;
	double	light_value;
	t_color	light_color;
	t_vec	light_cord;
	t_light	*light;
	char	**cord;
	bool	err;
}	t_parse_light;

typedef struct s_parse_plane
{
	char	**clrs;
	char	**vctr;
	t_color	plane_color;
	t_vec	plane_cord;
	t_vec	plane_norm;
	t_plane	*plane;
	char	**cord;
}	t_parse_plane;

typedef struct s_parse_cylinder
{
	char		**clrs;
	char		**vctr;
	t_color		cylinder_color;
	t_vec		cylinder_cord;
	t_vec		cylinder_norm;
	double		diameter;
	double		height;
	t_cylinder	*cylinder;
	char		**cord;
	bool		err;
}	t_parse_cylinder;

typedef struct s_parse_sphere
{
	char		**clrs;
	t_color		sphere_color;
	t_vec		sphere_cord;
	double		diameter;
	t_sphere	*sphere;
	char		**cord;
	bool		err;
}	t_parse_sphere;

typedef	struct s_utils_ambient
{
	char **clrs;
	double ambient_ratio;
	t_ambient *ambient;
	t_color ambient_color;
	bool err;
}	t_utils_ambient;

t_core				*getengine(void);
void				parsing(int ac, char *filename);
bool				starts_with(char *small, char *big);
bool				ends_with(char *small, char *big);
unsigned int		count_args(char **args);
double				ft_atof(const char *s, bool *err);
bool				between(double n, double min, double max);
void				loadline(char *line, int n_line, char *filename);
void				readfile(int fd, char *filename);
int					check_file(char *filename);

/*     >>>>>Rendering Funtions Section<<<<<     */
void				my_mlx_pixel_put(t_img *img, int x, int y, int color);
double				get_intersect_dist(t_world *w, t_ray *ray);
t_hit				set_hit(double t1, double t2, t_object *o);
t_hit				find_hit(t_world *w, t_ray *cam_ray);
t_color				get_ambient(bool lighted, t_world *w, t_object *obj,
						t_color obj_clr);
bool				is_shadowed(t_world *w, t_vec p, t_light *light);
t_color				lighting(t_ray *cam_ray, t_object *hit_obj, t_calc *calc);
t_vec				generate_cam_dir(t_camera *cam, double scale, double ndcx,
						double ndcy);
t_inter				sp_intersect(t_sphere *s, t_ray *ray);
t_inter				pl_intersect(t_plane *pl, t_ray *ray);
t_inter				cy_intersect(t_cylinder *cy, t_ray *r);
t_color				intersect_world(t_world *w, t_ray *cam_ray);
void				rendering(void);

t_vec				cy_normal(t_cylinder *cy, t_vec world_point);

/*
	linked list
*/
t_node				*create_node(void *t_core);
void				add_node(t_node **head, void *data, char type_macro);
t_object			*create_obj(void *data);
void				add_obj(t_object **head, void *data, char type_macro);

void				setup_cam_dir(t_camera *cam);

/*
	shapes handling
*/
bool				light_handled(t_core *d, char **args);
bool				plane_handled(t_core *d, char **args);
bool				cylinder_handled(t_core *d, char **args);
bool				sphere_handled(t_core *d, char **args);
bool				camera_handled(t_core *d, char **args);
bool				ambient_handled(t_core *d, char **args);
bool				color_struct_filled(t_color *c, char **args);
bool				point_struct_filled(t_vec *p, char **args);
bool				vector_struct_filled(t_vec *v, char **args);
bool				elem_added(t_core *d, char **args);

t_color				rgb_add(t_color c1, t_color c2, bool is_clampt);
t_color				clamp_color(t_color c1);
t_color				sub_colors(t_color c1, t_color c2);
t_color				rgb_mul(t_color c1, t_color c2);
t_color				rgb_mad(t_color c1, t_color c2);
t_color				zero_color(void);
t_color				rgb_scl(t_color v, double scale);
t_color				sclamp_color(t_color v, double scale);
t_color				rgb_sum(t_color amb, t_color dif, t_color spc);
double				get_brightness(t_color c);
t_color				rgb_to_gray(t_color c);

/* matrices */
double				**create_matrix_2x2(double a, double b, double c, double d);
double				**create_matrix_3x3(double a, double b, double c, double l,
						double m, double n, double x, double y, double z);
double				**create_matrix_4x4(double a, double b, double c, double d,
						double e, double f, double g, double h, double i,
						double j, double k, double l, double m, double n,
						double o, double q);
void				init_matrix_n(double **matrix, int n);
void				print_matrix_n(double **matrix, int n);
void				print_matrix_row_col(double **matrix, int row, int col);
double				**submatrix(double **matrix, int row, int col, int n);
double				**get_new_matrix_n(int n);
double				**get_new_matrix_row_col(int row, int col);
double				**mul_matrix_n(double **m1, double **m2, int n);
double				**mul_matrix_row_col(double **m1, double **m2, int row1,
						int col2);
double				**get_transposed(double **m, int n);
void				transpose(double **m, int n);
double				get_determinant_2(double **m);
double				get_determinant_n(double **m, int n);
double				**get_identity_matrix_n(int n);
double				get_minor_n(double **matrix, int row, int col, int n);
double				get_cofactor_n(double **matrix, int row, int col, int n);
double				**get_inverted_n(double **matrix, int n);
double				**get_4_1_matrix(double x, double y, double z, double w);
double				**from_n_to_4_1_matrix(double **matrix_n);
double				**from_4_1_to_n_matrix(double **matrix_4_1);
double				**get_translation_matrix(double x, double y, double z);
double				**get_scaling_matrix(double x, double y, double z,
						double w);
double				deg_to_rad(double deg);
double				rad_to_deg(double rad);
double				**rotate_x(double rad);
double				**rotate_y(double rad);
double				**rotate_z(double rad);
t_ray				transform_ray(t_ray old_r, double **transformation_mx);
t_vec				translate_mx_to_point(double **m);
t_vec				translate_mx_to_vector(double **m);
int					close_window(t_core *engine);
void				mlx_hooks(void);
/*     >>>>>Utils funtions section<<<<<     */
bool				is_wspace(char *s);
char				*err_msg(const char *filename, const int n_line);
void				set_smallest_if(double *smallest, t_inter it);
double				get_smallest_t(t_object *node, t_ray *ray);
int					key_press(int keycode, t_core *engine);
int					key_release(int keycode, t_core *engine);
void				init_hooks(t_core *engine);
t_vec				get_cam_dir(double x, double y, int i);
int					get_clr_int(t_color color);
t_vec				reflect(t_vec light, t_vec norm);
t_vec				vec_sub(t_vec p1, t_vec p2);
t_vec				vec_neg(t_vec v1);
t_vec				vec_add(t_vec v1, t_vec v2);
t_vec				vec_scl(t_vec v, double scale);
double				vec_len(t_vec v1);
t_vec				position_at(t_ray *r, double t);
t_vec				normal(t_vec v);
double				vec_dot(t_vec v1, t_vec v2);
t_vec				cross(t_vec v1, t_vec v2);
double				deg_to_rad(double deg);
t_vec				get_obj_origin(t_object *o);
t_color				get_obj_color(t_object *o);
void				set_obj_color(t_object *o, t_color c);
void				my_mlx_pixel_put(t_img *data, int x, int y, int color);

t_vec				get_obj_norm(t_object *o, t_vec pt_on_sphere);
t_vec				prepare_obj_norm(t_object *hit_obj, t_vec point, t_vec pt_cam_vec_norm);
#endif
