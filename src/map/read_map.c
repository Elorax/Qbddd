/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:06:22 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/12 16:15:09 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Cub3d.h"

void	read_player(t_player *player, int i, int j, char **map)
{
	player->posX = j;
	player->posY = i;
	player->dirX = (map[i][j] == 'E') - (map[i][j] == 'W');
	player->dirY = (map[i][j] == 'S') - (map[i][j] == 'N');
	player->lookingX = player->dirX;
	player->lookingY = player->dirY;
	player->planeX = -player->dirY * tan((FOV / 2) * PI / 180.0);
	player->planeY = player->dirX * tan((FOV / 2) * PI / 180.0);
	player->zoom = 1;
	player->height = 0;
	player->z_speed = 0;
	player->z_accel = 0;
	player->is_jumping = 0;
	player->sprint = 0;
	player->try_sprint = 0;
	player->stamina = 500;
	player->can_sprint = 1;
	player->ms = 0;
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
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if (ft_strchr("0NSEW", map[i][j]))
				if (!check_around_zero(map, i, j))
					return (printf("%d%d\n", i, j), FALSE);
			if (!ft_strchr("20NSEW1 ", map[i][j]))
					return (printf("%d%d\n", i, j), FALSE);
			if (ft_strchr("NSEW", map[i][j]))
			{
				nb_player++;
				read_player(data->player, i, j, map);
			}
			j++;
		}
	}
//	printf("%d ??\n", nb_player);
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

char	*insert(char *str, char c, int idx, int nb_insert)
{
	char	*dest;

	if (idx > (int)ft_strlen(str))
		return (str);
	dest = malloc(ft_strlen(str) + nb_insert);
	if (!dest)
	{
		free(str);
		return (NULL);
	}
	int	i;
	i = 0;
	int	j;
	j = 0;
	while (str[i] && i < idx)
	{
		dest[i] = str[i];
		i++;
	}
	while (j < nb_insert)
		dest[i + j++] = c;
	while (str[i])
	{
			dest[i + j] = str[i];
			i++;
	}
	free(str);
//	printf("%s\n", dest);
	return (dest);
}

void	fill_with_spaces(char **map, t_data *data)
{
	int	i;
	i = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) - 1 < data->map_length)
		{
			map[i] = insert(map[i], ' ', ft_strlen(map[i]) - 1, 10);
			printf("lala%s", map[i]);
		}

		i++;
	}
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
	data->map_length = 0;
	while (++i < data->map_size)
	{
		data->map[i] = get_next_line(data->fd);
	//	printf("line : %s", data->map[i]);
		if (!data->map[i])
			printf("Ooopsiiiee\n");
		if (data->map_length < (int)ft_strlen(data->map[i]) - 1)
			data->map_length = ft_strlen(data->map[i]) - 1;
	//	printf("size : %d\n", data->map_length);
	}
	//printf("size : %d\n", data->map_length);
	data->map[data->map_size] = NULL;
	fill_with_spaces(data->map, data);
	close(data->fd);
}
