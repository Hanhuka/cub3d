/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_raycasting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:14:26 by ralves-g          #+#    #+#             */
/*   Updated: 2023/01/23 17:04:22 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// Rotate a vector that has a center on origin by angle 'a' 
// (new point (x1, y1) old point (x0, y0))

// x1 = x0 * cos(a) - y0 * sin(a)
// y1 = x0 * sin(a) + y0 * cos(a)

void	draw_vector(t_cub *cub, int start_x, int start_y, int dir_x, int dir_y)
{
	int	x;
	int	y;

	x = start_x + dir_x;
	y = start_y + dir_y;
	while (x > 0 && x < CUB_W && y > 0 && y < CUB_H)
	{
		mlx_pixel_put(cub->mlx, cub->mlx_w, x, y, 0x00FF0000);
		x *= 2;
		y *= 2;
	}
}
