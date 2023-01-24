/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:20:45 by ralves-g          #+#    #+#             */
/*   Updated: 2023/01/24 13:45:00 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
				cub->play_x = x * MAP_UNIT;
				cub->play_y = y * MAP_UNIT;
			}
			x++;
		}
		y++;
	}
	printf("PLAYER X[%d] Y[%d]\n", cub->play_x, cub->play_y);
}

void	map_move_player(t_cub *cub, int x, int y)
{
	cub->play_x += x * MAP_UNIT / 2;
	cub->play_y += y * MAP_UNIT / 2;
}

int	scuffed_move_down(int key, t_cub *cub)
{
	cub->key_w = 0;
	cub->key_a = 0;
	cub->key_s = 0;
	cub->key_d = 0;
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
	map_move_player(cub, cub->key_d - cub->key_a, cub->key_s - cub->key_w);
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
	create_image(cub, &cub->map_outline, CUB_W, CUB_H);
	// create_outline(cub);
	// printf("Outline created!\n");
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
