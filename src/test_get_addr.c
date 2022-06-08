/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_addr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:32:45 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/08 19:46:09 by abiersoh         ###   ########.fr       */
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
//	static int nb = 0;
//	printf("building image %d\n", nb++);
	build_image(&data->render[data->frame%2], data, data->player);
	mlx_put_image_to_window(data->mlx, data->win, data->render[data->frame++%2].img, 0, 0);
}
