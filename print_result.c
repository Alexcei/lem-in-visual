/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 00:35:11 by bpole             #+#    #+#             */
/*   Updated: 2019/12/19 16:40:36 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			ft_print_save(t_lem *lem)
{
	t_save		*save;
	t_save		*tmp;

	save = lem->save;
	while (save)
	{
		ft_printf("%s\n", save->content);
		if (save->content)
			ft_strdel(&save->content);
		tmp = save;
		save = save->next;
		ft_memdel((void*)&tmp);
	}
	ft_printf("\n");
}

static void		print_moves(t_lem *lem, t_connect *clone)
{
	if (clone->next && clone->next->rooms->number_ant)
	{
		if (lem->space)
			lem->space = 0;
		else
			ft_printf(" ");
		ft_printf("L%d-%s", clone->next->rooms->number_ant,
				clone->rooms->name);
		clone->rooms->number_ant = clone->next->rooms->number_ant;
		clone->next->rooms->number_ant = 0;
	}
}

void			ft_ant_moves_in_rooms(t_lem *lem)
{
	t_connect	*clone;
	t_way		*way;

	way = lem->way;
	while (way)
	{
		clone = way->clone;
		if (clone->rooms->number_ant)
		{
			if (lem->space)
				lem->space = 0;
			else
				ft_printf(" ");
			ft_printf("L%d-%s", clone->rooms->number_ant, lem->end->name);
			lem->end->number_ant++;
			clone->rooms->number_ant = 0;
		}
		while (clone)
		{
			print_moves(lem, clone);
			clone = clone->next;
		}
		way = way->next;
	}
}
