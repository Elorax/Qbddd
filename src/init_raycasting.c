/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:31:08 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/08 20:38:25 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	init_raycasting(int x, t_raycasting *ray, t_player *player)
{
	ray->ray_x = 2 * x / (double)(W_HEIGHT) - 1;
	ray->ray_dir_x = player->dirX + (player->planeX / player->zoom) * ray->ray_x;
	ray->ray_dir_y = player->dirY + (player->planeY / player->zoom) * ray->ray_x;

	ray->map_x = (int) player->posX;
	ray->map_y = (int) player->posY;
	ray->has_hit = 0;
}

void	calcul_dist(t_raycasting *ray)
{
	if (ray->ray_dir_x == 0)
		ray->diff_dist_x = 1e30;
	else
		ray->diff_dist_x = double_abs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->diff_dist_y = 1e30;
	else
		ray->diff_dist_y = double_abs(1 / ray->ray_dir_y);
}

void	calcul_initial_dist(t_raycasting *ray, t_player *player)
{
		if (ray->ray_dir_x < 0)
		{
			ray->step_x = -1;
			ray->side_dist_x = (player->posX - ray->map_x) * ray->diff_dist_x;
		}
		else
		{
			ray->step_x = 1;
			ray->side_dist_x = (ray->map_x + 1.0 - player->posX) * ray->diff_dist_x;
		}
		if (ray->ray_dir_y < 0)
		{
			ray->step_y = -1;
			ray->side_dist_y = (player->posY - ray->map_y) * ray->diff_dist_y;
		}
		else
		{
			ray->step_y = 1;
			ray->side_dist_y = (ray->map_y + 1.0 - player->posY) * ray->diff_dist_y;
		}
}


void	casting_ray(t_raycasting *ray, t_data *data)
{
	while (!ray->has_hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->diff_dist_x;
			ray->map_x += ray->step_x;
			ray->facing = EAST + (ray->ray_dir_x > 0);
		}
		else
		{
			ray->side_dist_y += ray->diff_dist_y;
			ray->map_y += ray->step_y;
			ray->facing = NORTH + (ray->ray_dir_y < 0);
		}
		if (data->map[ray->map_y][ray->map_x] == '1')
			ray->has_hit = 1;
		if (data->map[ray->map_y][ray->map_x] == '2')
		{
			ray->has_hit = 1;
			ray->facing += MESSAGE;
		}
	}
}

double	calcul_perpendiculary_dist(t_raycasting ray)
{
	if (ray.facing % 4 == EAST || ray.facing % 4 == WEST)
		return (ray.side_dist_x - ray.diff_dist_x);
	return (ray.side_dist_y - ray.diff_dist_y);
}

void	calcul_wall_drawing(t_raycasting *ray, t_player *player)
{
	int	line_height;
	if (ray->dist_perp_wall == 0)
		line_height = 1000000;
	else
		line_height = (int) (W_HEIGHT / ray->dist_perp_wall);
	ray->upper_wall = W_HEIGHT / 2 - (1 / (1 + player->height)) * line_height * (28.0 * player->zoom/FOV) ;	//+/- offset
	ray->lower_wall = W_HEIGHT / 2 + ((2 - (1 / (1 + player->height)))) * line_height * (28.0 * player->zoom/FOV);	//+/- offset

	
	if (ray->facing % 4 == EAST || ray->facing % 4 == WEST)
		ray->x_pix_wall = (double) player->posY + ray->dist_perp_wall * ray->ray_dir_y;
	else
		ray->x_pix_wall = (double) player->posX + ray->dist_perp_wall * ray->ray_dir_x;	
	ray->x_pix_wall -= floor(ray->x_pix_wall);

		//Bon ca c'est de la giga rustine qui fait degueuler mais osef
	if (!(ray->facing % 2))
		ray->x_pix_wall = 1 - ray->x_pix_wall;
}
