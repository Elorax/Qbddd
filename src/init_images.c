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
	img[0].img = mlx_xpm_file_to_image(data->mlx, data->path_north,
			&img[0].width, &img[0].height);
	img[0].addr = mlx_get_data_addr(img[0].img, &img[0].bpp, &img[0].line_length, &img[0].endian);
	img[1].img = mlx_xpm_file_to_image(data->mlx, data->path_south,
			&img[1].width, &img[1].height);
	img[1].addr = mlx_get_data_addr(img[1].img, &img[1].bpp, &img[1].line_length, &img[1].endian);

	img[2].img = mlx_xpm_file_to_image(data->mlx, data->path_east,
			&img[2].width, &img[2].height);
	img[2].addr = mlx_get_data_addr(img[2].img, &img[2].bpp, &img[2].line_length, &img[2].endian);

	img[3].img = mlx_xpm_file_to_image(data->mlx, data->path_west,
			&img[3].width, &img[3].height);
	img[3].addr = mlx_get_data_addr(img[3].img, &img[3].bpp, &img[3].line_length, &img[3].endian);

	return (img[0].img && img[1].img && img[2].img && img[3].img);
}


void	init_frames(t_data *data)
{
	data->render[0].height = W_HEIGHT;
	data->render[0].width = W_LENGTH;
	data->render[0].img = mlx_new_image(data->mlx, W_LENGTH, W_HEIGHT);
	data->render[0].addr = mlx_get_data_addr(data->render[0].img, &data->render[0].bpp, &data->render[0].line_length, &data->render[0].endian);
	data->render[1].height = W_HEIGHT;
	data->render[1].width = W_LENGTH;
	data->render[1].img = mlx_new_image(data->mlx, W_LENGTH, W_HEIGHT);
	data->render[1].addr = mlx_get_data_addr(data->render[1].img, &data->render[1].bpp, &data->render[1].line_length, &data->render[1].endian);
}