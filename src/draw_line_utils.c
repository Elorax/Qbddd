/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:11:35 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/13 13:45:59 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	draw_black(t_image *img)
{
	int			x;
	static int	up[W_LENGTH];
	static int	down[W_LENGTH];

	x = -1;
	while (++x < W_LENGTH)
	{
		if (x < 51 || x > 749)
			draw_black_line(img, x, -1, -1);
		else
		{
			get_intersec(x, 200, up + x, down + x);
			draw_black_line(img, x, up[x], down[x]);
		}
	}
}

void	draw_black_line(t_image *img, int x, int up, int down)
{
	int	y;

	y = 0;
	while (y < up)
		pixel_put(img, x, y++, 0);
	while (y < down)
		y++;
	while (y < W_HEIGHT)
		pixel_put(img, x, y++, 0);
}

int	init_draw_line(t_data *data, t_raycasting *ray,
		t_image **texture, int *x_img)
{
	int		i;
	int		y;
	t_image	*img;
	int		x;

	i = -1;
	x = x_img[10];
	img = &data->render[data->frame % 2];
	while (++i < 10)
	{
		texture[i] = &data->img[ray->line[i].facing % 4];
		if (data->player->zoom > 1 && !ft_strncmp(texture[i]->path, "./text/pokeball.xpm", 20))
			texture[i] = &data->img[4];
		x_img[i] = floor(ray->line[i].x_pix_wall * (double) texture[i]->width);
		if (x_img[i] < 0)
			x_img[i] = 0;
		if (x_img[i] >= texture[i]->width)
			x_img[i] = texture[i]->width - 1;
	}
	y = 0;
	while (y < ray->line[9].upper_wall && y
		< W_HEIGHT / 2 + (abs(W_LENGTH / 2 - x)) / 80)
		pixel_put(img, x, y++, data->Ccolor);
	while (y < ray->line[9].upper_wall && y < W_HEIGHT)
		pixel_put(img, x, y++, data->Fcolor);
	return (y);
}

void	put_the_good_pixel(t_image *img, int x, int y, t_data *data)
{
	if (y < W_HEIGHT / 2)
		pixel_put(img, x, y++, data->Ccolor);
	else
		pixel_put(img, x, y++, data->Fcolor);
}

int	draw_walls(t_data *data, t_raycasting *ray, t_image **texture, int *x_img)
{
	int		i;
	t_image	*img;
	int		x;
	int		y;

	x = x_img[10];
	y = x_img[11];
	img = &data->render[data->frame % 2];
	i = 10;
	while (--i > 0)
	{
		while (y < ray->line[i].lower_wall
			&& y < ray->line[i - 1].upper_wall && y < W_HEIGHT)
		{
			pixel_put(img, x, y, get_color(texture[i], x_img[i],
					texture[i]->width * (y - ray->line[i].upper_wall)
					/ (ray->line[i].lower_wall - ray->line[i].upper_wall)));
			y++;
		}
		while (y < ray->line[i - 1].upper_wall && y < W_HEIGHT)
			put_the_good_pixel(img, x, y++, data);
	}
	return (y);
}

