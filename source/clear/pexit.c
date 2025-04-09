/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pexit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:44:29 by ysbai-jo          #+#    #+#             */
/*   Updated: 2025/01/04 18:41:43 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	pexit(char *msg, short int exit_code)
{
	ft_putstr_fd(PRGM_NAME ":"
							" ",
					2);
	if (msg[ft_strlen(msg) - 1] == '!' || msg[ft_strlen(msg) - 1] == '>')
	{
		(ft_putstr_fd(msg, 2), ft_putstr_fd("\n", 2));
	}
	else
		perror(msg);
	ft_putstr_fd(END, 2);
	clear();
	exit(exit_code);
}
