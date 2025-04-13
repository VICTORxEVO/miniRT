/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:24:57 by ysbai-jo          #+#    #+#             */
/*   Updated: 2025/04/13 18:21:11 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef unsigned char	t_uc;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char					*handle_it(char **q_res, int nl_ind);
char					*get_next_line(int fd);
char					*get_last_line(char **q_res);
int						check_nl(char *str);
char					*ft_gstrjoin(char **s1, char const *s2, int rd);
void					*free_all(char **q_res, char **buff);

#endif
