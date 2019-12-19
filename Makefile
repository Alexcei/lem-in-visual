# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bpole <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 10:08:31 by bpole             #+#    #+#              #
#    Updated: 2019/12/19 01:06:17 by bpole            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

LIB_DIR = ./ft_printf/

LIBFT = $(LIB_DIR)libftprintf.a

SRC = ant_moves.c bfs.c find_way.c free_all.c lib_connect.c lib_room.c main.c \
      parse.c parse_link.c parse_rooms.c print_result.c utils.c valid_links.c \
      valid_rooms.c valid_rooms2.c

OBJ = $(SRC:.c=.o)

INCLUDE = ./

CC = gcc

FLAGS = -Wall -Wextra -Werror

FRAEM = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

%.o: %.c
	$(CC) -c $(FLAGS) $<

$(NAME): $(OBJ)
	$(MAKE) -C $(LIB_DIR)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(FRAEM)

clean:
	rm -rf $(OBJ)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all
