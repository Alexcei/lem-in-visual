/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 00:51:59 by bpole             #+#    #+#             */
/*   Updated: 2019/12/19 02:57:27 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "ft_printf/ft_printf.h"
# include <mlx.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>

# define HEIGHT				1080
# define WIDTH				1920
# define SIZE 				HEIGHT * WIDTH

# define TEXT_COLOR			0xEAEAEA
# define BACKGROUND			0x0
# define PLAYER1		    0x5555FF
# define PLAYER2		    0xFF5555
# define FDF 		   		0x0

# define FT_MIN(a, b) (a < b ? a : b)
# define MAX(a, b) (a > b ? a : b)
# define MOD(a) (a < 0 ? -a : a)

# define MOUSE_LEFT_BUTTON	1
# define MOUSE_RIGHT_BUTTON	2
# define MOUSE_THREE_BUTTON	3
# define MOUSE_SCROLL_UP	4
# define MOUSE_SCROLL_DOWN	5

# define ARROW_UP			126
# define ARROW_DOWN			125
# define ARROW_LEFT			123
# define ARROW_RIGHT		124

# define NUM_PAD_PLUS		69
# define NUM_PAD_MINUS		78

# define MAIN_PAD_ESC		53
# define MAIN_PAD_G			5
# define MAIN_PAD_H			4
# define MAIN_PAD_P			35
# define MAIN_PAD_PLUS		24
# define MAIN_PAD_MINUS		27

typedef struct			s_save
{
	char				*content;
	struct s_save		*next;
}						t_save;

typedef struct			s_links
{
	char				*begin;
	char				*finish;
	struct s_links		*next;
}						t_links;

typedef struct s_rooms	t_rooms;

typedef struct			s_connect
{
	t_rooms				*rooms;
	struct s_connect	*next;
}						t_connect;

typedef struct			s_way
{
	t_connect			*connect;
	t_connect			*clone;
	int					count;
	struct s_way		*next;
}						t_way;

struct					s_rooms
{
	int					number_ant;
	int					used;
	char				*name;
	int					x;
	int					y;
	int					z;
	int					out;
	int					in;
	int					bfs;
	int					type;
	t_connect			*connect;
	struct s_rooms		*next;
}						;

typedef struct			s_lem
{
	char				**str;
	t_save				*save;
	int					space;
	int					max_bfs;
	int					fd;
	int					ants;
	t_way				*way;
	t_links				*links;
	t_rooms				*rooms;
	t_rooms				*start;
	t_rooms				*end;
	char				*line;
	char				**arr;
	int					v;
}						t_lem;

typedef struct		s_mouse
{
	char			put_left;
	char			put_right;
	int				x;
	int				y;
	int				previous_x;
	int				previous_y;
}					t_mouse;

typedef struct		s_camera
{
	int				zoom;
	double			alpha;
	double			beta;
	double			x_offset;
	double			y_offset;
	int 			polygon;
}					t_camera;

typedef struct		s_dot
{
	double			x;
	double			y;
	double			z;
	int 			color;
}					t_dot;

typedef struct		s_data
{
	t_camera		*camera;
	t_mouse 		*mouse;
	t_dot			*dot;
	int 			color_tmp;
	int				width;
	int				height;
	int 			size;
	int 			pause;
	int				z_min;
	int				z_max;
	void			*mlx;
	void			*win;
	void			*img;
	char			*data_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_data;

/*
** 						ant_moves.c
*/
void					ft_ant_moves(t_lem *lem);

/*
**						bfs.c
*/
void					ft_bfs(t_lem *lem);

/*
**						bresenhem.c
*/
void					render_line(t_dot a, t_dot b, t_data *data);
void					render_plane(t_dot a, t_dot b, t_dot c, t_data *data);

/*
**						control.c
*/
int						lem_hook_keydown(int key, t_data *data);

/*
**						control.c
*/
void					ft_creat_image(t_data *data);

/*
**						find_way.c
*/
void					find_way(t_lem *lem);

/*
**						free_all.c
*/
void					free_all(t_lem *lem);

/*
**						lib_connect.c
*/
t_connect				*ft_connect_new(t_rooms *rooms);
void					ft_connect_add(t_connect **alst, t_connect *new);
void					ft_connect_push_back(t_connect **begin_list,
						t_connect *new);
void					ft_connect_sort(t_connect **begin_list);

/*
**						lib_room.c
*/
t_save					*ft_save_new(char *content);
void					ft_save_push_back(t_save **begin_list, t_save *new);
int						ft_find_fork_out(t_rooms *room);

/*
**						loop_key_hook.c
*/
int						lem_loop_key_hook(t_data *data);

/*
**						mouse_move.c
*/
int						lem_mouse_press(int button, int x, int y, void *param);
int						lem_mouse_release(int button, int x, int y, void *param);
int						lem_mouse_move(int x, int y, void *param);

/*
**						parse.c
*/
int						ft_read_file(t_lem *lem);
int						ft_hash(char *line);
void					ft_parse_file(t_lem *lem);

/*
**						parse_link.c
*/
void					parse_links(t_lem *lem);

/*
**						parse_rooms.c
*/
void					parse_rooms(t_lem *lem);

/*
**						print_result.c
*/
void					ft_print_save(t_lem *lem);
void					ft_ant_moves_in_rooms(t_lem *lem);

/*
** 						render.c
*/
void					fdf_render(t_data *data);

/*
** 						transform.c
*/
void					rotate(t_dot *dot, double alpha, double beta);
t_dot					transformations(t_dot dot, t_data *data);

/*
** 						utils.c
*/
void					ft_error(char *str);
void					ft_free_char_arr(char ***arr);
void					ft_swap(void **a, void **b);

/*
** 						valid_links.c
*/
void					add_links(t_lem *lem);

/*
** 						valid_rooms.c
*/
char					**valid_rooms(t_lem *lem);

/*
** 						valid_rooms2.c
*/
void					valid_rooms2(t_lem *lem);

#endif
