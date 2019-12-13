#include "lem_visual.h"

void	print_error(char *message)
{
	ft_putendl_fd(message, 0);
	exit(EXIT_FAILURE);
}

void			ft_free_char_arr(char ***arr)
{
	int			i;

	i = 0;
	if (*arr)
	{
		while ((*arr)[i])
			ft_strdel(&((*arr)[i++]));
		free(*arr);
		*arr = NULL;
	}
}

static void		free_connect(t_connect *connect)
{
	t_connect		*tmp;

	while (connect)
	{
		tmp = connect;
		connect = connect->next;
		ft_memdel((void*)&tmp);
	}
}

static void		free_rooms(t_rooms *rooms)
{
	t_rooms		*tmp_rooms;

	if (!rooms)
		return ;
	while (rooms)
	{
		tmp_rooms = rooms;
		if (tmp_rooms->name)
			ft_strdel(&tmp_rooms->name);
		if (tmp_rooms->name)
			ft_strdel(&tmp_rooms->name);
		if (tmp_rooms->connect)
			free_connect(tmp_rooms->connect);
		rooms = rooms->next;
		ft_memdel((void*)&tmp_rooms);
	}
}

void	free_all(t_lem *lem)
{
	if (lem->rooms)
		free_rooms(lem->rooms);
	if (lem->line)
		ft_strdel(&lem->line);
	if (lem->arr)
		ft_free_char_arr(&lem->arr);
}