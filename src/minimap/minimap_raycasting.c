/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_raycasting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:14:26 by ralves-g          #+#    #+#             */
/*   Updated: 2023/01/27 18:48:31 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// Rotate a vector that has a center on origin by angle 'a' 
// (new point (x1, y1) old point (x0, y0))

// x1 = x0 * cos(a) - y0 * sin(a)
// y1 = x0 * sin(a) + y0 * cos(a)

void	draw_vector(t_cub *cub, double start_x, double start_y,
		double dir_x, double dir_y, double max_size)
{
	double	x;
	double	y;


	// printf("vector dirX[%f] dirY[%f]\n", dir_x, dir_y);
	x = start_x;
	y = start_y;
	while (x >= 0 && x < CUB_W && y >= 0 && y < CUB_H
		&& (start_x - x) * (start_x - x) + (start_y - y) * (start_y - y)
		<= max_size * max_size)
	{
		my_mlx_pixel_put(&cub->map_outline, x, y, 0x00FF0000);
		x += dir_x / 10.0;
		y += dir_y / 10.0;
		// printf("Pixel at x[%f] y[%f]\n", x, y);
	}
}

// void	draw_rays_3d(t_cub *cub)
// {
// 	t_rays rays;
// 	rays.ra = cub.pa;
// 	rays.r = 0;
// 	while (rays.r < 1)
// 	{
// 		rays.a_tan = -1/tan(rays.ra);
// 		if (rays.ra > M_PI)
// 		{
// 			rays.ry = (((int)cub->minimap_y>>6)<<6) - 0.0001;
// 			rays.rx = (cub->minimap_y - ry) * rays.a_tan + px;
// 			rays.yo = -64;
// 			rays.xo = -rays.yo * rays.a_tan;
// 		}
// 		if (rays.ra > M_PI)
// 		{
// 			rays.ry = (((int)cub->minimap_y>>6)<<6) + 64;
// 			rays.rx = (cub->minimap_y - ry) * rays.a_tan + px;
// 			rays.yo = 64;
// 			rays.xo = -rays.yo * rays.a_tan;
// 		}
// 		if (rays.ra == 0 || rays.ra == M_PI)
// 		{
// 			rays.rx = cub->minimap_x;
// 			rays.ry = cub->minimap_y;
// 			rays.dof = 8;
// 		}
// 		while (dof < 8)
// 		{
// 			rays.mx = (int)(rays.rx) >> 6;
// 			rays.my = (int) (rays.ry) >> 6;
// 			rays.mp = rays.my * 
// 		}
// 		r++;
// 	}
// }

































void	rc_initvals(t_cub *cub, int *x)
{
	cub->camera_x = 2 * (*x) / (double)CUB_W - 1;
	cub->ray_dir_x = cub->dir_x + cub->plane_x * cub->camera_x;
	cub->ray_dir_y = cub->dir_y + cub->plane_y * cub->camera_x;
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
		if (cub->map[cub->map_y][cub->map_x] == '1')
		{
			cub->hit = 1;
			printf("Hit at x[%d], y[%d] rayDirX[%f] rayDirY[%f]_y\n sideDistX = %f\n",
				cub->map_x, cub->map_y, cub->ray_dir_x, cub->ray_dir_y, cub->side_dist_x);
		}
	}
}

void	draw_ray(t_cub *cub, int x, int start_y, int end_y, int color)
{
	while (start_y <= end_y)
	{
		my_mlx_pixel_put(&cub->map_outline, CUB_W - x, start_y, color);
		start_y++;
	}
}

void	raycasting(t_cub *cub)
{
	int	x;
	double	m;
	double	b;
	double	eux;
	double	euy;

	x = 0;
	while (x < CUB_W)
	{
		printf("x = %d\n", x);
		rc_initvals(cub, &x);
		rc_initvals2(cub);
		digital_differential_analyzer(cub);
		if (cub->side == 0)
			cub->perp_wall_dist = cub->side_dist_x - cub->delta_dist_x;
		else
			cub->perp_wall_dist = cub->side_dist_y - cub->delta_dist_y;
		if (!cub->ray_dir_x)
			m = cub->ray_dir_y;
		else
			m = cub->ray_dir_y / cub->ray_dir_x;
		b = cub->play_y - cub->play_x * m;
		euy = cub->map_y + (1 - cub->step_y) / 2 - cub->play_y;
		if (cub->side == 0)
			cub->eu = fabs(cub->perp_wall_dist * cub->ray_dir_x);
		else
			cub->eu = fabs(cub->perp_wall_dist * cub->ray_dir_y);

		// draw_vector(cub, MAP)
		// printf("m = %f\n");
		if (!m)
			eux = 0;
		else
			eux = (euy - b) / m;
		// draw_vector(cub, MAP_X_CENTER, MAP_Y_CENTER, cub->ray_dir_x, cub->ray_dir_y, 
		// fabs(sqrt((eux - cub->play_x)*(eux - cub->play_x)+(euy - cub->play_y)*(euy - cub->play_y))));
		// printf("%f\n", fabs(sqrt((eux - cub->play_x)*(eux - cub->play_x)+(euy - cub->play_y)*(euy - cub->play_y))));
		// draw_vector(cub, MAP_X_CENTER, MAP_Y_CENTER, cub->ray_dir_x, cub->ray_dir_y, 
		// cub->perp_wall_dist * MAP_UNIT);
		
		if (cub->side == 0)
			cub->wall_x = cub->play_y + cub->perp_wall_dist * cub->ray_dir_y;
		else
			cub->wall_x = cub->play_x + cub->perp_wall_dist * cub->ray_dir_x;
		cub->wall_x -= floor((cub->wall_x));
		
		cub->line_height = (int)(CUB_H / cub->perp_wall_dist);
		cub->draw_start = -cub->line_height / 2 + CUB_H / 2;
		if (cub->draw_start < 0)
			cub->draw_start = 0;
		cub->draw_end = cub->line_height / 2 + CUB_H / 2;
		if (cub->draw_end >= CUB_H)
			cub->draw_end = CUB_H -1;
		if (cub->side == 1)
			draw_ray(cub, x, cub->draw_start, cub->draw_end, 0x00FCFF3F);
		else
			draw_ray(cub, x, cub->draw_start, cub->draw_end, 0x00DEE05B);
		printf("%f\n", cub->perp_wall_dist);
		printf("%f\n", cub->eu);
		draw_vector(cub, MAP_X_CENTER, MAP_Y_CENTER, cub->ray_dir_x, cub->ray_dir_y, 
		cub->eu * MAP_UNIT);
		x++;
	}
}


