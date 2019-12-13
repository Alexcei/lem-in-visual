#ifndef LEM_VISUAL_LEM_VISUAL_H
# define LEM_VISUAL_LEM_VISUAL_H

# include "ft_printf/ft_printf.h"

typedef struct s_rooms		t_rooms;

typedef struct              s_connect
{
	t_rooms					*rooms;
	struct s_connect		*next;
}							t_connect;

struct		         		s_rooms
{
	char					*name;
	int 					number;
	int						x;
	int						y;
	int 					out;
	int 					in;
	int						bfs;	// -1 - middle, 0 - start, max_int - end,
	t_connect				*connect;
	struct s_rooms			*next;
}							;

typedef struct				s_lem
{
	int 					count_connect;
	int 					count_rooms;
	int						ants;
	t_rooms					*rooms;
	t_rooms					*start;
	t_rooms					*end;
	int 					fd;
	char 					*line;
	char 					**arr;
}							t_lem;

/*
**				double_split.c
*/
char			**ft_double_split(char const *s, char c1, char c2);

/*
**				lib_connect.c
*/
t_connect		*ft_connect_new(t_rooms *rooms);
void			ft_connect_add(t_connect **alst, t_connect *new);
void			ft_connect_push_back(t_connect **begin_list, t_connect *new);
void 			ft_connect_clear(t_connect **begin_list);
void			ft_connect_remove_if(t_connect **begin_list, int bfs, int (*cmp)());

/*
**				lib_room.c
*/
t_rooms			*ft_rooms_new(t_connect *connect);
void			ft_rooms_add(t_rooms **alst, t_rooms *new);
void			ft_rooms_push_back(t_rooms **begin_list, t_rooms *new);

/*
**				utils.c
*/
void			print_error(char *message);
void			ft_free_char_arr(char ***arr);
void			free_all(t_lem *lem);

#endif
