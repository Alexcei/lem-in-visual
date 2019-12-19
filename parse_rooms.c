/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 00:56:56 by bpole             #+#    #+#             */
/*   Updated: 2019/12/19 00:57:04 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_rooms	*creat_room(t_lem *lem, char **str, int type)
{
	t_rooms		*new;

	(void)lem;
	if ((new = (t_rooms *)ft_memalloc(sizeof(t_rooms))) == NULL)
		ft_error("ERROR: of malloc");
	new->name = ft_strjoin("", str[0]);
	new->x = ft_atoi(str[1]);
	new->y = ft_atoi(str[2]);
	if (lem->v == 1)
		new->z = ft_atoi(str[3]);
	new->type = type;
	new->next = NULL;
	if (type == 1)
	{
		lem->start = new;
		new->bfs = 0;
	}
	else if (type == 2)
	{
		lem->end = new;
		new->bfs = INT_MAX;
	}
	else
		new->bfs = -1;
	return (new);
}

static void		add_room(t_lem *lem, int type)
{
	char		**str;
	t_rooms		*cpy;

	cpy = lem->rooms;
	if ((str = valid_rooms(lem)) == NULL)
		ft_error("ERROR: in room");
	lem->line = NULL;
	if (lem->rooms == NULL)
		lem->rooms = creat_room(lem, str, type);
	else
	{
		while (cpy->next != NULL)
			cpy = cpy->next;
		cpy->next = creat_room(lem, str, type);
	}
	ft_free_char_arr(&str);
}

static	void	add_start_end_room(t_lem *lem, int type)
{
	int			gnl;

	lem->line = NULL;
	gnl = ft_read_file(lem);
	if (!gnl)
		ft_error("ERROR: no line after start or end command");
	if (ft_hash(lem->line) == 0)
		add_room(lem, type);
	else
		ft_error("ERROR: in start or end room");
}

void			parse_rooms(t_lem *lem)
{
	int			type;
	char		**str;
	int			gnl;

	while ((gnl = ft_read_file(lem) > 0))
	{
		type = ft_hash(lem->line);
		if (type == -1 && ((str = valid_rooms(lem)) == NULL))
		{
			ft_free_char_arr(&str);
			lem->line = NULL;
			continue ;
		}
		else if (type == 1 || type == 2)
			add_start_end_room(lem, type);
		else if (type == 0 && ((str = valid_rooms(lem)) != NULL))
		{
			ft_free_char_arr(&str);
			add_room(lem, type);
		}
		else
			break ;
	}
	if (gnl <= 0)
		ft_error("ERROR: no links");
}
