/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stamina_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:11:35 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/13 13:43:57 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

//stamina_display.c

void	draw_bar_1(t_image *img, t_data *data)
{
	int	x;
	int	y;

	y = W_HEIGHT / 100 * 90;
	while (y < W_HEIGHT / 100 * 90 + 5)
	{
		x = W_LENGTH / 2 - W_LENGTH / 12 - 5;
		while (x < W_LENGTH / 2 + W_LENGTH / 12 + 5)
		{
			pixel_put(img, x, y, 0xFFFF00 / (1 + !data->player->can_sprint));
			x++;
		}
		y++;
	}
	y = W_HEIGHT / 100 * 95;
	while (y < W_HEIGHT / 100 * 95 + 5)
	{
		x = W_LENGTH / 2 - W_LENGTH / 12 - 5;
		while (x < W_LENGTH / 2 + W_LENGTH / 12 + 5)
		{
			pixel_put(img, x, y, 0xFFFF00 / (1 + !data->player->can_sprint));
			x++;
		}
		y++;
	}
}

void	draw_bar_2(t_image *img, t_data *data)
{
	int	x;
	int	y;

	x = W_LENGTH / 2 - W_LENGTH / 12 - 5;
	while (x < W_LENGTH / 2 - W_LENGTH / 12)
	{
		y = W_HEIGHT / 100 * 90;
		while (y < W_HEIGHT / 100 * 95)
		{
			pixel_put(img, x, y, 0xFFFF00 / (1 + !data->player->can_sprint));
			y++;
		}
		x++;
	}
	x = W_LENGTH / 2 + W_LENGTH / 12;
	while (x < W_LENGTH / 2 + W_LENGTH / 12 + 5)
	{
		y = W_HEIGHT / 100 * 90;
		while (y < W_HEIGHT / 100 * 95)
		{
			pixel_put(img, x, y, 0xFFFF00 / (1 + !data->player->can_sprint));
			y++;
		}
		x++;
	}
}

void	fill_bar(t_image *img, t_data *data)
{
	int	x;
	int	y;

	x = W_LENGTH / 2 - W_LENGTH / 12;
	while (x < W_LENGTH / 2 + W_LENGTH / 12)
	{
		if (W_LENGTH * 5 / 12 + ((W_LENGTH / 6)
				* data->player->stamina) / 500.0 > x)
		{
			y = W_HEIGHT / 100 * 90 + 5;
			while (y < W_HEIGHT / 100 * 95)
			{
				pixel_put(img, x, y, 0xFFFF00
					/ (1 + !data->player->can_sprint));
				y++;
			}			
		}
		x++;
	}
}

void	staminamina_heyhey(t_image *img, t_data *data)
{
	draw_bar_1(img, data);
	draw_bar_2(img, data);
	fill_bar(img, data);
}
