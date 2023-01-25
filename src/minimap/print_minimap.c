/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:45:49 by ralves-g          #+#    #+#             */
/*   Updated: 2023/01/25 18:15:33 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

//Circle formula
// ( x − a )^2 + ( y − b )^2 = r^2

// To print the map at a certain location with the player int the middle we have
// to print in relation to the player
// Meaning you have to print the pixel at: 
// (object pos) - (player pos) + (position you want for the center of the map)

void	print_minimap_wall(t_cub *cub, int m_x, int m_y)
{
	int	y;
	int	x;

	y = m_y;
	while (y < m_y + MAP_UNIT)
	{
		x = m_x;
		while (x < m_x + MAP_UNIT)
		{
			if ((x - cub->minimap_x) * (x - cub->minimap_x) + (y
					- cub->minimap_y) * (y - cub->minimap_y)
				<= MAP_RADIUS * MAP_RADIUS)
				my_mlx_pixel_put(&(cub->map_outline), x - cub->minimap_x
					+ MAP_X_CENTER, y - cub->minimap_y
					+ MAP_Y_CENTER, 0x55FFFFFF);
			x++;
		}
		y++;
	}
}

void	print_outline(t_cub *cub)
{
	int	y;
	int	x;
	int	test;

	y = MAP_Y_CENTER - MAP_RADIUS - 1;
	while (++y < MAP_Y_CENTER + MAP_RADIUS)
	{
		x = MAP_X_CENTER - MAP_RADIUS - 1;
		while (++x < MAP_X_CENTER + MAP_RADIUS)
		{
			if (((x - MAP_X_CENTER) * (x - MAP_X_CENTER) + (y - MAP_Y_CENTER)
					* (y - MAP_Y_CENTER)) <= MAP_OUTLINE * MAP_OUTLINE)
				my_mlx_pixel_put(&(cub->map_outline), x, y, MAP_OUTL_CLR);
		}
	}
	y = MAP_Y_CENTER - MAP_RADIUS - MAP_OUTLINE;
	while (y < MAP_Y_CENTER + MAP_RADIUS + MAP_OUTLINE)
	{
		x = MAP_X_CENTER - MAP_RADIUS - MAP_OUTLINE;
		while (x < MAP_X_CENTER + MAP_RADIUS + MAP_OUTLINE)
		{
			test = (x - MAP_X_CENTER) * (x - MAP_X_CENTER)
				+ (y - MAP_Y_CENTER) * (y - MAP_Y_CENTER);
			if (test >= MAP_RADIUS * MAP_RADIUS && test
				<= (MAP_RADIUS + MAP_OUTLINE) * (MAP_RADIUS + MAP_OUTLINE))
				my_mlx_pixel_put(&(cub->map_outline), x, y, MAP_OUTL_CLR);
			x++;
		}
		y++;
	}
}

void	print_minimap(t_cub *cub)
{
	int	y;
	int	x;

	create_image(cub, &cub->map_outline, CUB_W, CUB_H);
	y = -1;
	while (cub->map[++y])
	{
		x = -1;
		while (cub->map[y][++x])
			if (cub->map[y][x] == '1')
				print_minimap_wall(cub, x * MAP_UNIT, y * MAP_UNIT);
	}
	y = MAP_Y_CENTER - MAP_RADIUS - 1;
	while (++y < MAP_Y_CENTER + MAP_RADIUS)
	{
		x = MAP_X_CENTER - MAP_RADIUS - 1;
		while (++x < MAP_X_CENTER + MAP_RADIUS)
		{
			if (((x - MAP_X_CENTER) * (x - MAP_X_CENTER) + (y - MAP_Y_CENTER)
					* (y - MAP_Y_CENTER)) <= MAP_OUTLINE * MAP_OUTLINE)
				my_mlx_pixel_put(&cub->map_outline, x , y, 0xFFC500FF);
		}
	}
	print_outline(cub);
	mlx_put_image_to_window(cub->mlx, cub->mlx_w, cub->map_outline.img, 0, 0);
	// mlx_destroy_image(cub->mlx, cub->map_outline.img);
	// double test_x = 1.0;
	// double test_y = 0.0;
	// while (test_x >= 0.0)
	// {
	draw_vector(cub, MAP_X_CENTER, MAP_Y_CENTER, (cub->pdx + MAP_X_CENTER) * 20, (cub->pdy + MAP_Y_CENTER) * 20);
	// 	test_x -= 0.01;
	// 	test_y += 0.01;
	// }
}