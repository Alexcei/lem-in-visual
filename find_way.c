/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 00:45:27 by bpole             #+#    #+#             */
/*   Updated: 2019/12/19 00:53:34 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		way_push_back(t_way **begin_list, t_way *new)
{
	t_way		*last;

	if (!*begin_list)
	{
		*begin_list = new;
		return ;
	}
	last = *begin_list;
	while (last->next)
		last = last->next;
	last->next = new;
}

static void		del_one_con(t_connect **root_con, t_rooms *room)
{
	t_connect	*connect;

	connect = *root_con;
	if (root_con && *root_con && room)
	{
		*root_con = (*root_con)->next;
		free(connect);
	}
}

static int		get_way(t_connect **root_con, t_rooms *room)
{
	t_connect	*connect;

	if (room->bfs == 0)
		return (1);
	connect = room->connect;
	ft_connect_add(root_con, ft_connect_new(room));
	while (connect)
	{
		if (!connect->rooms->used && connect->rooms->bfs < room->bfs)
		{
			room->used = 1;
			if (get_way(root_con, connect->rooms))
				return (1);
		}
		connect = connect->next;
	}
	del_one_con(root_con, room);
	return (0);
}

static t_way	*creat_way(t_rooms *room)
{
	t_connect	*connect;
	t_way		*way;

	connect = NULL;
	if (room->bfs < 1 || !get_way(&connect, room))
		return (NULL);
	way = (t_way*)ft_memalloc(sizeof(t_way));
	way->connect = connect;
	way->count = room->bfs + 1;
	return (way);
}

void			find_way(t_lem *lem)
{
	t_connect	*connect;
	t_way		*way;

	connect = lem->end->connect;
	ft_connect_sort(&connect);
	while (connect)
	{
		way = creat_way(connect->rooms);
		if (way)
			way_push_back(&lem->way, way);
		connect = connect->next;
	}
}
