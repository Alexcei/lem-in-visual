/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 00:57:49 by bpole             #+#    #+#             */
/*   Updated: 2019/12/19 00:57:59 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				lem_close(void *data)
{
	(void)data;
	exit(EXIT_SUCCESS);
}

void			ft_error(char *message)
{
	ft_putendl_fd(message, 2);
	exit(EXIT_FAILURE);
}

void			ft_free_char_arr(char ***arr)
{
	int			i;

	i = 0;
	if (*arr)
	{
		while ((*arr)[i])
			ft_strdel(&((*arr)[i++]));
		free(*arr);
		*arr = NULL;
	}
}

void			ft_swap(void **a, void **b)
{
	void		*tmp_a;

	tmp_a = *a;
	*a = *b;
	*b = tmp_a;
}

int				check_start_end(t_lem *lem)
{
	t_connect	*connect;

	connect = lem->start->connect;
	while (connect)
	{
		if (connect->rooms->bfs == INT_MAX)
			return (1);
		connect = connect->next;
	}
	return (0);
}