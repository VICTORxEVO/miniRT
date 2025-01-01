#include "miniRT.h"

char	*ft_strdup(t_data *d, char *s1)
{
	const char	*clone;
	int			len_;

	if (s1 == NULL)
		return (NULL);
	len_ = (int)ft_strlen(s1);
	clone = gc_malloc(d, sizeof(char) * (len_ + 1));
	if (!clone)
		return (NULL);
	ft_memcpy((void *)clone, s1, len_ + 1);
	return ((char *)clone);
}

char	*ft_substr(t_data *d, char *s, unsigned int start, size_t len_)
{
	char	*substring;
	size_t	str_len;

	if (!s)
		return (NULL);
	str_len = (int)ft_strlen(s);
	if (start > str_len || *s == '\0')
		return (ft_strdup(d, ""));
	if (len_ > str_len - start)
		len_ = str_len - start;
	substring = gc_malloc(d, sizeof(char) * (len_ + 1));
	if (!substring)
		return (NULL);
	ft_memcpy(substring, s + start, len_);
	substring[len_] = '\0';
	return (substring);
}

int	count_words(char const *s1, char c)
{
	int	count;

	count = 0;
	while (*s1)
	{
		if (*s1 == '\0')
			return (count);
		else if (*s1 && *s1 == c)
		{
			while (*s1 && *s1 == c)
				(s1)++;
		}
		else if (*s1)
		{
			count++;
			while (*s1 && *s1 != c)
				s1++;
		}
	}
	return (count);
}

char	**ft_split(t_data *d, char *s, char c)
{
	int		w;
	char	**res;
	int		i;
	int		j;

	i = 0;
	res = ((char **)gc_malloc(d, (count_words(s, c) + 1) * sizeof(char *)));
	w = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		j = 0;
		while (s[i] && s[i] != c && ++j)
			i++;
		res[w++] = ft_substr(d, s, i - j, j);
	}
	res[w] = 0;
	return (res);
}