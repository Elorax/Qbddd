/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:11:35 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/10 11:09:33 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"


double	double_abs(double d)
{
	if (d < 0)
		return (-d);
	return (d);
}

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
	//	printf("%d > %d\n", data->player->stamina / (W_LENGTH / 6), x - (W_LENGTH / 2 - W_LENGTH / 12));
		if (data->player->stamina * 71 / (W_LENGTH / 3) > x - (W_LENGTH / 2 - W_LENGTH / 12))
		{
			y = W_HEIGHT / 100 * 90 + 5;
			while (y < W_HEIGHT / 100 * 95)
			{
				pixel_put(img, x, y, 0xFFFF00 / (1 + !data->player->can_sprint));
				y++;
			}			
		}
		x++;
	}

}

void	staminamina_heyhey(t_image *img, t_data *data)
{
	/*int	y;
	int	x;*/


	draw_bar_1(img, data);
	draw_bar_2(img, data);
	fill_bar(img, data);
	/*for (y = 500; y < 505; y++)
		for (x = 345; x < 455; x++)
	for (y = 550; y < 555; y++)
		for (x = 345; x < 455; x++)*/
/*	for (x = 345; x < 350; x++)
		for (y = 500; y < 550; y++)
	for (x = 450; x < 455; x++)
		for (y = 500; y < 550; y++)*/


	/*for(x = 350; x < 450; x++)
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
	}*/
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

int	is_in_circle(int y, int ray, int x_to_center)
{

	if (x_to_center < 0)
		x_to_center *= -1;
	if (sqrt((double) (x_to_center * x_to_center) + (double)(W_HEIGHT / 2.0 - (double)(y)) * (double)(W_HEIGHT / 2.0 - (double)y)) < (double)(ray))
		return (1);
	return (0);
}

void	get_intersec(int x, int ray, int *up, int *down)
{
	int	y;

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

void	draw_black(t_image *img)
{
	int	x;
	int	up;
	int	down;	//Conserver un tableau d'up et down apres premier appel ? static ?
	x = -1;
	while (++x < W_LENGTH)
	{
		if (x < 51 || x > 749)
			draw_black_line(img, x, -1, -1);
		else
		{
			get_intersec(x, 200, &up, &down);
			draw_black_line(img, x, up, down);
		}

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
		draw_line(img, data, x, &ray);
	}
	if (data->player->zoom > 1)
		draw_black(img);
	else
		staminamina_heyhey(img, data);
}

void	draw_line(t_image *img, t_data *data, int x, t_raycasting *ray)
{
	int	y;
	int	x_img;
	t_image	*texture;

	texture = &data->img[ray->facing];
	x_img = floor(ray->x_pix_wall * (double) texture->width);
	if (x_img < 0)
		x_img = 0;
	if (x_img >= texture->width)
		x_img = texture->width - 1;
	y = 0;
	while (y < ray->upper_wall && y < W_HEIGHT / 2)
		pixel_put(img, x, y++, data->Ccolor);
	while (y < ray->upper_wall && y < W_HEIGHT)
		pixel_put(img, x, y++, data->Fcolor);
	while (y < ray->lower_wall && y < W_HEIGHT)
	{
		pixel_put(img, x, y, get_color(texture, x_img,
				texture->width * (y - ray->upper_wall)
				/ (ray->lower_wall - ray->upper_wall)));
		y++;
	}
	while (y < W_HEIGHT)
		pixel_put(img, x, y++, data->Fcolor);
	return ;
}
