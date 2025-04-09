/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_libs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:26:09 by sgouzi            #+#    #+#             */
/*   Updated: 2025/04/09 18:01:20 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_LIBS_H
# define MATH_LIBS_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}			t_vec;

typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;
}			t_ray;

#endif