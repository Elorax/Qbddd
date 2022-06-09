/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:11:35 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/08 19:26:53 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"


double	double_abs(double d)
{
	if (d < 0)
		return (-d);
	return (d);
}

void	draw_stamina_bar(t_image *img, t_data *data)
{
	int	y;
	int	x;

	for (y = 500; y < 505; y++)
	{
		for (x = 345; x < 455; x++)
		{
			pixel_put(img, x, y, 0xFFFF00 / (1 + !data->player->can_sprint));
		}
	}
	for (y = 550; y < 555; y++)
	{
		for (x = 345; x < 455; x++)
		{
			pixel_put(img, x, y, 0xFFFF00 / (1 + !data->player->can_sprint));
		}
	}
	for (x = 345; x < 350; x++)
	{
		for (y = 500; y < 550; y++)
		{
			pixel_put(img, x, y, 0xFFFF00 / (1 + !data->player->can_sprint));
		}
	}
	for (x = 450; x < 455; x++)
	{
		for (y = 500; y < 550; y++)
		{
			pixel_put(img, x, y, 0xFFFF00 / (1 + !data->player->can_sprint));
		}
	}
	for(x = 350; x < 450; x++)
	{
		if (data->player->stamina / 5 > x - 350)
		{
			for (y = 505; y < 550; y++)
			{
				pixel_put(img, x, y, 0xFFFF00 / (1 + !data->player->can_sprint));

			}
		}
		else
			break;
	}
}

void	build_image(t_image *img, t_data *data, t_player *player)
{
	int				x;
	t_raycasting	ray;

	x = -1;
	while (++x < W_LENGTH)
	{
		init_raycasting(x, &ray, player);
		calcul_dist(&ray);
		calcul_initial_dist(&ray, player);
		casting_ray(&ray, data);
		ray.dist_perp_wall = calcul_perpendiculary_dist(ray);
		calcul_wall_drawing(&ray, player);
		if (ray.facing > 3)
		ray.facing = 4;
		draw_line(img, data, ray.x_pix_wall, x, ray.upper_wall, ray.lower_wall, &data->img[ray.facing]);
	}
	draw_stamina_bar(img, data);
}

void	draw_line(t_image *img, t_data *data, double wallX, int x, int upperWall, int lowerWall, t_image *texture)
{
	int	y;
	int	x_img;

	x_img = floor(wallX * (double) texture->width);
	if (x_img < 0)
		x_img = 0;
	if (x_img >= texture->width)
		x_img = texture->width - 1;
	y = 0;
	while (y < upperWall && y < W_HEIGHT)
		pixel_put(img, x, y++, data->Ccolor);
	while (y < lowerWall && y < W_HEIGHT)
	{
		pixel_put(img, x, y, get_color(texture, x_img, texture->width * (y - upperWall) / (lowerWall - upperWall)));
		y++;
	}
	while (y < W_HEIGHT)
		pixel_put(img, x, y++, data->Fcolor);
	return ;
}
