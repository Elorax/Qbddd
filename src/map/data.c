/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:05:57 by abiersoh          #+#    #+#             */
/*   Updated: 2022/05/30 18:33:01 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Cub3d.h"

void	free_data(t_data *data)
{
	free(data->path_north);
	free(data->path_south);
	free(data->path_east);
	free(data->path_west);
	ft_freesplit(data->map);
	return ;
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
	printf("Fcolor: %#X\n", data.Fcolor);
	printf("Ccolor: %#X\n", data.Ccolor);
	i = 0;
	while (data.map[i])
		printf("%s", data.map[i++]);
}

void	init_data(t_data *data)
{
	data->path_north = NULL;
	data->path_south = NULL;
	data->path_east = NULL;
	data->path_west = NULL;
	data->map = NULL;
	data->Fcolor = COLOR_UNSET;
	data->Ccolor = COLOR_UNSET;
	data->nb_param = 0;
}
