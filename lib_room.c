/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 00:54:44 by bpole             #+#    #+#             */
/*   Updated: 2019/12/19 00:55:17 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_save			*ft_save_new(char *content)
{
	t_save	*res;

	if (!(res = (t_save*)ft_memalloc(sizeof(t_save))))
		return (NULL);
	res->content = content;
	res->next = NULL;
	return (res);
}

void			ft_save_push_back(t_save **begin_list, t_save *new)
{
	t_save		*last;

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

int				ft_find_fork_out(t_rooms *room)
{
	t_connect	*connect;

	if (room->bfs == 0)
		return (0);
	if (room->out > 2)
	{
		room->out--;
		return (1);
	}
	connect = room->connect;
	while (connect && room->bfs >= connect->rooms->bfs)
	{
		if (ft_find_fork_out(connect->rooms))
			return (1);
		connect = connect->next;
	}
	return (0);
}
