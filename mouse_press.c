/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 18:29:08 by bpole             #+#    #+#             */
/*   Updated: 2019/12/19 18:29:52 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		zoom(int key, t_data *data)
{
	if (key == NUM_PAD_PLUS ||
			key == MAIN_PAD_PLUS ||
			key == MOUSE_SCROLL_UP)
		data->camera->zoom++;
	else if (key == NUM_PAD_MINUS ||
			key == MAIN_PAD_MINUS ||
			key == MOUSE_SCROLL_DOWN)
		data->camera->zoom--;
	if (data->camera->zoom < 1)
		data->camera->zoom = 1;
}

static void		view_up(t_data *data)
{
	data->camera->x_offset = WIDTH / 2;
	data->camera->y_offset = HEIGHT / 2;
	data->camera->zoom = FT_MIN(WIDTH / data->width / 2,
			HEIGHT / data->height / 2);
	data->camera->alpha = 0;
	data->camera->beta = 0;
}

int				lem_mouse_press(int button, int x, int y, void *param)
{
	t_data		*data;

	(void)x;
	(void)y;
	data = (t_data *)param;
	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
		zoom(button, data);
	else if (button == MOUSE_LEFT_BUTTON)
		data->mouse->put_left = 1;
	else if (button == MOUSE_RIGHT_BUTTON)
		data->mouse->put_right = 1;
	else if (button == MOUSE_THREE_BUTTON)
		view_up(data);
	return (0);
}

int				lem_mouse_release(int button, int x, int y, void *param)
{
	t_data		*data;

	(void)x;
	(void)y;
	(void)button;
	data = (t_data *)param;
	data->mouse->put_left = 0;
	data->mouse->put_right = 0;
	return (0);
}

int				lem_mouse_move(int x, int y, void *param)
{
	t_data		*data;

	data = (t_data *)param;
	data->mouse->previous_x = data->mouse->x;
	data->mouse->previous_y = data->mouse->y;
	data->mouse->x = x;
	data->mouse->y = y;
	if (data->mouse->put_left)
	{
		data->camera->beta += (x - data->mouse->previous_x) * 0.002;
		data->camera->alpha -= (y - data->mouse->previous_y) * 0.002;
	}
	if (data->mouse->put_right)
	{
		data->camera->x_offset += x - data->mouse->previous_x;
		data->camera->y_offset += y - data->mouse->previous_y;
	}
	return (0);
}
