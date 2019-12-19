/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtorwold <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 16:04:04 by wtorwold          #+#    #+#             */
/*   Updated: 2019/12/19 18:31:08 by bpole            ###   ########.fr       */
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

static void		count_size(t_data *data)
{
	data->width = data->lem->max_x - data->lem->min_x;
	data->height = data->lem->max_y - data->lem->min_y;
	data->camera->zoom = FT_MIN(WIDTH / data->width / 2,
			HEIGHT / data->height / 2);
}

void			ft_parse_file(t_data *data)
{
	if (!ft_read_file(data->lem))
		ft_error("ERROR: first line is empty");
	parse_ants(data->lem);
	parse_rooms(data->lem);
	valid_rooms2(data->lem);
	parse_links(data->lem);
	if (data->lem->v)
		count_size(data);
}
