/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_prints.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:29:13 by ralves-g          #+#    #+#             */
/*   Updated: 2023/01/19 15:04:18 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_matrix(char **matrix)
{
	int	y;
	int	x;

	(void)x;
	y = 0;
	if (!matrix)
	{
		printf("NO MATRIX\n");
		return ;
	}
	while (matrix[y])
	{
		// x = 0;
		// while (matrix[y][x])
		// {
		// 	printf("%c", matrix[y][x]);
		// 	x++;
		// }
		// printf("        [%d]\n", y);
		printf("%s        [%d]\n", matrix[y], y);
		y++;
	}
}

void	print_vars(t_cub cub)
{
	printf("North textute: %s\n", cub.walls[C_NO]);
	printf("East textute: %s\n", cub.walls[C_EA]);
	printf("South textute: %s\n", cub.walls[C_SO]);
	printf("West textute: %s\n", cub.walls[C_WE]);
	printf("Ceiling color: %d\n", cub.color[CEILING]);
	printf("Floor color: %d\n", cub.color[FLOOR]);
	print_matrix(cub.map);
}
