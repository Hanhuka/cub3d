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

INCLUDE		=	-I ./

SRCS_		=	cub3d.c \
				get_next_line.c \
				get_next_line_utils.c \
				map_parser/map_parser.c \
				map_parser/map_parser2.c \
				map_parser/map_parser_utils.c \
				map_parser/map_parser_utils2.c \
				map_parser/map_parser_utils3.c

SRCS		=	$(addprefix $(_SRC), $(SRCS_))

_OBJ		=
_SRC		=	./src/

OBJS		=	$(patsubst %.c, %.o, $(SRCS))
all:		$(NAME)

$(_OBJ)%.o: $(_SRC)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(_OBJ) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDE)

#bonus:		$(SRCS_B) $(OBJS_B)
#			$(CC) $(CFLAGS) $(SRCS_B) -o $(NAME_B)
#			$(CC) $(CFLAGS) $(SRCS_B) -c

$(_OBJ):
	mkdir $@

clean:
	$(RM) -r $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
