/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 09:39:33 by ysbai-jo          #+#    #+#             */
/*   Updated: 2025/04/11 09:47:19 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	validated_type(char *name, unsigned int args_count)
{
	if ((!ft_strcmp(name, "A") && args_count == e_ambient) || (!ft_strcmp(name,
				"C") && args_count == e_color) || (!ft_strcmp(name, "L")
			&& args_count == e_light) || (!ft_strcmp(name, "pl")
			&& args_count == e_plain) || (!ft_strcmp(name, "sp")
			&& args_count == e_sphere) || (!ft_strcmp(name, "cy")
			&& args_count == e_cylinder))
		return (true);
	return (false);
}

bool	starts_with(char *s, char *start)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] && start[i] && start[i] == s[i])
	{
		if (s[i] != start[j])
			return (false);
		i++;
		j++;
	}
	if (i != j)
		return (false);
	if (start[j])
		return (false);
	return (true);
}

void	loadline(char *line, int n_line, char *filename)
{
	char			**words;
	unsigned int	args_count;

	if (is_wspace(line) || starts_with(line, "#"))
		return ;
	words = ft_split(line, " \n\v\t");
	args_count = count_args(words);
	if (args_count < 1)
		pexit(err_msg(filename, n_line), 3);
	if (!validated_type(words[0], args_count))
		pexit(ft_strjoin("unknown type  -> ", words[0]), 1);
	if (!elem_added(getengine(), words))
		pexit("error !", 1);
}
