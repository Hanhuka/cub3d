/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_raycasting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:14:26 by ralves-g          #+#    #+#             */
/*   Updated: 2023/01/26 12:29:54 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// Rotate a vector that has a center on origin by angle 'a' 
// (new point (x1, y1) old point (x0, y0))

// x1 = x0 * cos(a) - y0 * sin(a)
// y1 = x0 * sin(a) + y0 * cos(a)

void	draw_vector(t_cub *cub, double start_x, double start_y,
		double dir_x, double dir_y)
{
	double	x;
	double	y;


	printf("vector dirX[%f] dirY[%f]\n", dir_x, dir_y);
	x = start_x;
	y = start_y;
	while (x >= 0 && x < CUB_W && y >= 0 && y < CUB_H
		&& (start_x - x) * (start_x - x) + (start_y - y) * (start_y - y)
		<= MAP_RADIUS * MAP_RADIUS)
	{
		mlx_pixel_put(cub->mlx, cub->mlx_w, x, y, 0x00FF0000);
		x += dir_x;
		y += dir_y;
		// printf("Pixel at x[%f] y[%f]\n", x, y);
	}
}

void	rc_initvals(t_cub *cub, int *x)
{
	cub->camera_x = 2 * (*x) / (double)CUB_W - 1;
	cub->ray_dir_x = cub->dir_x + cub->plane_x * cub->camera_x;
	cub->ray_dir_y = cub->dir_y + cub->plane_y * cub->camera_x;
	x++;
	cub->map_x = (int) cub->play_x;
	cub->map_y = (int) cub->play_y;
	if (cub->ray_dir_x == 0)
		cub->delta_dist_x = 1e30;
	else
		cub->delta_dist_x = fabs(1 / cub->ray_dir_x);
	if (cub->ray_dir_y == 0)
		cub->delta_dist_y = 1e30;
	else
		cub->delta_dist_y = fabs(1 / cub->ray_dir_y);
	cub->hit = 0;
}

void	rc_initvals2(t_cub *cub)
{
	if (cub->ray_dir_x < 0)
	{
		cub->step_x = -1;
		cub->side_dist_x = (cub->play_x - cub->map_x) * cub->delta_dist_x;
	}
	else
	{
		cub->step_x = 1;
		cub->side_dist_x = (cub->map_x + 1.0 - cub->play_x) * cub->delta_dist_x;
	}
	if (cub->ray_dir_y < 0)
	{
		cub->step_y = -1;
		cub->side_dist_y = (cub->play_y - cub->map_y) * cub->delta_dist_y;
	}
	else
	{
		cub->step_y = 1;
		cub->side_dist_y = (cub->map_y + 1.0 - cub->play_y) * cub->delta_dist_y;
	}
}

void	digital_differential_analyzer(t_cub *cub)
{
	while (!cub->hit)
	{
		if (cub->side_dist_x < cub->side_dist_y)
		{
			cub->side_dist_x += cub->delta_dist_x;
			cub->map_x += cub->step_x;
			cub->side = 0;
		}
		else
		{
			cub->side_dist_y += cub->delta_dist_y;
			cub->map_y += cub->step_y;
			cub->side = 1;
		}
		if (cub->map[cub->map_y][cub->map_x] > 0)
		{
			cub->hit = 1;
			printf("Hit at x[%d], y[%d] rayDirX[%f] rayDirY[%f]_y\n sideDistX = %f\n",
				cub->map_x, cub->map_y, cub->ray_dir_x, cub->ray_dir_y, cub->side_dist_x);
		}
	}
}

void	draw_ray(t_cub *cub)
{
	int	m;
	int	b;
	int	x;
	int	y;

	m = (cub->play_y * MAP_UNIT - cub->map_y) / (cub->play_x * MAP_UNIT
			- cub->map_x);
	b = cub->play_y * MAP_UNIT - m * cub->play_x * MAP_UNIT;
	x = MAP_X_CENTER - MAP_RADIUS;
	while (x <= MAP_X_CENTER + MAP_RADIUS)
	{
		y = m * x + b;
		if (y >= MAP_Y_CENTER - MAP_RADIUS && y <= MAP_Y_CENTER - MAP_RADIUS)
			my_mlx_pixel_put(&cub->map_outline, x, y, 0x0000FF00);
		x++;
	}
}

void	raycasting(t_cub *cub)
{
	int	x;

	x = 0;
	while (x < CUB_W)
	{
		printf("x = %d\n", x);
		rc_initvals(cub, &x);
		rc_initvals2(cub);
		digital_differential_analyzer(cub);
		draw_ray(cub);
		x++;
	}
}


