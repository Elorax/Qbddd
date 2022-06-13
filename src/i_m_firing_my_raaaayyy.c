/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_m_firing_my_raaaayyy.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:31:08 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/13 14:04:40 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	casting_ray(t_raycasting *ray, t_data *data, int nb_wall)
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
		if (ray->map_x < 0 || ray->map_y < 0 || ray->map_y >= data->map_size
			|| ray->map_x > data->map_length)
			return ;
		if (nb_wall % 2)
			ray->has_hit = !!ft_strchr("0NSEW",
					data->map[ray->map_y][ray->map_x]);
		else if (data->map[ray->map_y][ray->map_x] == '1')
			ray->has_hit = 1;
	}
	ray->line[nb_wall].facing = ray->facing;
	ray->dist_perp_wall = calcul_perpendiculary_dist(*ray);
}
