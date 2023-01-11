/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:17:31 by ralves-g          #+#    #+#             */
/*   Updated: 2023/01/11 18:52:35 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include "get_next_line.h"

# define CEILING 1
# define FLOOR 0

# define C_NO 0
# define C_EA 1
# define C_SO 2
# define C_WE 3

typedef struct s_cub {
	char	*walls[4];
	int		color[2];
	int		play_x;
	int		play_y;
	char	**map;
}	t_cub;

//map_parser.c
int		check_name(char *name);
int		parse_variables(char *name, t_cub *cub, int var);
int		parse_map(int ac, char **av, t_cub *cub);

//map_parser_utils.c
int		has_char(char *str, char c);
char	*get_map(int fd);
void	init_cub(t_cub *cub);
char	*ft_strdup(char *str);
int		check_equal(char *line, char *test);

#endif 