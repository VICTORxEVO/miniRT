/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_libs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:43:37 by ysbai-jo          #+#    #+#             */
/*   Updated: 2025/04/13 21:08:18 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**

	* @details this header adds external libs like stdlib
	and also  same of libft functions
 */
#ifndef EXT_LIBS_H
# define EXT_LIBS_H

# ifdef USER
#  if USER == sgouzi
#   include "mlx.h"
#  else
#   include <mlx.h>
#  endif
# else
#  include <mlx.h>
# endif
# define _POSIX_C_SOURCE 200809L
# include "get_next_line.h"
# include "math_libs.h"
# include <X11/X.h>
# include <X11/XKBlib.h>
# include <X11/keysym.h>
# include <assert.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <math.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

typedef unsigned char	t_uc;
// just a macro that i used in libft to avoid long line on norminette ;)

int						ft_toupper(int x);
int						ft_tolower(int x);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					*ft_strtrim(char const *s1, char const *set);
char					*ft_strrchr(const char *str, int c);
char					*ft_strnstr(const char *big, const char *little,
							size_t len);
int						ft_strncmp(const char *str1, const char *str2,
							ssize_t n);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strmapi(char const *s, char (*f)(unsigned int,
								char));
size_t					ft_strlen(const char *str);
size_t					ft_strlcpy(char *dest, const char *src, size_t size);
size_t					ft_strlcat(char *dest, const char *src, size_t size);
char					*ft_strjoin(char const *s1, char const *s2);
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
char					*ft_strdup(const char *s);
char					*ft_strchr(const char *str, int c);
char					**ft_split(const char *s, char *c);
char					**ft_split_path(const char *s, char c);
void					*ft_memmove(void *dest, const void *src, size_t count);
void					*ft_memcpy(void *dest, const void *src, size_t n);
int						ft_memcmp(const void *str1, const void *str2, size_t n);
void					*ft_memchr(const void *str, int c, size_t n);
char					*ft_itoa(int n);
int						ft_isdigit(int x);
int						ft_isascii(int x);
int						ft_isalpha(int x);
int						ft_isalnum(int x);
void					ft_bzero(void *s, size_t n);
long					ft_atoi(const char *str, bool *err);
void					ft_putstr_fd(char *s, int fd);
int						ft_isprint(int c);
void					*ft_calloc(size_t n, size_t size);
void					ft_bzero(void *s, size_t n);
char					*ft_strtrim(char const *s1, char const *set);
char					*ft_strjoin_m(char const *s1, char const *s2);

#endif
