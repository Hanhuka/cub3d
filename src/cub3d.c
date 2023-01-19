/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:20:45 by ralves-g          #+#    #+#             */
/*   Updated: 2023/01/19 15:08:00 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// ( x − a )^2 + ( y − b )^2 = r^2

// pow(x - cub->play_x + CUB_W / 2 - play_x, 2) + pow(y - cub->play_y + CUB_W / 2 - play_y, 2) <= 90

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
			if ((pow(x - cub->play_x + CUB_W / 2 - CUB_W / 2, 2.0) + pow(y - cub->play_y + CUB_H / 2 - CUB_H / 2, 2.0)) <= pow(CUB_H / 2, 2.0))
				mlx_pixel_put(cub->mlx, cub->mlx_w, x - cub->play_x + CUB_W / 2, y -cub->play_y + CUB_H / 2, 0xFFFFFFFF);
			x += 1;
		}
		y += 1;
	}
}

void	print_minimap(t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if (cub->map[y][x] == '1')
				print_minimap_wall(cub, x * MAP_UNIT, y * MAP_UNIT);
			x++;
		}
		y++;
	}
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
			if (cub->map[y][x] == 'N' || cub->map[y][x] == 'S' || 
			cub->map[y][x] == 'W' || cub->map[y][x] == 'E')
			{
				cub->play_x = x * MAP_UNIT;
				cub->play_y = y * MAP_UNIT;
			}
			x++;
		}
		y++;
	}
	printf("PLAYER X[%d] Y[%d]\n", cub->play_x, cub->play_y);
}

void	move_player(t_cub *cub, int x, int y)
{
	cub->play_x += x * 10;
	cub->play_y += y * 10;
}

int	scuffed_move_down(int key, t_cub *cub)
{
	cub->key_w = 0;
	cub->key_a = 0;
	cub->key_s = 0;
	cub->key_d = 0;
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
	move_player(cub, cub->key_d - cub->key_a, cub->key_s - cub->key_w);
	mlx_clear_window(cub->mlx, cub->mlx_w);
	print_minimap(cub);
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
	cub->mlx = mlx_init();
	cub->mlx_w = mlx_new_window(cub->mlx, CUB_W, CUB_H, "Cub3d");
	search_player(cub);
	print_minimap(cub);
	// mlx_key_hook(cub->mlx_w, scuffed_move, cub);
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
