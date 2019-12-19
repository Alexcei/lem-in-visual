#include "lem_in.h"

static void		set_dot(t_data *data, int height, int wigth)
{
	data->dot[height * data->width + wigth].z = - data->fil->map[height][wigth];
	data->dot[height * data->width + wigth].x = (double)wigth;
	data->dot[height * data->width + wigth].y = (double)height;
	if ((data->fil->plat[height][wigth] == 'o' ||
		 data->fil->plat[height][wigth] == 'O') &&
		++data->fil->score_one)
		data->dot[height * data->width + wigth].color = PLAYER1;
	else if ((data->fil->plat[height][wigth] == 'x' ||
			  data->fil->plat[height][wigth] == 'X') &&
			 ++data->fil->score_two)
		data->dot[height * data->width + wigth].color = PLAYER2;
	else
		data->dot[height * data->width + wigth].color = 0;
}

static void		creat_fdf(t_data *data)
{
	int 		height;
	int 		width;

	data->width = data->fil->w_plat;
	data->height = data->fil->h_plat;
	if (!data->camera->zoom)
		data->camera->zoom =
				FT_MIN(WIDTH / data->width / 2, HEIGHT / data->height / 2);
	data->size = data->width * data->height;
	if (data->dot)
		ft_memdel((void*)&data->dot);
	data->dot = (t_dot*)ft_memalloc(sizeof(t_dot) * data->size);
	data->fil->score_one = 0;
	data->fil->score_two = 0;
	height = 0;
	while (height < data->height)
	{
		width = 0;
		while(width < data->width)
		{
			set_dot(data, height, width);
			width++;
		}
		height++;
	}
}

void			ft_creat_image(t_data *data)
{
	int 		i;

	i = 1;
	if (!(ft_creat_heat_map(data->fil)))
		print_error(data->fil, "error_memory_head_map");
	ft_put_players_on_heat_map(data->fil);
	while (ft_fill_heat_map(data->fil, i))
		i++;
	creat_fdf(data);
}