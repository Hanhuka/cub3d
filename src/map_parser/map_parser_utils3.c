/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:57:01 by ralves-g          #+#    #+#             */
/*   Updated: 2023/01/17 15:30:40 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	parse_error(char *line, t_cub *cub, char *msg)
{
	int	i;

	if (line)
		free(line);
	i = -1;
	while (++i < 4)
		if (cub->walls[i])
			free(cub->walls[i]);
	if (msg)
		printf("%s", msg);
	return (1);
}

void	free_textures(t_cub cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub.walls[i])
			free(cub.walls[i]);
		i++;
	}
}