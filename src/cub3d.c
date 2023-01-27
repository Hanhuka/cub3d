/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:20:45 by ralves-g          #+#    #+#             */
/*   Updated: 2023/01/27 18:45:58 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	give_dir(t_cub *cub, char c)
{
	cub->dir_x = 0;
	cub->dir_y = 0;
	if (c == 'N')
		cub->dir_y = -1;
	else if (c == 'S')
		cub->dir_y = 1;
	else if (c == 'W')
		cub->dir_x = -1;
	else if (c == 'E')
		cub->dir_x = 1;
	cub->pdx = 0;
	cub->pdy = 0;
	if (c == 'N')
		cub->pa = -M_PI_2;
	else if (c == 'S')
		cub->pa = M_PI_2;
	else if (c == 'W')
		cub->pa = M_PI;
	else if (c == 'E')
		cub->pa = 0;
	cub->pdx = cos(cub->pa) * 5;
	cub->pdy = sin(cub->pa) * 5;
	// if (c == 'N')
	// 	cub->pdy = -1;
	// else if (c == 'S')
	// 	cub->pdy = 1;
	// else if (c == 'W')
	// 	cub->pdx = -1;
	// else if (c == 'E')
	// 	cub->pdx = 1;
}

void	search_player(t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if (cub->map[y][x] == 'N' || cub->map[y][x] == 'S'
			|| cub->map[y][x] == 'W' || cub->map[y][x] == 'E')
			{
				cub->play_x = x;
				cub->play_y = y;
				cub->minimap_x = x * MAP_UNIT;
				cub->minimap_y = y * MAP_UNIT;
				give_dir(cub, cub->map[y][x]);
			}
			x++;
		}
		y++;
	}
	printf("PLAYER X[%f] Y[%f] dirX[%f] dirY[%f]\n", cub->play_x, cub->play_y, cub->dir_x, cub->dir_y);
}

void	map_move_player(t_cub *cub, int x, int y)
{
	double	dirx;
	double	diry;

	if (cub->key_r - cub->key_l == 1)
	{
		cub->old_dir_x = cub->dir_x;
		cub->dir_x = cub->dir_x * cos(-cub->rot_speed) - cub->dir_y * sin(-cub->rot_speed);
		cub->dir_y = cub->old_dir_x * sin(-cub->rot_speed) + cub->dir_y * cos(-cub->rot_speed);
		cub->old_plane_x = cub->plane_x;
		cub->plane_x = cub->plane_x * cos(-cub->rot_speed) - cub->plane_x * sin(-cub->rot_speed);
		cub->plane_y = cub->old_plane_x * sin(-cub->rot_speed) + cub->plane_y * cos(-cub->rot_speed);
	}
	else if (cub->key_r - cub->key_l == -1)
	{
		cub->old_dir_x = cub->dir_x;
		cub->dir_x = cub->dir_x * cos(cub->rot_speed) - cub->dir_y * sin(cub->rot_speed);
		cub->dir_y = cub->old_dir_x * sin(cub->rot_speed) + cub->dir_y * cos(cub->rot_speed);
		cub->old_plane_x = cub->plane_x;
		cub->plane_x = cub->plane_x * cos(cub->rot_speed) - cub->plane_x * sin(cub->rot_speed);
		cub->plane_y = cub->old_plane_x * sin(cub->rot_speed) + cub->plane_y * cos(cub->rot_speed);
	}
	cub->pa += (cub->key_r - cub->key_l) * (10 * (M_PI / 180));
	if (cub->pa < 0)
		cub->pa += 2 * M_PI;
	if (cub->pa > 2 * M_PI)
		cub->pa -= 2 * M_PI;
	cub->pdx = cos(cub->pa) * 5;
	cub->pdy = sin(cub->pa) * 5;
	if (x == 1 && y == 0)
	{
		dirx = cub->pdx * cos(M_PI_2) - cub->pdy * sin(M_PI_2);
		diry = cub->pdx * sin(M_PI_2) + cub->pdy * cos(M_PI_2);
	}
	else if (x == 1 && y == 1)
	{
		dirx = cub->pdx * cos(-M_PI_4) - cub->pdy * sin(-M_PI_4);
		diry = cub->pdx * sin(-M_PI_4) + cub->pdy * cos(-M_PI_4);
	}
	else if (x == 1 && y == -1)
	{
		dirx = cub->pdx * cos(-M_PI_4) - cub->pdy * sin(-M_PI_4);
		diry = cub->pdx * sin(-M_PI_4) + cub->pdy * cos(-M_PI_4);
	}
	else if (x == 0 && y == 1)
	{
		dirx = cub->pdx * cos(M_PI) - cub->pdy * sin(M_PI);
		diry = cub->pdx * sin(M_PI) + cub->pdy * cos(M_PI);
	}
		else if (x == 0 && y == -1)
	{
		dirx = cub->pdx * cos(0) - cub->pdy * sin(0);
		diry = cub->pdx * sin(0) + cub->pdy * cos(0);
	}
	else if (x == -1 && y == 0)
	{
		dirx = cub->pdx * cos(-M_PI_2) - cub->pdy * sin(-M_PI_2);
		diry = cub->pdx * sin(-M_PI_2) + cub->pdy * cos(-M_PI_2);
	}
	else if (x == -1 && y == 1)
	{
		dirx = cub->pdx * cos(M_PI_4) - cub->pdy * sin(M_PI_4);
		diry = cub->pdx * sin(M_PI_4) + cub->pdy * cos(M_PI_4);
	}
	else
	{
		dirx = cub->pdx * cos(M_PI + M_PI_4) - cub->pdy * sin(M_PI + M_PI_4);
		diry = cub->pdx * sin(M_PI + M_PI_4) + cub->pdy * cos(M_PI + M_PI_4);
	}
	// cub->play_x += 0.5;
	// cub->play_y += 0.5;
	// cub->minimap_x += cub->pdx;
	// cub->minimap_y += cub->pdy;
	if (x || y)
	{
	// printf("Dir x[%f]y[%f]\n", dirx, diry);
	// printf("Old pos x[%f]y[%f]\n", cub->minimap_x, cub->minimap_y);
		cub->minimap_x += dirx * SPEED;
		cub->minimap_y += diry * SPEED;
	// printf("New pos x[%f]y[%f]\n", cub->minimap_x, cub->minimap_y);
	}
	cub->step_x = x;
	cub->step_y = y;
}

int	scuffed_move_down(int key, t_cub *cub)
{
	cub->key_w = 0;
	cub->key_a = 0;
	cub->key_s = 0;
	cub->key_d = 0;
	cub->key_r = 0;
	cub->key_l = 0;
	// printf("key = %d\n", key);
	if (key == KEY_ESC)
		exit(0);
	if (key == KEY_W)
		cub->key_w = 1;
	if (key == KEY_A)
		cub->key_a = 1;
	if (key == KEY_S)
		cub->key_s = 1;	
	if (key == KEY_D)
		cub->key_d = 1;
	if (key == KEY_R)
		cub->key_r = 1;
	if (key == KEY_L)
		cub->key_l = 1;
	map_move_player(cub, cub->key_d - cub->key_a, cub->key_s - cub->key_w);
	// mlx_clear_window(cub->mlx, cub->mlx_w);
	create_image(cub, &cub->map_outline, CUB_W, CUB_H);
	raycasting(cub);
	print_minimap(cub);
	mlx_clear_window(cub->mlx, cub->mlx_w);
	mlx_put_image_to_window(cub->mlx, cub->mlx_w, cub->map_outline.img, 0, 0);
	mlx_destroy_image(cub->mlx, cub->map_outline.img);
	return (0);
}

int	scuffed_move_up(int key, t_cub *cub)
{
	if (key == KEY_W)
		cub->key_w = 0;
	if (key == KEY_A)
		cub->key_a = 0;
	if (key == KEY_S)
		cub->key_s = 0;
	if (key == KEY_D)
		cub->key_d = 0;
	return (0);
}

void	init_mlx(t_cub *cub)
{
	cub->key_w = 0;
	cub->key_a = 0;
	cub->key_s = 0;
	cub->key_d = 0;

	
	cub->plane_x = 0;
	cub->plane_y = 0.66;
	cub->time = 0;
	cub->old_time = 0;
	cub->rot_speed = 0.1;

	cub->mlx = mlx_init();
	cub->mlx_w = mlx_new_window(cub->mlx, CUB_W, CUB_H, "Cub3d");
	search_player(cub);
	create_image(cub, &cub->map_outline, CUB_W, CUB_H);
	raycasting(cub);
	print_minimap(cub);
	mlx_clear_window(cub->mlx, cub->mlx_w);
	mlx_put_image_to_window(cub->mlx, cub->mlx_w, cub->map_outline.img, 0, 0);
	mlx_destroy_image(cub->mlx, cub->map_outline.img);
	mlx_hook(cub->mlx_w, 2, 1, scuffed_move_down, cub);
	mlx_hook(cub->mlx_w, 3, 1, scuffed_move_up, cub);
	mlx_loop(cub->mlx);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	if (parse_file(ac, av, &cub))
		return (1);
	print_vars(cub);
	init_mlx(&cub);
}
