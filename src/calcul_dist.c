/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_dist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:31:08 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/13 14:01:59 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

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
