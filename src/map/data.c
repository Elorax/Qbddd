/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:05:57 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/12 16:13:06 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Cub3d.h"

void	free_data(t_data *data)
{
	free(data->path_north);
	free(data->path_south);
	free(data->path_east);
	free(data->path_west);
	if (data->img[0].img)
		mlx_destroy_image(data->mlx, data->img[0].img);
	if (data->img[1].img)
		mlx_destroy_image(data->mlx, data->img[1].img);
	if (data->img[2].img)
		mlx_destroy_image(data->mlx, data->img[2].img);
	if (data->img[3].img)
		mlx_destroy_image(data->mlx, data->img[3].img);
	if (data->img[4].img)
		mlx_destroy_image(data->mlx, data->img[4].img);
	if (data->render[0].img)
		mlx_destroy_image(data->mlx, data->render[0].img);
	if (data->render[1].img)
		mlx_destroy_image(data->mlx, data->render[1].img);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	ft_freesplit(data->map);
	free(data->mlx);
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
	data->img[0].img = NULL;
	data->img[1].img = NULL;
	data->img[2].img = NULL;
	data->img[3].img = NULL;
	data->img[4].img = NULL;
	data->render[0].img = NULL;
	data->render[1].img = NULL;
	data->mlx = NULL;
	data->frame = 0;
}
