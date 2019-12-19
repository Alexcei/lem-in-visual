#include "lem_in.h"

static void		zoom_down(t_data *data)
{
	data->camera->zoom  -= 1;
	if (data->camera->zoom  < 1)
		data->camera->zoom = 1;
}

static void		put_pause(t_data *data)
{
	if (data->pause == 0)
		data->pause = 1;
	else
		data->pause = 0;
}

static void		polygon_up(t_data *data)
{
	if (!data->camera->polygon)
		data->camera->polygon++;
	else
		data->camera->polygon--;
}

int				lem_hook_keydown(int key, t_data *data)
{
	if (key == MAIN_PAD_ESC)
		exit(EXIT_SUCCESS);
	if (key == MAIN_PAD_P)
		put_pause(data);
	if (key == MAIN_PAD_G)
		polygon_up(data);
	if (key == NUM_PAD_MINUS)
		zoom_down(data);
	if (key == NUM_PAD_PLUS)
		data->camera->zoom  += 1;
	if (key == ARROW_LEFT)
		data->camera->x_offset -= 10;
	else if (key == ARROW_RIGHT)
		data->camera->x_offset += 10;
	else if (key == ARROW_UP)
		data->camera->y_offset -= 10;
	else if (key == ARROW_DOWN)
		data->camera->y_offset += 10;
	fdf_render(data);
	return (0);
}