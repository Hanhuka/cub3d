/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:20:45 by ralves-g          #+#    #+#             */
/*   Updated: 2023/01/13 18:07:13 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_vars(t_cub cub)
{
	printf("North textute: %s\n", cub.walls[C_NO]);
	printf("East textute: %s\n", cub.walls[C_EA]);
	printf("South textute: %s\n", cub.walls[C_SO]);
	printf("West textute: %s\n", cub.walls[C_WE]);
	printf("Ceiling color: %d\n", cub.color[CEILING]);
	printf("Floor color: %d\n", cub.color[FLOOR]);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	if (parse_file(ac, av, &cub))
		return (1);
	// print_vars(cub);
	for (int i = 0; i < 4; i++)
	{
		if (cub.walls[i])
			free(cub.walls[i]);
	}
}
