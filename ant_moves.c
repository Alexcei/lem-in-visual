/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 00:38:22 by bpole             #+#    #+#             */
/*   Updated: 2019/12/19 00:53:10 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		ant_moves_from_start(t_lem *lem, t_way *way)
{
	if (lem->start->number_ant && !way->connect->rooms->number_ant)
	{
		lem->start->number_ant--;
		way->connect->rooms->number_ant = lem->ants - lem->start->number_ant;
		if (lem->space)
			lem->space = 0;
		else
			ft_printf(" ");
		ft_printf("L%d-%s", way->connect->rooms->number_ant,
				way->connect->rooms->name);
	}
}

static int		get_count_ant_in_way(t_lem *lem, int i, int count)
{
	t_way		*way;
	int			res;

	res = 0;
	way = lem->way;
	while (i && way)
	{
		res += count - way->count;
		way = way->next;
		i--;
	}
	return (res);
}

static void		ant_moves(t_lem *lem)
{
	t_way		*way;
	int			i;

	i = 0;
	way = lem->way;
	while (way)
	{
		if (lem->start->number_ant > get_count_ant_in_way(lem, i, way->count))
			ant_moves_from_start(lem, way);
		way = way->next;
		i++;
	}
}

static void		make_clone(t_lem *lem)
{
	t_way		*way;
	t_connect	*connect;

	way = lem->way;
	while (way)
	{
		connect = way->connect;
		while (connect)
		{
			ft_connect_add(&way->clone, ft_connect_new(connect->rooms));
			connect = connect->next;
		}
		way = way->next;
	}
}

void			ft_ant_moves(t_lem *lem)
{
	int			step;

	step = 0;
	lem->start->number_ant = lem->ants;
	make_clone(lem);
	while (lem->end->number_ant < lem->ants)
	{
		step++;
		lem->space = 1;
		ft_ant_moves_in_rooms(lem);
		ant_moves(lem);
		ft_printf("\n");
	}
}
