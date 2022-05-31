/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 23:21:58 by abiersoh          #+#    #+#             */
/*   Updated: 2022/05/31 02:13:12 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	init_images(t_data *data, t_image *img)
{
	printf("omg !!\n");
	img[0].img = mlx_xpm_file_to_image(data->mlx, data->path_north,
			&img[0].width, &img[0].height);
	printf("omg !!\n");
	img[1].img = mlx_xpm_file_to_image(data->mlx, data->path_south,
			&img[1].width, &img[1].height);
	img[2].img = mlx_xpm_file_to_image(data->mlx, data->path_east,
			&img[2].width, &img[2].height);
	img[3].img = mlx_xpm_file_to_image(data->mlx, data->path_west,
			&img[3].width, &img[3].height);
	return (img[0].img && img[1].img && img[2].img && img[3].img);
}
