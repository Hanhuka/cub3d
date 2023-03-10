	# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/26 16:26:20 by ralves-g          #+#    #+#              #
#    Updated: 2022/11/08 16:18:15 by ralves-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address -g
RM			=	rm -f

NAME		=	cub3d

INCLUDE		=	-I ./ mlx-linux/libmlx_Linux.a

SRCS_		=	cub3d.c \
				utils.c \
				testing_prints.c \
				gnl/get_next_line.c \
				gnl/get_next_line_utils.c \
				minimap/print_minimap.c \
				minimap/minimap_raycasting.c \
				map_parser/map_parser.c \
				map_parser/map_parser2.c \
				map_parser/map_parser3.c \
				map_parser/map_parser_utils.c \
				map_parser/map_parser_utils2.c \
				map_parser/map_parser_utils3.c

SRCS		=	$(addprefix $(_SRC), $(SRCS_))

DEPS		=	./mlx-linux/libmlx_Linux.a

_SRC		=	./src/
_MLX		=	./mlx-linux

OBJS		=	$(patsubst %.c, %.o, $(SRCS))
all:	$(NAME)

$(_OBJ)%.o: $(_SRC)%.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz $(OBJS) -o $(NAME) $(INCLUDE) -L $(_MLX)

./minilibx_linux/libmlx_Linux.a:
	make -C mlx-linux/

#bonus:		$(SRCS_B) $(OBJS_B)
#			$(CC) $(CFLAGS) $(SRCS_B) -o $(NAME_B)
#			$(CC) $(CFLAGS) $(SRCS_B) -c

$(_OBJ):
	mkdir $@

clean:
	$(RM) -r $(OBJS)

fclean:	clean
	$(RM) -r $(NAME)
	$(RM) -r $(_MLX)libmlx_Linux.a

re:	fclean all
