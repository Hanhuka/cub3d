/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:17:31 by ralves-g          #+#    #+#             */
/*   Updated: 2023/01/24 13:42:17 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "get_next_line.h"
# include "mlx-linux/mlx.h"

# define CEILING 1
# define FLOOR 0

# define C_NO 0
# define C_EA 1
# define C_SO 2
# define C_WE 3

//Window size: width and height
# define CUB_W 1920
//Window size: height
# define CUB_H 1080

//minimap defines
# define MAP_RADIUS 400
# define MAP_UNIT 20

# define MAP_X_CENTER 960
# define MAP_Y_CENTER 540
# define MAP_OUTLINE 5
# define MAP_OUTL_CLR 0xFFC500FF
# define PLAYER_RADIUS 5

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_cub {
	char				*walls[4];
	unsigned int		color[2];
	int					color_check[2];
	int					check_f;
	int					play_x;
	int					play_y;
	int					key_w;
	int					key_a;
	int					key_s;
	int					key_d;
	int					key_;
	char				**map;
	void				*mlx;
	void				*mlx_w;
	t_data				map_outline;
}	t_cub;

//testing_prints.c
void		print_matrix(char **matrix);
void		print_vars(t_cub cub);

//cub3d.c

//utils.c
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		create_image(t_cub *cub, t_data *data, int size_x, int size_y);

//print_minimap.c
void		print_minimap_wall(t_cub *cub, int m_x, int m_y);
void		print_outline(t_cub *cub);
void		print_minimap(t_cub *cub);

//minimap_raycasting.c
void		draw_vector(t_cub *cub, int start_x, int start_y, int dir_x, int dir_y);

//map_parser.c
int			get_color(char **rgb, t_cub *cub, int *var, int type);
int			add_fc(char *line, t_cub *cub, int *var, int type);
int			check_for_var(char *line, t_cub *cub, int *var);
int			parse_vars(t_cub *cub, int var, int fd);
int			parse_file(int ac, char **av, t_cub *cub);

//map_parser2.c
int			check_name(char *name);
int			add_texture(char *line, t_cub *cub, int *var, int type);
int			add_matrix(t_cub *cub, char *line);
int			check_line(char *line, int *player);
int			parse_map(t_cub *cub, int fd);

//mapp_parser3.c
int			check_map(t_cub *cub);

//map_parser_utils.c
int			has_char(char *str, char c);
char		*get_map(int fd);
void		init_cub(t_cub *cub);
char		*ft_strdup(char *str);
int			check_equal(char *line, char *test);

//map_parser_utils2.c
char		*ft_substr(char const *str, int start, int end);
char		**ft_split(char const *str, char c);
long int	ft_atoi(const char *str);
void		free_matrix(char **matrix);

//map_parser_utils3.c
int			parse_error(char *line, t_cub *cub, char *msg);
void		free_textures(t_cub cub);

#endif 