#include "lem_in.h"

//static void		free_all_fil(t_fil *fil)
//{
//	if (fil->plat)
//		ft_free_char_arr(&fil->plat);
//	if (fil->map)
//		ft_free_int_arr(&fil->map, fil->h_plat);
//}

//static void		print_score(t_data *data)
//{
//	char 		*str_one;
//	char 		*str_two;
//	int 		len_one;
//	int 		len_two;
//
//	str_one = ft_itoa(data->fil->score_one);
//	str_two = ft_itoa(data->fil->score_two);
//	len_one = ft_strlen(data->fil->play_one);
//	len_two = ft_strlen(data->fil->play_two);
//	mlx_string_put(data->mlx, data->win, (WIDTH / 2) - len_one * 10 - 110,
//				   (HEIGHT / 8), 0x0FFFFFF, str_one);
//	mlx_string_put(data->mlx, data->win, (WIDTH / 2) - len_one * 10 - 50,
//				   (HEIGHT / 8), PLAYER1, data->fil->play_one);
//	mlx_string_put(data->mlx, data->win, (WIDTH / 2) - 30, (HEIGHT / 8),
//				   0x0FFFFFF, "&");
//	mlx_string_put(data->mlx, data->win, (WIDTH / 2) , (HEIGHT / 8),
//				   PLAYER2, data->fil->play_two);
//	mlx_string_put(data->mlx, data->win, (WIDTH / 2) + len_two * 10 + 20,
//				   (HEIGHT / 8), 0x0FFFFFF, str_two);
//	ft_strdel(&str_one);
//	ft_strdel(&str_two);
//}

//static void		print_final(t_data *data)
//{
//	char		*str;
//	int 		len_one;
//	int 		len_two;
//
//	len_one = ft_strlen(data->fil->play_one);
//	len_two = ft_strlen(data->fil->play_two);
//	str = "IS WIN";
//	if (data->fil->score_one > data->fil->score_two)
//		mlx_string_put(data->mlx, data->win, (WIDTH / 2) - 60 - len_one * 10,
//					   (HEIGHT / 8) + 30, PLAYER1, data->fil->play_one);
//	else
//		mlx_string_put(data->mlx, data->win, (WIDTH / 2) - 60 - len_two * 10,
//					   (HEIGHT / 8) + 30, PLAYER2, data->fil->play_two);
//	mlx_string_put(data->mlx, data->win, (WIDTH / 2) - 50, (HEIGHT / 8) + 30,
//				   0x0FFFFFF, str);
//}

int				lem_loop_key_hook(t_data *data)
{
	char		*str;

	if (data->pause == 0)
	{
		while (!data->fil->read && !ft_read_fil(data->fil))
		{
			if (data->fil->plat)
			{
				ft_creat_image(data);
				//free_all_fil(data->fil);
			}
		}
	}
	fdf_render(data);
	//print_score(data);
	if (data->pause == 1)
	{
		str = "PAUSE";
		mlx_string_put(data->mlx, data->win,
					   (WIDTH / 5) - 10, (HEIGHT / 2) - 10, 0x0FFFFFF, str);
	}
	//if (data->fil->read)
	//	print_final(data);
	return (0);
}