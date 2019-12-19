/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 00:38:22 by bpole             #+#    #+#             */
/*   Updated: 2019/12/19 18:18:52 by bpole            ###   ########.fr       */
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

void			ft_ant_moves(t_data *data)
{
	while (data->lem->end->number_ant < data->lem->ants)
	{
		data->lem->space = 1;
		ft_ant_moves_in_rooms(data->lem);
		ant_moves(data->lem);
		ft_printf("\n");
	}
}

int				lem_loop_key_hook(t_data *data)
{
	char		*str;
	static int	i;

	if (i > data->speed)
		i = 0;
	else
		i++;
	if (!i && data->pause == 1 && data->lem->end->number_ant < data->lem->ants)
	{
		data->lem->space = 1;
		ft_ant_moves_in_rooms(data->lem);
		ant_moves(data->lem);
		ft_printf("\n");
	}
	lem_render(data);
	if (data->pause == 0)
	{
		str = "PAUSE";
		mlx_string_put(data->mlx, data->win,
				(WIDTH / 5) - 10, (HEIGHT / 2) - 10, 0x0FFFFFF, str);
	}
	return (0);
}
