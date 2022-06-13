/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:11:35 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/13 03:03:19 by abiersoh         ###   ########.fr       */
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

//calculs.c

int	is_in_circle(int y, int ray, int x_to_center)
{
	if (x_to_center < 0)
		x_to_center *= -1;
	if (sqrt((double)(x_to_center * x_to_center) + (double)(W_HEIGHT
		/ 2.0 - (double)(y)) *(double)(W_HEIGHT
			/ 2.0 - (double)(y))) < (double)(ray))
		return (1);
	return (0);
}

void	get_intersec(int x, int ray, int *up, int *down)
{
	int	y;

	if (*up)
		return ;
	y = 0;
	while (!is_in_circle(y, ray, 250 - x)
		&& !is_in_circle(y, ray, 550 - x)
		&& y < W_HEIGHT / 2)
		y++;
	if (y >= W_HEIGHT / 2)
	{
		*up = -1;
		*down = -1;
	}
	else
	{
		*up = y;
		*down = W_HEIGHT - y;
	}
}

double	double_abs(double d)
{
	if (d < 0)
		return (-d);
	return (d);
}

//draw_line.c
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

//build_image.c

void	build_image(t_image *img, t_data *data, t_player *player)
{
	int				x;
	t_raycasting	ray;
	int				i;
	int				max;

	x = -1;
	while (++x < W_LENGTH)
	{
		init_raycasting(x, &ray, player);
		calcul_dist(&ray);
		calcul_initial_dist(&ray, player);
		i = -1;
		max = 1 + 9 * (player->height > 0.44);
		while (++i < max)
		{
			ray.has_hit = 0;
			casting_ray(&ray, data, i);
			calcul_wall_drawing(&ray, player, i);
		}
		draw_line(img, data, x, &ray);
	}
	if (data->player->zoom > 1)
		draw_black(img);
	else
		staminamina_heyhey(img, data);
}

//draw_line.c

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

void	draw_line(t_image *img, t_data *data, int x, t_raycasting *ray)
{
	int		x_img[12];
	t_image	*texture[10];
	int		y;

	x_img[10] = x;
	x_img[11] = init_draw_line(data, ray, texture, x_img);
	x_img[11] = draw_walls(data, ray, texture, x_img);
	y = x_img[11];
	while (y < ray->line[0].lower_wall && y < W_HEIGHT)
	{
		pixel_put(img, x, y, get_color(texture[0], x_img[0],
				texture[0]->width * (y - ray->line[0].upper_wall)
				/ (ray->line[0].lower_wall - ray->line[0].upper_wall)));
		y++;
	}
	while (y < W_HEIGHT)
		pixel_put(img, x, y++, data->Fcolor);
}
