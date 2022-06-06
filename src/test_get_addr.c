/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_addr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:32:45 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/06 20:28:41 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	pixel_put(t_image *img, int x, int y, int color)
{
	char	*addr;

	addr = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *) addr = color;
}

int	get_color(t_image *img, int x, int y)
{
	char	*addr;

	addr = img->addr + (y * img->line_length + x * (img->bpp / 8));
	return (*(int *) addr);
}

void	create_big(t_data *data)
{
	t_image img;
	t_player	player;

	img.height = W_HEIGHT;
	img.width = W_LENGTH;
	img.img = mlx_new_image(data->mlx, W_LENGTH, W_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	printf("appel de build_image\n");
	build_image(&img, data, &player);
	mlx_put_image_to_window(data->mlx, data->win, img.img, 0, 0);
}