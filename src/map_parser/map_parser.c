/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:16:58 by ralves-g          #+#    #+#             */
/*   Updated: 2023/01/11 22:21:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_name(char *name)
{
	int	len;
	int	fd;

	len = ft_strlen(name);
	if (len < 5 || name[len - 4] != '.' || name[len - 3] != 'c'
		|| name[len - 2] != 'u' || name[len - 1] != 'b')
	{
		printf("Error\nMap name needs to end with \".cub\"\n");
		return (1);
	}
	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nCouldn't open file\n");
		return (1);
	}
	close(fd);
	return (0);
}

int	add_texture(char *line, t_cub *cub, int *var, int type)
{
	printf("add_texture type: %d, line: %s\n", type, line);
	if (cub->walls[type])
	{
		printf("Error\nDuplicated texture: %s\n", line);
		free(line);
		return (1);
	}
	// Maybe check here if textures have a valid path
	cub->walls[type] = ft_strdup(line + 3);
	*var -= 1;
	free(line);
	return (0);
}

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
		printf("Error\nRBG color values need to be >= 0 && <= 255");
		free_matrix(rgb);
		return (1);
	}
	cub->color[type] = (r << 16) + (g << 8) + b;
	*var -= 1;
	free_matrix(rgb);
	return (0);
}

int	add_fc(char *line, t_cub *cub, int *var, int type)
{
	char	**rgb;
	int		i;

	printf("add_fc type: %d, line: %s\n", type, line);
	i = 0;
	if (cub->color[type] != -1)
	{
		printf("Error\nDuplicated color: %s\n", line);
		free(line);
		return (1);
	}
	rgb = ft_split(line + 2, ',');
	while (rgb[i])
		i++;
	if (i != 3)
	{
		printf("Error\nInvalid color format: %s", line + 2);
		free(line);
		return (1);
	}
	free(line);
	return (get_color(rgb, cub, var, type));
}

int	check_for_var(char *line, t_cub *cub, int *var)
{
	if (!ft_strlen(line))
		return (0);
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
	return (1);
}

int	parse_variables(char *name, t_cub *cub, int var)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(name, O_RDONLY);
	while (var)
	{
		line = get_map(fd);
		i++;
		if (!line || check_for_var(line, cub, &var))
		{
			printf("Error\nMap is not correctly configured, ");
			printf("Stopped at line %d\n", i);
			return (1);
		}
	}
	return (0);
}

int	parse_map(int ac, char **av, t_cub *cub)
{
	if (ac != 2)
	{
		printf("Error\nExpected 1 argument recieved: %d\n", ac - 1);
		return (1);
	}
	init_cub(cub);
	if (check_name(av[1]))
		return (1);
	if (parse_variables(av[1], cub, 6))
	{
		
	}
	{return (1);
	}
	return (0);
}
