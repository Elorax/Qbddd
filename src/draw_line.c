/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:11:35 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/13 14:01:29 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

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

void	calcul_wall_drawing(t_raycasting *ray, t_player *player, int nb_wall)
{
	double	line_height;

	if (ray->dist_perp_wall == 0)
		line_height = 1000000;
	else
		line_height = (W_HEIGHT / ray->dist_perp_wall);
	ray->upper_wall = W_HEIGHT / 2 - (1 / (1 + player->height))
		* line_height * (28.0 * player->zoom / FOV)
		+ player->height * line_height / 2.0;
	ray->lower_wall = W_HEIGHT / 2 + ((2 - (1 / (1 + player->height))))
		* line_height * (28.0 * player->zoom / FOV)
		+ player->height * line_height / 2.0;
	if (ray->facing % 4 == EAST || ray->facing % 4 == WEST)
		ray->x_pix_wall = (double) player->posY
			+ ray->dist_perp_wall * ray->ray_dir_y;
	else
		ray->x_pix_wall = (double) player->posX
			+ ray->dist_perp_wall * ray->ray_dir_x;
	ray->x_pix_wall -= floor(ray->x_pix_wall);
	if (!(ray->facing % 2))
		ray->x_pix_wall = 1 - ray->x_pix_wall;
	ray->line[nb_wall].upper_wall = ray->upper_wall;
	ray->line[nb_wall].lower_wall = ray->lower_wall;
	ray->line[nb_wall].x_pix_wall = ray->x_pix_wall;
}
