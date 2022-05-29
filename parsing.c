#include "Cub3d.h"
char	*ft_strstr(const char *str, const char *tofind)
{
	size_t	i;
	size_t	j;
	size_t	find_len;

	if (!str || !tofind)
		return (NULL);
	find_len = ft_strlen(tofind);
	if (!(*tofind))
		return ((char *) str);
	j = 0;
	while (str[j])
	{
		i = 0;
		while (str[i + j] && (str[i + j] == tofind[i]))
		{
			i++;
			if (!tofind[i])
				return ((char *) (str + j));
		}
		j++;
	}
	return (NULL);
}

int	is_8bits_int(char *line)
{
	int	size = ft_strlen(line);
	if (size > 3 || size == 0)
		return (FALSE);
	int	i = -1;
	while (++i < size)
		if (!ft_isdigit(line[i]))
			return (FALSE);
	if (ft_atoi(line) > 255)
		return (FALSE);
	return (TRUE);
}

char	*ft_remove_newline_space(char *line)
{
	int	i;

	if (ft_strchr(line, '\n'))
		*ft_strchr(line, '\n') = 0;
	i = 0;
	while (line[i] == ' ')
		i++;
	return (ft_substr(line, i, ft_strlen(line) - i));
}

char	*ft_remove_newline(char *line)
{
	if (ft_strchr(line, '\n'))
		*ft_strchr(line, '\n') = 0;
	return (line);
}

int	read_color(char *line)
{
	int	res;
	int	i;
	char	**tmp;

	tmp = ft_split(line, ',');
	if (countchar(line, ',') != 2)
		exit((free_data(data), printf("COULEUR A CHIER\n"), ERROR_BAD_COLOR));
		
	if (!tmp)
		exit((free_data(data), printf("MALLOC A CHIER\n"), ERROR_FUCK_MALLOC));
	i = -1;
	res = 0;
	if (tmp[2] && ft_strchr(tmp[2], '\n'))
		ft_remove_newline(tmp[2]);
	while (++i < 3)
	{
		if (tmp[i] && is_8bits_int(tmp[i]))
		{
			res <<= 8;
			res += ft_atoi(tmp[i]);
		}
		else
			break;
	}
	if ((i == 3) && tmp[i] == NULL)
		return res;
	exit((free_data(data), printf("COULEUR A CHIER\n"), ERROR_BAD_COLOR));
}


int	read_line(char *line, t_data *data)
{
	if (ft_strstr(line, "NO ") == line)
		data->path_north = ft_remove_newline_space(ft_strstr(line, "NO ") + 3);
	else if (ft_strstr(line, "SO ") == line)
		data->path_south = ft_remove_newline_space(ft_strstr(line, "SO ") + 3);
	else if (ft_strstr(line, "EA ") == line)
		data->path_east = ft_remove_newline_space(ft_strstr(line, "EA ") + 3);
	else if (ft_strstr(line, "WE ") == line)
		data->path_west = ft_remove_newline_space(ft_strstr(line, "WE ") + 3);
	else if (ft_strstr(line, "F ") == line)
		data->Fcolor = read_color(line + 2);
	else if (ft_strstr(line, "C ") == line)
		data->Ccolor = read_color(line + 2);
	else
		return (0);
	return (1);
}

int	is_line_valid(char *line, t_data *data)
{
	if (!line)
		return (FALSE);
	if (ft_strstr(line, "NO ") == line
		&& ft_strlen(line) > 4 && !data->path_north)
		return (TRUE);
	else if (ft_strstr(line, "SO ") == line
		&& ft_strlen(line) > 4 && !data->path_south)
		return (TRUE);
	else if (ft_strstr(line, "EA ") == line
		&& ft_strlen(line) > 4 && !data->path_east)
		return (TRUE);
	else if (ft_strstr(line, "WE ") == line
		&& ft_strlen(line) > 4 && !data->path_west)
		return (TRUE);
	else if (ft_strstr(line, "F ") == line	
		&& ft_strlen(line) > 7 && data->Fcolor == COLOR_UNSET)
		return (TRUE);
	else if (ft_strstr(line, "C ") == line
		&& ft_strlen(line) > 7 && data->Ccolor == COLOR_UNSET)
		return (TRUE);
	else if (line[0] == '\n')
		return (TRUE);
	else
		return (FALSE);
}

int	check_around_zero(char **map, int i, int j)
{
	if (!j || !i)
		return (FALSE);
	if (map[i][j + 1] == '\n')
		return (FALSE);
	if (!map[i + 1])
		return (FALSE);
	if (ft_strlen(map[i - 1]) < j + 2)
		return (FALSE);
	if (ft_strlen(map[i + 1]) < j + 2)
		return (FALSE);
	if (!ft_strchr("10NSEW", map[i - 1][j - 1])
		|| !ft_strchr("10NSEW", map[i - 1][j])
		|| !ft_strchr("10NSEW", map[i - 1][j + 1])
		|| !ft_strchr("10NSEW", map[i][j - 1])
		|| !ft_strchr("10NSEW", map[i][j + 1]) 
		|| !ft_strchr("10NSEW", map[i + 1][j - 1])
		|| !ft_strchr("10NSEW", map[i + 1][j])
		|| !ft_strchr("10NSEW", map[i + 1][j + 1]))
		return (FALSE);
	return (TRUE);
}

int	check_around_space(char **map, int i, int j)
{
	if (i > 0 && j > 0 && ft_strlen(map[i - 1]) > j - 1)
		if (!ft_strchr("1 \n", map[i - 1][j - 1]))
			return (FALSE);
	if (i > 0 && ft_strlen(map[i - 1]) > j)
		if (!ft_strchr("1 \n", map[i - 1][j]))
			return (FALSE);
	if (i > 0 && ft_strlen(map[i - 1]) > j + 1)
		if (!ft_strchr("1 \n", map[i - 1][j + 1]))
			return (FALSE);
	if (j > 0)
		if (!ft_strchr("1 \n", map[i][j - 1]))
			return (FALSE);
	if (!ft_strchr("1 \n", map[i][j + 1]))
		return (FALSE);
	if (map[i + 1])
	{
		if (j > 0 && ft_strlen(map[i + 1]) > j - 1)
			if (!ft_strchr("1 \n", map[i + 1][j - 1]))
				return (FALSE);
		if (ft_strlen(map[i + 1]) > j)
			if (!ft_strchr("1 \n", map[i + 1][j]))
				return (FALSE);
		if (ft_strlen(map[i + 1]) > j + 1)
			if (!ft_strchr("1 \n", map[i + 1][j + 1]))
				return (FALSE);
	}
	return (TRUE);
}

int	check_map(char **map)
{
	int	nb_player;
	int	i;
	int	j;

//	j = 0;
	nb_player = 0;
/*	while (map[0][j] && map[0][j] != '\n')
	{
		if (!ft_strchr(" 1", map[0][j]))
			return (FALSE);
		j++;
	}*/
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j] != '\n')
		{
			if (ft_strchr("0NSEW", map[i][j]))
				if (!check_around_zero(map, i, j))
					return (FALSE);
			if (!ft_strchr("0NSEW1 ", map[i][j]))
				return (FALSE);
			nb_player += !!ft_strchr("NSEW", map[i][j]);
		}
	}
		return (nb_player == 1);
}

void	init_data(t_data *data)
{
	
	data->path_north = NULL;
	data->path_south = NULL;
	data->path_east = NULL;
	data->path_west = NULL;
	data->Fcolor = COLOR_UNSET;
	data->Ccolor = COLOR_UNSET;
	data->nb_param = 0;
}
int	check_args(int ac, char **av)
{
	if (ac != 2)
		return (printf("Error : argument count not valid\n"), 0);
	if (ft_strlen(ft_strstr(av[1], ".cub")) != ft_strlen(".cub"))
		return (printf("WRONG MAP NAME"), 0);
}

void	free_data(t_data *data)
{
	free(data->path_north);
	free(data->path_south);
	free(data->path_east);
	free(data->path_west);
	return ;
}

void	read_map_parameters(t_data *data)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(data->fd);
	while (data->nb_param < 6 && line)
	{
		if (!is_line_valid(line, data))
			exit((free_data(data), printf("Error : Wrong informations\n"),
				EXIT_FAILURE));
		data->nb_param += read_line(line, data);
		free(line);
		line = get_next_line(data->fd);
		i++;
	}
	if (data->nb_param < 6)
		exit((free_data(data), printf("Error : Wrong informations\n"),
			EXIT_FAILURE));
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(data->fd);
		i++;
	}
	data->begin_map = i;
}

void	count_map_size(t_data *data)
{
	char	*line;

	line = get_next_line(data->fd);
	data->end_map = data->begin_map;
	while (line && ft_strchr(line, '1'))
	{
		free(line);
		line = get_next_line(data->fd);
		data->end_map++;
	}
	while (line)				//On finit de lire le fichier.
	{
		if (line[0] != '\n')
			exit((free(line), free_data(data),
				printf("Error : Non-void line after map\n"), 0));
		free(line);
		line = get_next_line(data->fd);
	}
	close(data->fd);
}

void	read_map(t_data *data, char *path)
{
	int	i;

	data->fd = open(path, O_RDONLY);
	i = -1;
	while (++i < data->begin_map)
	{
		free(get_next_line(data->fd));
	}
	data->map_size = data->end_map - data->begin_map + 1;
	data->map = malloc(sizeof(char *) * (data->map_size + 1));
	if (!data->map)
		exit((free_data(data),printf("MALLOC C'EST A CHIER\n"), EXIT_FAILURE));
	i = -1;
	while (++i < data->map_size)
	{
		data->map[i] = get_next_line(data->fd);
		if (!data->map[i])
			printf("Ooopsiiiee\n");
	}
	data->map[data->map_size] = NULL;
	close(data->fd);
}


void	print_data(t_data data)
{
	int	i;

	printf("debut %d\n fin %d\n taille %d\n",
		data.begin_map, data.end_map, data.map_size);
	printf("north path: %s\n", data.path_north);
	printf("south path: %s\n", data.path_south);
	printf("east path: %s\n", data.path_east);
	printf("west path: %s\n", data.path_west);
	printf("Fcolor path: %#X\n", data.Fcolor);
	printf("Ccolor path: %#X\n", data.Ccolor);
	i = 0;
	while (data.map[i])
		printf("%s", data.map[i++]);
}

int main(int ac, char **av)
{
	int		fd;
	t_data	data;
	int		nb_param;

	nb_param = 0;
	if (check_args(ac, av) == FALSE)
		return (EXIT_FAILURE);
	init_data(&data);
	data.fd = open(av[1], O_RDONLY);
	if (data.fd < 0)
		return (printf("Error : File descriptor invalid\n"), 0);

	read_map_parameters(&data);
	count_map_size(&data);
	read_map(&data, av[1]);
	print_data(data);
	close(data.fd);
	if (check_map(data.map))
		printf("Map safe, skip voting\n");
	else
		printf("This map is sus\n");
	return (0);
}

