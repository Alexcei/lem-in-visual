#include "lem_visual.h"

static int	get_ant(t_lem *lem)
{
	get_next_line(lem->fd, &lem->line);
	if (!lem->line)
		return (0);
	lem->ants = ft_atoi(lem->line);
	ft_memdel((void*)&lem->line);
	return (1);
}

int 	ft_arr_count(char **arr)
{
	int 	res;

	res = 0;
	if (arr && *arr)
	{
		while (arr[res])
			res++;
	}
	return (res);
}

void	add_rooms(t_lem *lem, int *flag)
{
	t_rooms		*room;

	room = ft_rooms_new(NULL);
	room->name = ft_strdup(lem->arr[0]);
	room->x = ft_atoi(lem->arr[1]);
	room->y = ft_atoi(lem->arr[2]);
	ft_rooms_push_back(&lem->rooms, room);
	if (*flag == 1)
		lem->start = room;
	if (*flag == 2)
		lem->end = room;
	*flag = 0;
	ft_free_char_arr(&lem->arr);
}

void	get_rooms(t_lem *lem)
{
	int		flag;

	flag = 0;
	while (get_next_line(lem->fd, &lem->line))
	{
		if (ft_strnequ(lem->line, "##start", 7) && (flag = 1))
		{
			ft_memdel((void*)&lem->line);
			continue;
		}
		else if (ft_strnequ(lem->line, "##end", 5) && (flag = 2))
		{
			ft_memdel((void*)&lem->line);
			continue;
		}
		else if (ft_strnequ(lem->line, "#", 1))
		{
			ft_memdel((void*)&lem->line);
			continue;
		}
		lem->arr = ft_double_split(lem->line, ' ', '-');
		ft_memdel((void*)&lem->line);
		if (ft_arr_count(lem->arr) == 3)
			add_rooms(lem, &flag);
		else
			break ;
	}
}

void			add_connect(t_lem *lem)
{
	t_rooms		*rooms;
	t_rooms		*src;
	t_rooms		*dst;

	src = NULL;
	dst = NULL;
	rooms = lem->rooms;
	while (rooms)
	{
		if (ft_strcmp(lem->arr[0], rooms->name) == 0)
			src = rooms;
		else if (ft_strcmp(lem->arr[1], rooms->name) == 0)
			dst = rooms;
		if (src && dst)
			break ;
		rooms = rooms->next;
	}
	if (!src || !dst)
		print_error("ERROR - links name dosn't consist in rooms");
	ft_connect_push_back(&src->connect, ft_connect_new(dst));
	lem->count_connect++;
	ft_free_char_arr(&lem->arr);
}

void	get_connect(t_lem *lem)
{
	if (ft_arr_count(lem->arr) == 2)
		add_connect(lem);
	while (get_next_line(lem->fd, &lem->line))
	{
		if (ft_strnequ(lem->line, "#", 1))
		{
			ft_memdel((void *) &lem->line);
			continue;
		}
		lem->arr = ft_strsplit(lem->line, '-');
		ft_memdel((void*)&lem->line);
		if (ft_arr_count(lem->arr) == 2)
			add_connect(lem);
		else
			break ;
	}
}

void	ft_len_read(t_lem *lem)
{
	if (!get_ant(lem))
		print_error("ERROR: non ant");
	get_rooms(lem);
	get_connect(lem);
}

void	print_graf(t_lem lem)
{
	while (lem.rooms)
	{
		ft_printf("name -%6s number -%2d  bfs %10d  out %d  in %d\n", lem.rooms->name, lem.rooms->number, lem.rooms->bfs, lem.rooms->out, lem.rooms->in);
		lem.rooms = lem.rooms->next;
	}
	ft_printf("%d\n", lem.count_connect);
	ft_printf("\n");
}

int		main(int ac, char **av)
{
	t_lem	lem;

	ft_bzero(&lem, sizeof(t_lem));
	if (ac == 2)
		lem.fd = open(av[1], O_RDONLY);
	ft_len_read(&lem);

	ft_printf("%d\n", lem.ants);
	print_graf(lem);

	free_all(&lem);
	return (0);
}
