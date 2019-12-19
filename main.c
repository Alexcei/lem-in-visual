/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtorwold <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 14:50:34 by wtorwold          #+#    #+#             */
/*   Updated: 2019/12/19 02:40:02 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		fdf_close(void *data)
{
	(void)data;
	exit(EXIT_SUCCESS);
}

static int		fdf_init(t_data *data, t_mouse  *mouse, t_camera *camera)
{
	ft_bzero(camera, sizeof(t_camera));
	ft_bzero(mouse, sizeof(t_mouse));
	ft_bzero(data, sizeof(t_data));
	data->camera = camera;
	data->mouse = mouse;
	if (!(data->mlx = mlx_init()) ||
		!(data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "FDF")) ||
		!(data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT)))
		return (0);
	data->data_addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
										&data->size_line, &data->endian);
	data->camera->x_offset = WIDTH / 2;
	data->camera->y_offset = HEIGHT / 2;
	data->camera->polygon = 1;
	return (1);
}

int				main(int ac, char **av)
{
	t_camera	camera;
	t_mouse 	mouse;
	t_data		data;
	t_lem		lem;

	ft_bzero(&lem, sizeof(t_lem));
	if (!fdf_init(&data, &mouse, &camera))
		ft_error("error: initialization");

	if (av[2] != NULL && (ft_strcmp(av[2], "-v") == 0))
		lem.v = 1;
	if (ac != 2 && lem.v == 0)
		ft_error("ERROR: Usage : ./lem-in < <filename>");
	else if (ac != 3 && lem.v == 1)
		ft_error("ERROR: Usage : ./lem-in < <filename> [-v]");
	if ((lem.fd = open(av[1], O_RDONLY)) < 0)
		ft_error("Open error");

//	if (ac == 2 && (ft_strcmp(av[1], "-v") == 0))
//		lem.v = 1;
//	if (ac != 1 && lem.v == 0)
//		ft_error("ERROR: Usage : ./lem-in < <filename>");
//	else if (ac != 2 && lem.v == 1)
//		ft_error("ERROR: Usage : ./lem-in < <filename> [-v]");

	ft_parse_file(&lem);
	ft_bfs(&lem);
	find_way(&lem);
	if (!lem.way)
		ft_error("ERROR: no solve");
	//ft_print_save(&lem);

	mlx_key_hook(data.win, lem_hook_keydown, &data);
	mlx_hook(data.win, 17, 0, fdf_close, &data);
	mlx_hook(data.win, 4, 0, lem_mouse_press, &data);
	mlx_hook(data.win, 5, 0, lem_mouse_release, &data);
	mlx_hook(data.win, 6, 0, lem_mouse_move, &data);
	mlx_loop_hook(data.mlx, lem_loop_key_hook, &data);
	mlx_loop(&data.mlx);

	ft_ant_moves(&lem);
	free_all(&lem);
	return (0);
}
