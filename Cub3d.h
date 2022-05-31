/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:04:41 by abiersoh          #+#    #+#             */
/*   Updated: 2022/05/31 02:20:24 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include "minilibx/mlx.h"
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# define TRUE 1
# define FALSE 0
# define COLOR_UNSET -1
# define ERROR_BAD_COLOR -2
# define ERROR_FUCK_MALLOC -3
# define ERROR_PARAMETERS  -4

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3


typedef struct s_image
{
	void	*img;
	int		height;
	int		width;
}	t_image;

typedef struct s_data
{
	int	fd;
	char	**map;
	char	*path_north;
	char	*path_south;
	char	*path_east;
	char	*path_west;
	int		Fcolor;
	int		Ccolor;
	int		nb_param;
	int		begin_map;
	int		end_map;
	int		map_size;
	void	*mlx;
	void	*win;
	t_image	img[4];
}	t_data;

int		init_images(t_data *data, t_image *img);
int		read_line(char *line, t_data *data);
int		read_color(char *line, t_data *data);
void	free_data(t_data *data);
char	*ft_strstr(const char *str, const char *tofind);
int		is_8bits_int(char *line);
char	*ft_remove_newline_space(char *line);
char	*ft_remove_newline(char *line);
int		is_line_valid(char *line, t_data *data);
int		check_around_zero(char **map, int i, int j);
int		check_map(char **map);
void	ft_freesplit(char **s);
int		countchar(char *line, char c);
char	**formatting_split(char *line, char sep, char *trim);
void	init_data(t_data *data);
int		is_arg_valid(int ac, char **av);
void	read_map_parameters(t_data *data);
void	count_map_size(t_data *data);
void	read_map(t_data *data, char *path);
void	print_data(t_data data);

#endif
