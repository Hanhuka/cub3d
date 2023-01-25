/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:20:45 by ralves-g          #+#    #+#             */
/*   Updated: 2023/01/25 18:25:38 by ralves-g         ###   ########.fr       */
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
	cub->pa += (cub->key_r - cub->key_l) * 0.9;
	if (cub->pa < 0)
		cub->pa += 2 * M_PI;
	if (cub->pa > 2 * M_PI)
		cub->pa -= 2 * M_PI;
	cub->pdx = cos(cub->pa) * 5;
	cub->pdy = sin(cub->pa) * 5;
	printf("pdx = [%f] pdy  = [%f]\n", cub->pdx, cub->pdy);


	cub->play_x += 0.5;
	cub->play_y += 0.5;
	cub->minimap_x += x + cub->pdx;
	cub->minimap_y += y + cub->pdy;
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
	printf("key = %d\n", key);
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
	mlx_clear_window(cub->mlx, cub->mlx_w);
	print_minimap(cub);
	// raycasting(cub);
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

	cub->mlx = mlx_init();
	cub->mlx_w = mlx_new_window(cub->mlx, CUB_W, CUB_H, "Cub3d");
	search_player(cub);
	print_minimap(cub);
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
