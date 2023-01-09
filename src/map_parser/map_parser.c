/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:16:58 by ralves-g          #+#    #+#             */
/*   Updated: 2023/01/09 17:46:04 by ralves-g         ###   ########.fr       */
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

int	check_line(char *line)
{
	if (!line)
		return (-1);
	if (!ft_strlen(line))
	{
		free(line);
		return (0);
	}
	return (1);
}

int	parse_variables(char *name, t_cub *cub)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(name, O_RDONLY);
	line = get_map(fd);
	if (check_line(line) == -1)
	{
		printf("Error\n\"%s\" is not a correct map. Stopped at line %d\n", name, i);
		return (1);
	}
	if (check_line(line))
		;
	
	//NEED TO CHECK IF LINE IS VARIABLE
	while (line)
	{
		
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
	if (check_name(av[1]) || parse_variables(av[1], cub))
		return (1);
	return (0);
}
