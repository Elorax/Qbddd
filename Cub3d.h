/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:04:41 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/01 17:08:14 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include "minilibx/mlx.h"
# include "minilibx/mlx_int.h"
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

typedef int t_pixel;

typedef struct s_image
{
	void	*img;
	int		height;
	int		width;
	t_pixel	**pix;
}	t_image;


typedef struct s_data
{
	int	fd;
	char	**map;
	char	*path_north;
	char	*path_south;
	char	*path_east;
	char	*path_west;
	t_pixel	Fcolor;
	t_pixel	Ccolor;
	int		nb_param;
	int		begin_map;
	int		end_map;
	int		map_size;
	void	*mlx;
	void	*win;
	t_image	img[4];
}	t_data;

# define R_KEY 114
# define W_KEY 119
# define A_KEY 97
# define Z_KEY 122
# define P_KEY 112
# define Q_KEY 113
# define S_KEY 115
# define D_KEY 100
# define ESCAPE_KEY 65307
# define UP_KEY 65362
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define DOWN_KEY 65364

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
int	exit_hook(t_data *data);
int	key_hook(int keycode, t_data *data);
void	manage_movement(t_data *data, int keycode);
void	ft_mlx_close_game(t_data *data);
void	ft_mlx_close_croix_rouge_de_ses_morts(t_data *data);


#endif
