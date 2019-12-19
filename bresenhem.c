#include "lem_in.h"

static void		paint_point(int x, int y, t_data *data, int color_default)
{
	int			i;

	(void)color_default;
	i = x + y * WIDTH;
	if (0 < x && x < WIDTH && 0 < y && y < HEIGHT)
		((int *)(data->data_addr))[i] = FDF;
}

void			render_line(t_dot a, t_dot b, t_data *data)
{
	double		x_step;
	double		y_step;
	int 		max;

	x_step = b.x - a.x;
	y_step = b.y - a.y;
	max = MAX(MOD(x_step), MOD(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(a.x - b.x) || (int)(a.y - b.y))
	{
		paint_point((int)a.x, (int)a.y, data, a.color);
		a.x += x_step;
		a.y += y_step;
	}
}

static void		paint_plane(int x, int y, t_data *data, int color_default)
{
	int			i;

	i = x + y * WIDTH;
	if (0 < x && x < WIDTH && 0 < y && y < HEIGHT)
	{
		((int *)(data->data_addr))[i] = color_default;
	}
}

static void		render_line_plane(t_dot a, t_dot b, t_data *data)
{
	double 		x_step;
	double 		y_step;
	int 		max;

	x_step = b.x - a.x;
	y_step = b.y - a.y;
	max = MAX(MOD(x_step), MOD(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(a.x - b.x) || (int)(a.y - b.y))
	{
		paint_plane((int)a.x, (int)a.y, data, data->color_tmp);
		a.x += x_step;
		a.y += y_step;
	}
}

void			render_plane(t_dot a, t_dot b, t_dot c, t_data *data)
{
	double		x_step;
	double		y_step;
	int			max;

	x_step = b.x - a.x;
	y_step = b.y - a.y;
	max = MAX(MOD(x_step), MOD(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(a.x - b.x) || (int)(a.y - b.y))
	{
		render_line_plane(a, c, data);
		a.x += x_step;
		a.y += y_step;
	}
}