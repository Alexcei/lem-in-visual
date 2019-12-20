/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 18:20:35 by bpole             #+#    #+#             */
/*   Updated: 2019/12/19 18:20:40 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		put_pause(t_data *data)
{
	if (data->pause == 0)
		data->pause = 1;
	else
		data->pause = 0;
}

static void		speed_control(int key, t_data *data)
{
	if (key == NUM_PAD_PLUS)
	{
		if (data->speed == 0)
			data->speed = 0;
		else
			data->speed--;
	}
	if (key == NUM_PAD_MINUS)
		data->speed++;
}

int				lem_hook_keydown(int key, t_data *data)
{
	if (key == MAIN_PAD_ESC)
		exit(EXIT_SUCCESS);
	if (key == MAIN_PAD_P)
		put_pause(data);
	if (key == NUM_PAD_MINUS || key == NUM_PAD_PLUS)
		speed_control(key, data);
	if (key == ARROW_LEFT)
		data->camera->x_offset -= 10;
	else if (key == ARROW_RIGHT)
		data->camera->x_offset += 10;
	else if (key == ARROW_UP)
		data->camera->y_offset -= 10;
	else if (key == ARROW_DOWN)
		data->camera->y_offset += 10;
	lem_render(data);
	return (0);
}