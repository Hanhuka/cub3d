/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:59:13 by ralves-g          #+#    #+#             */
/*   Updated: 2023/01/11 23:12:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	has_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*get_map(int fd)
{
	char	*line;
	char	*no_nl;
	int		i;
	int		len;

	line = get_next_line(fd);
	if (!line || !has_char(line, '\n'))
		return (line);
	i = 0;
	len = ft_strlen(line);
	no_nl = malloc(sizeof(char) * len);
	i = 0;
	while (i < len)
	{
		if (line[i] == '\n')
			no_nl[i] = 0;
		else
			no_nl[i] = line[i];
		i++;
	}
	free(line);
	return (no_nl);
}

void	init_cub(t_cub *cub)
{
	cub->color[FLOOR] = -1;
	cub->color[CEILING] = -1;
	cub->walls[C_NO] = NULL;
	cub->walls[C_EA] = NULL;
	cub->walls[C_SO] = NULL;
	cub->walls[C_WE] = NULL;
	cub->map = NULL;
}

char	*ft_strdup(char *str)
{
	char	*dup;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
		i++;
	dup = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

int	check_equal(char *line, char *test)
{
	int	i;

	i = 0;
	while (line[i] && test[i] && line[i] == test[i])
		i++;
	if (!test[i])
		return (1);
	return (0);
}
