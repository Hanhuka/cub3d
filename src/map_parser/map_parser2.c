/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:13:20 by ralves-g          #+#    #+#             */
/*   Updated: 2023/01/12 23:09:44 by marvin           ###   ########.fr       */
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
