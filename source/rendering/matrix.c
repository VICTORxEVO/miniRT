#include "miniRT.h"

double **create_matrix_2x2(double a, double b, double c, double d)
{
    double **matrix;

    int i = -1;
    matrix = malloc(4 * sizeof(double *));
    while (++i < 4)
        matrix[i] = malloc(4 * sizeof(double));

    matrix[0][0] = a;
    matrix[0][1] = b;
    matrix[1][0] = c;
    matrix[1][1] = d;
    return matrix;
}

double **create_matrix_3x3(double a, double b, double c, double l, double m, double n, double x, double y, double z)
{
    double **matrix;
    int i = -1;

    matrix = malloc(3 * sizeof(double *));
    while (++i < 3)
        matrix[i] = malloc(3 * sizeof(double));

    matrix[0][0] = a;
    matrix[0][1] = b;
    matrix[0][2] = c;
    matrix[1][0] = l;
    matrix[1][1] = m;
    matrix[1][2] = n;
    matrix[2][0] = x;
    matrix[2][1] = y;
    matrix[2][2] = z;

    return matrix;
}

double **create_matrix_4x4(double a, double b, double c, double d, 
    double e, double f, double g, double h,
    double i, double j, double k, double l,
    double m, double n, double o, double q)
{
    double **matrix;
    int x = -1;

    matrix = malloc(4 * sizeof(double *));
    while (++x < 4)
        matrix[x] = malloc(4 * sizeof(double));

    matrix[0][0] = a;
    matrix[0][1] = b;
    matrix[0][2] = c;
    matrix[0][3] = d;

    matrix[1][0] = e;
    matrix[1][1] = f;
    matrix[1][2] = g;
    matrix[1][3] = h;

    matrix[2][0] = i;
    matrix[2][1] = j;
    matrix[2][2] = k;
    matrix[2][3] = l;


    matrix[3][0] = m;
    matrix[3][1] = n;
    matrix[3][2] = o;
    matrix[3][3] = q;

    return matrix;
}

void init_matrix_n(double **matrix, int n)
{
    int i = -1;
    int j = -1;
    while (++i < n)
    {
        while (++j < n)
            matrix[i][j] = 0;
    }
}

void print_matrix_n(double **matrix, int n)
{
    int i = -1;
    int j = -1;
    while (++i  < n)
    {
        j = -1;
        while (++j < n)
        {
            printf("  %.5f", matrix[i][j]);
            if (j < n)
                printf("  |");
            printf("  ");
        }
        j = -1;
        while (++j < n)
        {
            printf("________________________________________________________________________________");
        }
        printf("\n\n");
    }
    printf("\n\n");
}

void print_matrix_row_col(double **matrix, int row, int col)
{
    int i = -1;
    int j = -1;
    printf("\n\n");
    while (++i  < row)
    {
        j = -1;
        while (++j < col)
        {
            printf("  %.5f", matrix[i][j]);
            if (j < col)
                printf("  |");
            printf("  ");
        }
        printf("\n\n");
        j = -1;
        while (++j < col)
        {
            printf("____________");
        }
        printf("\n\n");
    }
    printf("\n\n");
}

double **submatrix(double **matrix, int row, int col, int n)
{
    if (n < 2)
    {
        printf("this matrix is too small to have a submatrix\n");
        return NULL;
    }
    double **sub;
    sub = get_new_matrix_n(n - 1);

    int x = -1;
    int y = -1;

    int u = 0;
    int v = 0;
    while (++y < n)
    {
        x = -1;
        v = 0;
        while (++x < n)
        {
            if (y == row)
                continue;
            else if (x == col)
                continue;
            else
            {
                sub[u][v++] = matrix[y][x];
            }
        }
        if (v == n - 1)
            u++;
    }
    return sub;
}

double  **get_new_matrix_n(int n)
{
    double **m;
    int i = -1;
    int j = -1;

    m = malloc(n * sizeof(double *));
    while (++i < n)
        m[i] = malloc(n * sizeof(double));
    i = 0;
    while (++i < n)
    {
        while (++j < n)
            m[i][j] = 0.0f;
    }
    return m;
}

double  **get_new_matrix_row_col(int row, int col)
{
    double **m;
    int i = -1;
    int j = -1;

    m = malloc(row * sizeof(double *));
    while (++i < row)
        m[i] = malloc(col * sizeof(double));
    i = -1;
    while (++i < row)
    {
        j = -1;
        while (++j < col)
            m[i][j] = 0.0f;
    }
    return m;
}

double **mul_matrix_n(double **m1, double **m2, int n)
{
    double **m3;
    int i = -1;
    int j = -1;
    m3 = get_new_matrix_n(n);

    while (++i < n)
    {
        j = -1;
        while (++j < n)
        {
            int k = -1;
            while (++k < n)
                m3[i][j] += m1[i][k] * m2[k][j];
        }
    }
    return m3;
}

double **mul_matrix_row_col(double **m1, double **m2, int row1, int col2)
{
    double **m3;
    int i = -1;
    int j = -1;
    m3 = get_new_matrix_row_col(row1, col2);

    while (++i < row1)
    {
        j = -1;
        while (++j < col2)
        {
            int k = -1;
            while (++k < row1)
                m3[i][j] += m1[i][k] * m2[k][j];
        }
    }
    return m3;
}

double **get_transposed(double **m, int n)
{
    double **t = get_new_matrix_n(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            t[i][j] = m[j][i];
    return t;
}

void transpose(double **m, int n)
{
    int i = -1;
    int j = -1;

    double temp;
    while (++i < n)
    {
        j = -1;
        while (++j < i)
        {
            printf("swaping -> %f  and   %f\n", m[i][j], m[j][i]);
            temp = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = temp;
        }
    }
}

double get_determinant_2(double **m)
{
    double det;

    det = m[0][0] * m[1][1] - m[0][1] * m[1][0];
    return det;       
}

double get_determinant_n(double **m, int n)
{
    double det;
    double co;
    int i = -1;

    det = 0;
    if (n == 2)
        det = get_determinant_2(m);
    else
    {
        while (++i < n)
        {
            co = get_cofactor_n(m, 0, i, n);
            det += (co * m[0][i]);
        }
    }
    return det;
}

double **get_identity_matrix_n(int n)
{
    double **i_matrix;
    int i = -1;
    int j = -1;

    i_matrix = malloc(n * sizeof(double *));
    while (++i < n)
        i_matrix[i] = malloc(n * sizeof(double));
    i = -1;
    while (++i < n)
    {
        j = -1;
        while (++j < n)
        {
            i_matrix[i][j] = 0.0f;
            if (i == j)
                i_matrix[i][j] = 1.0f;
        }
    }
    return i_matrix;
}

double get_minor_n(double **matrix, int row, int col, int n)
{

    // minor of an element at row i and col j is the get_determinant_n of the sub matrix at (i, j)
    double **sub = submatrix(matrix, row, col, n);
    double minor = get_determinant_n(sub, n - 1);
    return minor;
}

double get_cofactor_n(double **matrix, int row, int col, int n)
{
    double minor = get_minor_n(matrix, row, col, n);
    double cofactor = minor;
    if ((row + col) % 2 != 0)
    {
        cofactor *= -1;
    }
    return cofactor;
}

double **get_inverted_n(double **matrix, int n)
{
    double det;
    double **inverted;
    double co;
    int i = -1;
    int j = -1;

    det = get_determinant_n(matrix, n);
    if (det == 0)
    {
        printf("MATRIX NOT INVERTIBLE\n");
        return NULL;
    }
    inverted = get_new_matrix_n(n);
    while (++i < n)
    {
        j = -1;
        while (++j < n)
        {
            co = get_cofactor_n(matrix, i, j, n) ;
            inverted[j][i] = co / det;
        }
    }
    return inverted;
}


double **get_4_1_matrix(double x, double y, double z, double w)
{
    double **matrix;
    matrix = get_new_matrix_row_col(4, 1);
    matrix[0][0] = x;
    matrix[1][0] = y;
    matrix[2][0] = z;
    matrix[3][0] = w;
    return matrix;
}

double **from_n_to_4_1_matrix(double **matrix_n)
{
    double **matrix;
    matrix = get_new_matrix_row_col(4, 1);
    matrix[0][0] = matrix_n[0][0];
    matrix[1][0] = matrix_n[1][0];
    matrix[2][0] = matrix_n[2][0];
    matrix[3][0] = matrix_n[3][0];
    return matrix;
}

double **from_4_1_to_n_matrix(double **matrix_4_1)
{
    double **matrix;
    matrix = get_new_matrix_n(4);
    matrix[0][0] = matrix_4_1[0][0];
    matrix[1][0] = matrix_4_1[1][0];
    matrix[2][0] = matrix_4_1[2][0];
    matrix[3][0] = matrix_4_1[3][0];
    return matrix;
}

double **get_translation_matrix(double x, double y, double z)
{
    double **matrix;

    matrix = get_identity_matrix_n(4);
    matrix[0][3] = x;
    matrix[1][3] = y;
    matrix[2][3] = z;
    return matrix;
}

/* for a t_point  we will have 1 at the end [3][3] */
/* for a t_vector we will have 0 at the end [3][3] */
double **get_scaling_matrix(double x, double y, double z, double w)
{
    double **matrix;

    matrix = get_new_matrix_n(4);
    matrix[0][0] = x;
    matrix[1][1] = y;
    matrix[2][2] = z;
    matrix[3][3] = w;
    return matrix;
}

inline t_point translate_mx_to_point(double **m)
{
    t_point p;
    p.x = m[0][0];
    p.y = m[1][0];
    p.z = m[2][0];
    return p;
}

inline t_vector translate_mx_to_vector(double **m)
{
    t_vector v;
    v.x = m[0][0];
    v.y = m[1][0];
    v.z = m[2][0];
    return v;
}

double **rotate_x(double rad)
{
    double **matrix;

    matrix = get_identity_matrix_n(4);
    matrix[1][1] = cos(rad);
    matrix[1][2] = -sin(rad);
    matrix[2][1] = sin(rad);
    matrix[2][2] = cos(rad);
    return matrix;
}

double **rotate_y(double rad)
{
    double **matrix;

    matrix = get_identity_matrix_n(4);
    matrix[0][0] = cos(rad);
    matrix[0][2] = sin(rad);
    matrix[2][0] = -sin(rad);
    matrix[2][2] = cos(rad);
    return matrix;
}


double **rotate_z(double rad)
{
    double **matrix;

    matrix = get_identity_matrix_n(4);
    matrix[0][0] = cos(rad);
    matrix[0][1] = -sin(rad);
    matrix[1][0] = sin(rad);
    matrix[1][1] = cos(rad);
    return matrix;
}


t_ray transform_ray(t_ray old_r, double **transformation_mx)
{
    t_ray new_r;
    t_point ray_origin_res;
    t_vector ray_direction_res;
    double  **ray_matrix_origin;
    double  **ray_matrix_direction;
    double **origin_mul_res_matrix;
    double **direction_mul_res_matrix;

    if (!transformation_mx)
        return old_r;

    ray_matrix_origin = get_new_matrix_row_col(4, 1);
    ray_matrix_origin[0][0] = old_r.origin.x;
    ray_matrix_origin[1][0] = old_r.origin.y;
    ray_matrix_origin[2][0] = old_r.origin.z;
    ray_matrix_origin[3][0] = 1;

    origin_mul_res_matrix = mul_matrix_row_col(transformation_mx, ray_matrix_origin, 4, 1);
    ray_origin_res.x = origin_mul_res_matrix[0][0];
    ray_origin_res.y = origin_mul_res_matrix[1][0];
    ray_origin_res.z = origin_mul_res_matrix[2][0];


    ray_matrix_direction = get_new_matrix_row_col(4, 1);
    ray_matrix_direction[0][0] = old_r.direction.x;
    ray_matrix_direction[1][0] = old_r.direction.y;
    ray_matrix_direction[2][0] = old_r.direction.z;
    ray_matrix_direction[3][0] = 0;

    direction_mul_res_matrix = mul_matrix_row_col(transformation_mx, ray_matrix_direction, 4, 1);
    ray_direction_res.x = direction_mul_res_matrix[0][0];
    ray_direction_res.y = direction_mul_res_matrix[1][0];
    ray_direction_res.z = direction_mul_res_matrix[2][0];

    new_r.origin = ray_origin_res;
    new_r.direction = ray_direction_res;
    return new_r;
}

double **get_orientation_view_matrix(t_vector left, t_vector true_up, t_vector forward)
{
    double **vm = get_new_matrix_n(4);
    vm[0][0] = left.x;
    vm[0][1] = left.y;
    vm[0][2] = left.z;
    vm[0][3] = 0;

    vm[1][0] = true_up.x;
    vm[1][1] = true_up.y;
    vm[1][2] = true_up.z;
    vm[1][3] = 0;

    vm[2][0] = -forward.x;
    vm[2][1] = -forward.y;
    vm[2][2] = -forward.z;
    vm[2][3] = 0;

    vm[3][0] = 0;
    vm[3][1] = 0;
    vm[3][2] = 0;
    vm[3][3] = 1;

    return vm;
}

// double **get_view_matrix(t_point from, t_point to, t_vector up)
// {
//     double **orientation_mx;
//     double **view_mx;
//     t_vector forward;
//     double **transformation_mx;
//     t_vector left;
//     t_vector true_up;

//     // forwad ->   sub 'from' from 'to'    normalized
//     // forward = get_normalized(get_vector_2_pts(from, to));  
//     // left = cross_product(forward, up);
//     // true_up = cross_product(left, forward);
//     // orientation_mx = get_orientation_view_matrix(left, true_up, forward);
//     // transformation_mx = get_translation_matrix(-from.x, -from.y, -from.z);
//     view_mx = mul_matrix_n(orientation_mx, transformation_mx, 4);
//     return view_mx;
// }

t_sphere transform_sphere(t_sphere s, double **transformation_mx)
{
    t_sphere new_sphere;
    double  **sphere_matrix_origin;
    double **origin_mul_res_matrix;

  
    sphere_matrix_origin = get_new_matrix_row_col(4, 1);
    sphere_matrix_origin[0][0] = s.origin.x;
    sphere_matrix_origin[1][0] = s.origin.y;
    sphere_matrix_origin[2][0] = s.origin.z;
    sphere_matrix_origin[3][0] = 0;

    origin_mul_res_matrix = mul_matrix_row_col(transformation_mx, sphere_matrix_origin, 4, 1);
    new_sphere.origin.x = origin_mul_res_matrix[0][0];
    new_sphere.origin.y = origin_mul_res_matrix[1][0];
    new_sphere.origin.z = origin_mul_res_matrix[2][0];

    return new_sphere;
}