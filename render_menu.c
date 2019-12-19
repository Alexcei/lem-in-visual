/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 18:32:37 by bpole             #+#    #+#             */
/*   Updated: 2019/12/19 18:33:01 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		render_background(t_data *data)
{
	int		i;

	i = 0;
	ft_bzero(data->data_addr, sizeof(char) * SIZE);
	while (i < SIZE)
		((int*)(data->data_addr))[i++] = BACKGROUND;
}

void		render_menu(t_data *data)
{
	mlx_string_put(data->mlx, data->win, 85, 20,
			TEXT_COLOR, "MENU");
	mlx_string_put(data->mlx, data->win, 65, 40,
			TEXT_COLOR, "Zoom - Scroll mouse");
	mlx_string_put(data->mlx, data->win, 65, 60,
			TEXT_COLOR, "Rotate - Press left mouse and move");
	mlx_string_put(data->mlx, data->win, 65, 80,
			TEXT_COLOR, "Move - Press right mouse and move");
	mlx_string_put(data->mlx, data->win, 65, 100,
			TEXT_COLOR, "Reset view - Press wheel mouse");
	mlx_string_put(data->mlx, data->win, 65, 120,
			TEXT_COLOR, "Pause - \"P\"");
}

void		get_dot(t_data *data, t_dot *dot, t_rooms *rooms)
{
	dot->x = rooms->x;
	dot->y = rooms->y;
	dot->z = rooms->z;
	*dot = transformations(*dot, data);
}
