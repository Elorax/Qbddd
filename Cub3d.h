


#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
//# include "mlx/mlx.h"
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
}	t_data;

int	read_line(char *line, t_data *data);
int	read_color(char *line);
char	*ft_strstr(const char *str, const char *tofind);
int	is_8bits_int(char *line);
char	*ft_remove_newline_space(char *line);
char	*ft_remove_newline(char *line);
int	is_line_valid(char *line, t_data *data);
int	check_around_zero(char **map, int i, int j);
int	check_around_space(char **map, int i, int j);
int	check_map(char **map);


#endif
