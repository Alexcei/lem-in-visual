/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 00:46:14 by bpole             #+#    #+#             */
/*   Updated: 2019/12/19 00:53:49 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			free_connect(t_connect *connect)
{
	t_connect	*tmp;

	while (connect)
	{
		tmp = connect;
		connect = connect->next;
		ft_memdel((void*)&tmp);
	}
}

static void		free_rooms(t_rooms *rooms)
{
	t_rooms		*tmp_rooms;

	if (!rooms)
		return ;
	while (rooms)
	{
		tmp_rooms = rooms;
		if (tmp_rooms->name)
			ft_strdel(&tmp_rooms->name);
		if (tmp_rooms->name)
			ft_strdel(&tmp_rooms->name);
		if (tmp_rooms->connect)
			free_connect(tmp_rooms->connect);
		rooms = rooms->next;
		ft_memdel((void*)&tmp_rooms);
	}
}

void			free_ways(t_way *way)
{
	t_way		*temp_way;

	while (way)
	{
		free_connect(way->clone);
		free_connect(way->connect);
		temp_way = way;
		way = way->next;
		ft_memdel((void*)&temp_way);
	}
}

void			ft_free_links(t_links *links)
{
	t_links		*temp;
	t_links		*cpy;

	temp = links;
	while (temp)
	{
		cpy = temp;
		temp = temp->next;
		ft_memdel((void*)&cpy->begin);
		ft_memdel((void*)&cpy->finish);
		ft_memdel((void*)&cpy);
	}
}

void			free_all(t_lem *lem)
{
	if (lem->way)
		free_ways(lem->way);
	if (lem->rooms)
		free_rooms(lem->rooms);
	if (lem->arr)
		ft_free_char_arr(&lem->arr);
	if (lem->links)
		ft_free_links(lem->links);
}
