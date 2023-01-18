/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:13:20 by ralves-g          #+#    #+#             */
/*   Updated: 2023/01/18 16:46:07 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_name(char *name)
{
	int	len;
	int	fd;

	len = ft_strlen(name);
	if (len < 5 || name[len - 4] != '.' || name[len - 3] != 'c'
		|| name[len - 2] != 'u' || name[len - 1] != 'b')
	{
		printf("Error\nMap name needs to end with \".cub\"\n");
		return (1);
	}
	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nCouldn't open file\n");
		return (1);
	}
	close(fd);
	return (0);
}

int	add_texture(char *line, t_cub *cub, int *var, int type)
{
	if (cub->walls[type])
	{
		printf("Error\nDuplicated texture: \"%s\"\n", line);
		return (1);
	}
	// Maybe check here if textures have a valid path
	cub->walls[type] = ft_strdup(line + 3);
	*var -= 1;
	free(line);
	return (0);
}

int	add_matrix(t_cub *cub, char *line)
{
	char	**map;
	int		i;

	i = 0;
	while (cub->map && cub->map[i])
		i++;
	map = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (cub->map && cub->map[i])
	{
		map[i] = cub->map[i];
		i++;
	}	
	map[i] = line;
	map[i + 1] = 0;
	if (cub->map)
		free(cub->map);
	cub->map = map;
	// printf_matrix(cub->map);
	return (0);
}

int	check_line(char *line, int *player)
{
	int			i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' ' && \
		line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
		{
			printf("Error\nMap contains at least one invalid character '%C'\n", line[i]);
			free(line);
			return (1);
		}
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			*player += 1;
		if (*player > 1)
		{
			free(line);
			printf("Error\nThere can only be one player\n");
			return (1);
		}
	}
	return (0);
}

int	parse_map(t_cub *cub, int fd)
{
	char		*line;
	static int	player = 0;

	line = get_map(fd);
	while (line)
	{
		if (check_line(line, &player))
		{
			if (cub->map)
				free_matrix(cub->map);
			return (1);
		}
		else
			add_matrix(cub, line);
		line = get_map(fd);
	}
	if (!player)
	{
		printf("Error\nMap needs at least one player\n");
		if (cub->map)
			free_matrix(cub->map);
		return (1);
	}
	return (0);
}
