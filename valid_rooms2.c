/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtorwold <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 18:24:02 by wtorwold          #+#    #+#             */
/*   Updated: 2019/12/19 20:44:07 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		check_star_end(t_lem *lem_in)
{
	int			start;
	int			end;
	t_rooms		*temp;

	temp = lem_in->rooms;
	start = 0;
	end = 0;
	while (temp)
	{
		if (temp->type == 1)
			start++;
		if (temp->type == 2)
			end++;
		temp = temp->next;
	}
	if (start < 1 || end < 1)
		ft_error("ERROR: in rooms");
	if (start > 1 || end > 1)
		ft_error("ERROR: too much start or end");
}

static void		check_coords(t_lem *lem_in)
{
	int			x;
	int			y;
	int			i;
	t_rooms		*temp;
	t_rooms		*cpy;

	cpy = lem_in->rooms;
	while (cpy)
	{
		i = 0;
		temp = lem_in->rooms;
		x = cpy->x;
		y = cpy->y;
		while (temp)
		{
			if (temp->x == x && temp->y == y)
				i++;
			temp = temp->next;
		}
		if (i > 1)
			ft_error("ERROR: duplicate coords");
		cpy = cpy->next;
	}
}

static void		check_name(t_lem *lem)
{
	char		*str;
	int			i;
	t_rooms		*temp;
	t_rooms		*cpy;

	cpy = lem->rooms;
	while (cpy)
	{
		i = 0;
		temp = lem->rooms;
		str = cpy->name;
		while (temp)
		{
			if (ft_strcmp(str, temp->name) == 0)
				i++;
			temp = temp->next;
		}
		if (i > 1)
			ft_error("ERROR: duplicate name");
		cpy = cpy->next;
	}
}

void			valid_rooms2(t_lem *lem_in)
{
	check_star_end(lem_in);
	check_coords(lem_in);
	check_name(lem_in);
}
