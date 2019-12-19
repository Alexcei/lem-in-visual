/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 00:45:02 by bpole             #+#    #+#             */
/*   Updated: 2019/12/19 00:53:23 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			ft_bfs(t_lem *lem)
{
	t_connect	*queue;
	t_connect	*cur;
	t_connect	*tmp;

	queue = ft_connect_new(lem->start);
	while (queue)
	{
		cur = queue->rooms->connect;
		while (cur)
		{
			if (queue->rooms->bfs != INT_MAX && cur->rooms->bfs == -1)
			{
				cur->rooms->bfs = queue->rooms->bfs + 1;
				ft_connect_push_back(&queue->next, ft_connect_new(cur->rooms));
				if (cur->rooms->bfs > lem->max_bfs)
					lem->max_bfs = cur->rooms->bfs;
			}
			cur = cur->next;
		}
		tmp = queue;
		queue = queue->next;
		ft_memdel((void*)&tmp);
		if (lem->max_bfs == -1)
			ft_error("ERROR: no way");
	}
}
