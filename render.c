#include "lem_in.h"

static void		render_connect(t_data *data)
{
	t_connect *connect;
	t_rooms *rooms;
	t_dot dots[2];

	rooms = data->lem->rooms;
	while (rooms)
	{
		connect = rooms->connect;
		while (connect)
		{
			get_dot(data, &dots[0], rooms);
			get_dot(data, &dots[1], connect->rooms);
			render_line(dots[0], dots[1], data, GRAF);
			connect = connect->next;
		}
		rooms = rooms->next;
	}
}

static void		render_way(t_data *data)
{
	t_way		*way;
	t_connect	*connect;
	t_dot 		dots[2];

	way = data->lem->way;
	while (way)
	{
		connect = way->connect;
		get_dot(data, &dots[0], data->lem->start);
		get_dot(data, &dots[1], connect->rooms);
		render_line(dots[0], dots[1], data, WAY);
		while (connect)
		{
			get_dot(data, &dots[0], connect->rooms);
			if (connect->next)
				get_dot(data, &dots[1], connect->next->rooms);
			else
				get_dot(data, &dots[1], data->lem->end);
			render_line(dots[0], dots[1], data, WAY);
			connect = connect->next;
		}
		way = way->next;
	}
}

static void		render_ant(t_data *data)
{
	t_dot		dot;
	t_way		*way;
	t_connect	*connect;
	char		*str;

	way = data->lem->way;
	while (way)
	{
		connect = way->connect;

		while (connect)
		{
			str = ft_itoa(connect->rooms->number_ant);
			get_dot(data, &dot, connect->rooms);
			if (connect->rooms->number_ant)
				mlx_string_put(data->mlx, data->win, (int)dot.x,
						   (int)dot.y, ANT, str);
			ft_strdel(&str);
			connect = connect->next;
		}
		way = way->next;
	}
}

static void		render_ant_on_start_end(t_data *data)
{
	t_dot		dot;
	char		*str;

	str = ft_itoa(data->lem->start->number_ant);
	get_dot(data, &dot, data->lem->start);
	mlx_string_put(data->mlx, data->win, (int)dot.x, (int)dot.y, ANT_S, str);
	ft_strdel(&str);
	str = ft_itoa(data->lem->end->number_ant);
	get_dot(data, &dot, data->lem->end);
	mlx_string_put(data->mlx, data->win, (int)dot.x, (int)dot.y, ANT_S, str);
	ft_strdel(&str);
}

void			lem_render(t_data *data)
{
	render_background(data);
	render_connect(data);
	render_way(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	render_ant(data);
	render_ant_on_start_end(data);
	render_menu(data);
}