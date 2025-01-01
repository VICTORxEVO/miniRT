/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memo1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchikhi <abchikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 02:09:24 by sgouzi            #+#    #+#             */
/*   Updated: 2024/09/16 00:26:04 by abchikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	if (dst == src)
		return (dst);
	i = 0;
	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

void	ft_bzero(void *s, size_t n)
{
    size_t			i;
	unsigned char	*ptr;

	ptr = s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

void	add_front_gc(t_data *d, void *ptr)
{
	d->gc = malloc(sizeof(t_gc));
	if (!d->gc)
		(free(ptr), gc_void(d), exit(1));
	d->gc->ptr = ptr;
	d->gc->next = NULL;
}

void	*gc_malloc(t_data *d, size_t size)
{
	void	*ptr;
	t_gc	*gc;

	ptr = malloc(size + 1);
	if (!ptr)
		(gc_void(d), exit(1));
	ft_bzero(ptr, size + 1);
	if (!d->gc)
		add_front_gc(d, ptr);
	else
	{
		gc = d->gc;
		while (gc->next)
			gc = gc->next;
		gc->next = malloc(sizeof(t_gc));
		if (!gc->next)
		{
			gc->next = NULL;
			(free(ptr), gc_void(d), exit(1));
		}
		gc->next->ptr = ptr;
		gc->next->next = NULL;
	}
	return (ptr);
}

void	free_array(t_data *d, char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		gc_free(d, array[i]);
		i++;
	}
	gc_free(d, array);
}

void	gc_void(t_data *d)
{
	t_gc	*gc;

	while (d->gc)
	{
		gc = d->gc;
		d->gc = d->gc->next;
		free(gc->ptr);
		free(gc);
	}
	d->gc = NULL;
}

void	*gc_realloc(t_data *d, void *ptr, size_t old_size, size_t new_size)
{
	t_gc	*gc;
	void	*new_ptr;

	gc = d->gc;
	while (gc)
	{
		if (gc->ptr == ptr)
		{
			new_ptr = malloc(new_size);
			if (!new_ptr)
			{
				gc_void(d);
				exit(1);
			}
			ft_bzero(new_ptr, new_size);
			ft_memcpy(new_ptr, ptr, old_size);
			free(ptr);
			gc->ptr = new_ptr;
			return (new_ptr);
		}
		gc = gc->next;
	}
	return (NULL);
}

void	gc_free(t_data *d, void *ptr)
{
	t_gc	*gc;
	t_gc	*prev;

	gc = d->gc;
	prev = NULL;
	while (gc)
	{
		if (gc->ptr == ptr)
		{
			if (prev)
				prev->next = gc->next;
			else
				d->gc = gc->next;
			free(gc->ptr);
			free(gc);
			return ;
		}
		prev = gc;
		gc = gc->next;
	}
}