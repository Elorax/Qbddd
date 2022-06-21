/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 23:21:58 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/12 15:29:38 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	init_image(t_data *data, t_image *img, char *path)
{
	img->img = mlx_xpm_file_to_image(data->mlx, path,
			&img->width, &img->height);
	if (img->img)
		img->addr = mlx_get_data_addr(img->img, &img->bpp,
				&img->line_length, &img->endian);
	img->path = ft_strdup(path);
}

int	init_images(t_data *data, t_image *img)
{
	init_image(data, &img[0], data->path_north);
	init_image(data, &img[1], data->path_south);
	init_image(data, &img[2], data->path_east);
	init_image(data, &img[3], data->path_west);
	init_image(data, &img[4], "./text/pikapika.xpm");
	return (img[0].img && img[1].img && img[2].img && img[3].img && img[4].img);
}

int	init_frames(t_data *data)
{
	data->render[0].height = W_HEIGHT;
	data->render[0].width = W_LENGTH;
	data->render[0].img = mlx_new_image(data->mlx, W_LENGTH, W_HEIGHT);
	if (data->render[0].img)
		data->render[0].addr = mlx_get_data_addr(data->render[0].img,
				&data->render[0].bpp, &data->render[0].line_length,
				&data->render[0].endian);
	data->render[1].height = W_HEIGHT;
	data->render[1].width = W_LENGTH;
	data->render[1].img = mlx_new_image(data->mlx, W_LENGTH, W_HEIGHT);
	if (data->render[0].img)
		data->render[1].addr = mlx_get_data_addr(data->render[1].img,
				&data->render[1].bpp, &data->render[1].line_length,
				&data->render[1].endian);
	return (data->render[0].img && data->render[1].img);
}
