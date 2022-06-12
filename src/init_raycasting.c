/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:31:08 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/12 15:55:54 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

//init_raycasting.c

void	init_raycasting(int x, t_raycasting *ray, t_player *player)
{
	ray->ray_x = 2 * x / (double)(W_LENGTH) - 1;
	ray->ray_dir_x = player->lookingX
		+ (player->planeX / player->zoom) * ray->ray_x;
	ray->ray_dir_y = player->lookingY
		+ (player->planeY / player->zoom) * ray->ray_x;
	ray->map_x = (int) player->posX;
	ray->map_y = (int) player->posY;
	ray->has_hit = 0;
	ray->nb_wall = 0;
	for (int i = 0; i < 10; i++)
	{
		ray->line[i].facing = 0;
		ray->line[i].upper_wall = 0;
		ray->line[i].lower_wall = 0;
		ray->line[i].x_pix_wall = 0;
	}
}

//calcul_dist.c

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
		ray->side_dist_x = (player->posX - ray->map_x)
			* ray->diff_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->posX)
			* ray->diff_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->posY - ray->map_y)
			* ray->diff_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->posY)
			* ray->diff_dist_y;
	}
}

double	calcul_perpendiculary_dist(t_raycasting ray)
{
	if (ray.facing % 4 == EAST || ray.facing % 4 == WEST)
		return (ray.side_dist_x - ray.diff_dist_x);
	return (ray.side_dist_y - ray.diff_dist_y);
}

//I_m_firing_my_raaayyy.c
//nb_wall : walls to skip
//return nb walls rencontrés
int	casting_ray(t_raycasting *ray, t_data *data, int nb_wall)
{
	int	nb_hit;

	nb_hit = 0;
//	while (nb_hit < nb_wall + 1)
//	{
		//On cherche le prochain mur
		ray->has_hit = 0;
	//	int	old_facing = ray->facing;
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
			if (ray->map_x < 0 || ray->map_y < 0 || ray->map_y >= data->map_size || ray->map_x > data->map_length)
				{
					//ray->facing = old_facing;
					return (nb_hit);
				}
			if (nb_wall % 2)
			{
				if (ft_strchr("0NSEW", data->map[ray->map_y][ray->map_x]))
					ray->has_hit = 1;
			}
			else
			{
			if (data->map[ray->map_y][ray->map_x] == '1')
				{	
					ray->has_hit = 1;
				}
			}
		}


		ray->line[nb_wall].facing = ray->facing;
		printf("%d --> %d\n", ray->facing, ray->line[nb_wall].facing);
		ray->dist_perp_wall = calcul_perpendiculary_dist(*ray);
		//a changer
		nb_hit++;
		ray->has_hit = 0;
		//On cherche le prochain 0 ou espace cette fois
		/*while (!ray->has_hit)
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
			if (ray->map_x < 0 || ray->map_y < 0 || ray->map_y >= data->map_size || ray->map_x > data->map_length)
				return (nb_hit);
			if (ft_strchr("0 NSEW", data->map[ray->map_y][ray->map_x]))
			{	
				ray->has_hit = 1;
			}
		}*/
//	}
	return (nb_hit);
}

//draw_line.c

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
	//ray->line[nb_wall].facing = ray->facing;
}
