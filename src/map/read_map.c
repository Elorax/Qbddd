/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:06:22 by abiersoh          #+#    #+#             */
/*   Updated: 2022/05/30 18:34:05 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Cub3d.h"

void	read_player(t_player *player, int i, int j, char **map)
{
	player->posX = j;
	player->posY = i;
	player->dirX = (map[i][j] == 'E') - (map[i][j] == 'W');
	player->dirY = (map[i][j] == 'S') - (map[i][j] == 'N');
	player->planeX = - player->dirY * tan(FOV * PI/180);
	player->planeY = player->dirX * tan(FOV * PI/180.0);
	printf("X, Y, dirX, dirY, planeX, planeY\n%f, %f, %f, %f, %f, %f\n", player->posX, player->posY, player->dirX, player->dirY, player->planeX, player->planeY);
}

int	check_map(char **map, t_data *data)
{
	int	nb_player;
	int	i;
	int	j;

	nb_player = 0;
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
			if (ft_strchr("NSEW", map[i][j]))
			{
				nb_player++;
				read_player(data->player, i, j, map);
			}
		}
	}
	return (nb_player == 1);
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
			exit((free_data(data), free(line),
					printf("Error : Wrong informations\n"), EXIT_FAILURE));
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
	data->begin_map = (free(line), i);
}

void	count_map_size(t_data *data)
{
	char	*line;

	line = get_next_line(data->fd);
	data->end_map = data->begin_map;
	while (line && (ft_strchr(line, '1') || ft_strchr(line, ' ')))
	{
		free(line);
		line = get_next_line(data->fd);
		data->end_map++;
	}
	while (line)
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
		exit((free_data(data), printf("MALLOC C'EST A CHIER\n"), EXIT_FAILURE));
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
