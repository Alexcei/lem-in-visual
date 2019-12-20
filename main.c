/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtorwold <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 14:50:34 by wtorwold          #+#    #+#             */
/*   Updated: 2019/12/20 17:01:36 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		lem_init(t_data *data, t_mouse  *mouse, t_camera *camera)
{
	ft_bzero(camera, sizeof(t_camera));
	ft_bzero(mouse, sizeof(t_mouse));
	data->camera = camera;
	data->mouse = mouse;
	if (!(data->mlx = mlx_init()) ||
		!(data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "LEM_IN")) ||
		!(data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT)))
		return (0);
	data->data_addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
										&data->size_line, &data->endian);
	data->camera->x_offset = WIDTH / 2;
	data->camera->y_offset = HEIGHT / 2;
	return (1);
}

static void		make_clone(t_lem *lem)
{
	t_way		*way;
	t_connect	*connect;

	lem->start->number_ant = lem->ants;
	way = lem->way;
	while (way)
	{
		connect = way->connect;
		while (connect)
		{
			ft_connect_add(&way->clone, ft_connect_new(connect->rooms));
			connect = connect->next;
		}
		way = way->next;
	}
}

void			lem_in(t_data *data, t_lem *lem)
{
	ft_parse_file(data);
	ft_bfs(data->lem);
	find_way(data->lem);
	if (!data->lem->way && !check_start_end(lem))
		ft_error("ERROR: no solve");
	ft_print_save(lem);
	make_clone(data->lem);
}

void			parse_flag(t_data *data, t_lem *lem, int ac, char **av)
{
	ft_bzero(data, sizeof(t_data));
	ft_bzero(lem, sizeof(t_lem));
	data->lem = lem;

	if (av[2] != NULL && (ft_strcmp(av[2], "-v") == 0))
		data->lem->v = 1;
	if (ac != 2 && data->lem->v == 0)
		ft_error("ERROR: Usage : ./lem-in < <filename>");
	else if (ac != 3 && data->lem->v == 1)
		ft_error("ERROR: Usage : ./lem-in < <filename> [-v]");
	if ((data->lem->fd = open(av[1], O_RDONLY)) < 0)
		ft_error("Open error");

//	if (ac == 2 && (ft_strcmp(av[1], "-v") == 0))
//		data->lem->v = 1;
//	if (ac != 1 && data->lem->v == 0)
//		ft_error("ERROR: Usage : ./lem-in < <filename>");
//	else if (ac != 2 && data->lem->v == 1)
//		ft_error("ERROR: Usage : ./lem-in < <filename> [-v]");
}

int				main(int ac, char **av)
{
	t_camera	camera;
	t_mouse 	mouse;
	t_data		data;
	t_lem		lem;

	parse_flag(&data, &lem, ac, av);
	if (data.lem->v && !lem_init(&data, &mouse, &camera))
		ft_error("error: initialization");
	lem_in(&data, &lem);
	if (data.lem->v)
	{
		mlx_key_hook(data.win, lem_hook_keydown, &data);
		mlx_hook(data.win, 17, 0, lem_close, &data);
		mlx_hook(data.win, 4, 0, lem_mouse_press, &data);
		mlx_hook(data.win, 5, 0, lem_mouse_release, &data);
		mlx_hook(data.win, 6, 0, lem_mouse_move, &data);
		mlx_loop_hook(data.mlx, lem_loop_key_hook, &data);
		mlx_loop(&data.mlx);
	}
	else
		ft_ant_moves(&data);
	free_all(data.lem);
	return (0);
}