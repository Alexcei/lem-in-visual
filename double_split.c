#include "lem_visual.h"

static size_t	ft_word_count2(char const *str, char c1, char c2)
{
	size_t		tr;
	size_t		res;

	tr = 0;
	res = 0;
	while (*str)
	{
		if (*str != c1 && *str != c2 && tr == 0)
			res++;
		tr = (*str != c1 && *str != c2 ? 1 : 0);
		str++;
	}
	return (res);
}

static void		ft_free_words(char **arr, size_t i)
{
	while (i--)
		ft_strdel(&arr[i]);
	free(arr);
}

static size_t	ft_word_len(char const *str, char c1, char c2)
{
	size_t		res;

	res = 0;
	while (*str && *str != c1 && *str != c2)
	{
		str++;
		res++;
	}
	return (res);
}

static char		**ft_full_arr(char **arr, const char *s, char c1, char c2)
{
	size_t		i;
	size_t		tr;
	size_t		len_word;
	char		*word;

	i = 0;
	tr = 0;
	while (*s)
	{
		if (*s != c1 && *s != c2 && tr == 0)
		{
			len_word = ft_word_len(s, c1, c2);
			word = ft_strncpy(ft_strnew(len_word), s, len_word);
			if (!word)
			{
				ft_free_words(arr, i);
				return (NULL);
			}
			arr[i++] = word;
		}
		tr = (*s != c1 && *s != c2 ? 1 : 0);
		s++;
	}
	return (arr);
}

char			**ft_double_split(char const *s, char c1, char c2)
{
	char		**arr;
	size_t		i;

	if (!s)
		return (NULL);
	i = ft_word_count2(s, c1, c2);
	if (i + 1 == 0)
		return (NULL);
	arr = (char**)malloc(sizeof(char*) * (i + 1));
	if (!arr)
		return (NULL);
	arr[i] = NULL;
	if (!ft_full_arr(arr, s, c1, c2))
		return (NULL);
	return (arr);
}