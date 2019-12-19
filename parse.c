/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtorwold <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 16:04:04 by wtorwold          #+#    #+#             */
/*   Updated: 2019/12/19 00:56:03 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				ft_read_file(t_lem *lem)
{
	int			gnl;

	if ((gnl = get_next_line(lem->fd, &lem->line)) == -1)
		ft_error("ERROR: reading");
	if (gnl)
		ft_save_push_back(&lem->save, ft_save_new(lem->line));
	return (gnl);
}

static void		parse_ants(t_lem *lem)
{
	int			i;
	int			num;

	i = 0;
	if (lem->line[i] == '+')
		i++;
	while (lem->line[i])
	{
		if (ft_isdigit(lem->line[i]))
			i++;
		else
			ft_error("ERROR: ant");
	}
	num = ft_atoi(lem->line);
	lem->line = NULL;
	if (num <= 0 || i > 10)
		ft_error("ERROR: ant");
	lem->ants = num;
}

int				ft_hash(char *line)
{
	if (ft_strcmp(line, "##start") == 0)
		return (1);
	else if (ft_strcmp(line, "##end") == 0)
		return (2);
	else if (line[0] == '#' || (line[0] == '#' && line[1] == '#'))
		return (-1);
	else
		return (0);
}

void			ft_parse_file(t_lem *lem)
{
	if (!ft_read_file(lem))
		ft_error("ERROR: first line is empty");
	parse_ants(lem);
	parse_rooms(lem);
	valid_rooms2(lem);
	parse_links(lem);
}
