#include "lem_in.h"

static void		render_background(t_data *data)
{
	int 		i;

	i = 0;
	ft_bzero(data->data_addr, sizeof(char) * SIZE);
	while (i < SIZE)
		((int*)(data->data_addr))[i++] = BACKGROUND;
}

static void		init_dot_c_d(int i, t_dot *dot_c, t_dot *dot_d, t_data *data)
{
	if (i + data->width < data->size)
		*dot_c = transformations(data->dot[i + data->width], data);
	if (i + data->width + 1 < data->size)
		*dot_d = transformations(data->dot[i + data->width + 1], data);
}

static void		render_map(t_data *data)
{
	t_dot		dots[4];
	int 		i;

	i = -1;
	while (++i < data->size)
	{
		dots[0] = transformations(data->dot[i], data);
		if (i + 1 < data->size)
			dots[1] = transformations(data->dot[i + 1], data);
		init_dot_c_d(i, &dots[2], &dots[3], data);
		if ((i + 1) % data->width != 0)
		{
			if (dots[0].color && data->camera->polygon &&
				i / data->width != data->height - 1)
			{
				data->color_tmp = dots[0].color;
				render_plane(dots[0], dots[1], dots[2], data);
				render_plane(dots[1], dots[2], dots[3], data);
			}
			render_line(dots[0], dots[1], data);
		}
		if (i / data->width != data->height - 1)
			render_line(dots[0], dots[2], data);
	}
}

static void		render_menu(t_data *data)
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

void			fdf_render(t_data *data)
{
	render_background(data);
	render_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	render_menu(data);
}