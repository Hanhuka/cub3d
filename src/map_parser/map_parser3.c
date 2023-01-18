/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:41:27 by ralves-g          #+#    #+#             */
/*   Updated: 2023/01/18 17:03:35 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_coords(t_cub *cub, int x, int y)
{
	if (y == 0 || x == 0 || !cub->map[y - 1][x] || cub->map[y - 1][x] == ' ' || 
	!cub->map[y - 1][x + 1] || cub->map[y - 1][x + 1] == ' ' || 
	!cub->map[y][x + 1] || cub->map[y][x + 1] == ' ' || 
	!cub->map[y + 1][x + 1] || cub->map[y + 1][x + 1] == ' ' || 
	!cub->map[y + 1][x] || cub->map[y + 1][x] == ' ' || 
	!cub->map[y + 1][x - 1] || cub->map[y + 1][x - 1] == ' ' || 
	!cub->map[y][x - 1] || cub->map[y][x - 1] == ' ' || 
	!cub->map[y - 1][x - 1] || cub->map[y - 1][x - 1] == ' ')
		return (1);
	return (0);
}

int	check_map(t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if ((cub->map[y][x] == '0' || cub->map[y][x] == 'N' || cub->map[y][x] == 'S' || 
			cub->map[y][x] == 'W' || cub->map[y][x] == 'E') && (check_coords(cub, x, y)))
			{
				printf("Error\nMap is not correcty configured\nStopped at point [%d][%d]\n", y, x);
				free_matrix(cub->map);
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}