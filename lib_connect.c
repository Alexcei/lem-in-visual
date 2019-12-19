/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_connect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 22:40:55 by bpole             #+#    #+#             */
/*   Updated: 2019/12/19 00:54:18 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_connect		*ft_connect_new(t_rooms *rooms)
{
	t_connect	*res;

	if (!(res = (t_connect*)ft_memalloc(sizeof(t_connect))))
		return (NULL);
	res->rooms = rooms;
	res->next = NULL;
	return (res);
}

void			ft_connect_push_back(t_connect **begin_list, t_connect *new)
{
	t_connect	*last;

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

void			ft_connect_add(t_connect **alst, t_connect *new)
{
	if (alst && new)
	{
		if (*alst)
		{
			new->next = *alst;
			*alst = new;
		}
		else
			*alst = new;
	}
}

void			ft_connect_sort(t_connect **begin_list)
{
	t_connect	*current;
	int			tr;

	tr = 1;
	while (tr--)
	{
		current = *begin_list;
		while (current && current->next)
		{
			if (current->rooms->bfs > current->next->rooms->bfs)
			{
				ft_swap((void*)&current->rooms, (void*)&current->next->rooms);
				tr = 1;
			}
			current = current->next;
		}
	}
}
