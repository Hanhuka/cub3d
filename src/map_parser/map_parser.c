/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:16:58 by ralves-g          #+#    #+#             */
/*   Updated: 2023/01/12 16:31:14 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	get_color(char **rgb, t_cub *cub, int *var, int type)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
	{
		printf("Error\nRBG color values need to be >= 0 && <= 255\n");
		free_matrix(rgb);
		return (1);
	}
	cub->color_check[type] = 1;
	cub->color[type] = (r << 16) + (g << 8) + b;
	printf("Color: R:%d G:%d B:%d UINT: %d\n",r, g, b, (r << 16) + (g << 8) + b);
	*var -= 1;
	free_matrix(rgb);
	return (0);
}

int	add_fc(char *line, t_cub *cub, int *var, int type)
{
	char	**rgb;
	int		i;

	i = 0;
	if (cub->color_check[type])
	{
		printf("Error\nDuplicated color: \"%s\"\n", line);
		return (1);
	}
	rgb = ft_split(line + 2, ',');
	while (rgb[i])
	{
		printf("rgb = %s\n", rgb[i]);
		i++;
	}
	if (i != 3)
	{
		printf("Error\nInvalid color format: \"%s\"", line + 2);
		return (1);
	}
	if (!get_color(rgb, cub, var, type))
	{
		free(line);
		return (0);
	}
	return (1);
}

int	check_for_var(char *line, t_cub *cub, int *var)
{
	if (!ft_strlen(line))
	{
		free(line);
		return (0);
	}
	if (check_equal(line, "NO "))
		return (add_texture(line, cub, var, C_NO));
	if (check_equal(line, "SO "))
		return (add_texture(line, cub, var, C_EA));
	if (check_equal(line, "WE "))
		return (add_texture(line, cub, var, C_SO));
	if (check_equal(line, "EA "))
		return (add_texture(line, cub, var, C_WE));
	if (check_equal(line, "F "))
		return (add_fc(line, cub, var, FLOOR));
	if (check_equal(line, "C "))
		return (add_fc(line, cub, var, CEILING));
	printf("Error\nLine does not match any variable\n");
	return (1);
}

int	parse_variables(t_cub *cub, int var, int fd)
{
	char	*line;
	int		i;

	init_cub(cub);
	i = 0;
	while (var)
	{
		line = get_map(fd);
		i++;
		if (!line)
		{
			parse_error(line, cub, "Error\nMap is not correctly configured, ");
			close(fd);
			printf("Stopped at line %d\n", i);
			return (1);
		}
		if (check_for_var(line, cub, &var))
		{
			parse_error(line, cub, NULL);
			close(fd);
			return (printf("Stopped at line %d\n", i));
		}
	}
	return (0);
}

int	parse_file(int ac, char **av, t_cub *cub)
{
	if (ac != 2)
	{
		printf("Error\nExpected 1 argument recieved: %d\n", ac - 1);
		return (1);
	}
	if (check_name(av[1]) || parse_variables(cub, 6, open(av[1], O_RDONLY)))
		return (1);
	return (0);
}
