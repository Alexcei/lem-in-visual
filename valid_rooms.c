/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 00:58:56 by bpole             #+#    #+#             */
/*   Updated: 2019/12/19 00:59:07 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		check_l_or_hash_in_name(char c)
{
	if (c == 'L')
		ft_error("ERROR: Name begins whith L");
	if (c == '#')
		ft_error("ERROR: Name begins whith #");
}

static int		valid_rooms_while(char **str, int i, int j)
{
	int			c;

	c = i;
	while (j < c)
	{
		i = 0;
		while (str[j][i])
		{
			if (ft_isdigit(str[j][i]) || str[j][0] == '-')
				i++;
			else
			{
				ft_free_char_arr(&str);
				return (0);
			}
		}
		j++;
	}
	return (1);
}

char			**valid_rooms(t_lem *lem)
{
	char		**str;
	int			i;
	int			j;

	i = 0;
	j = 1;
	str = ft_strsplit(lem->line, ' ');
	while (str[i] != NULL)
		i++;
	if (i != 3 && lem->v == 0)
	{
		ft_free_char_arr(&str);
		return (NULL);
	}
	else if (i != 4 && lem->v == 1)
	{
		ft_free_char_arr(&str);
		return (NULL);
	}
	if (!valid_rooms_while(str, i, j))
		return (NULL);
	check_l_or_hash_in_name(str[0][0]);
	return (str);
}
