/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:31:08 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/13 14:04:48 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

//init_raycasting.c

void	init_raycasting(int x, t_raycasting *ray, t_player *player)
{
	int	i;

	i = -1;
	ray->ray_x = 2 * x / (double)(W_LENGTH) - 1;
	ray->ray_dir_x = player->lookingX
		+ (player->planeX / player->zoom) * ray->ray_x;
	ray->ray_dir_y = player->lookingY
		+ (player->planeY / player->zoom) * ray->ray_x;
	ray->map_x = (int) player->posX;
	ray->map_y = (int) player->posY;
	ray->has_hit = 0;
	ray->nb_wall = 0;
	while (++i < 10)
	{
		ray->line[i].facing = 0;
		ray->line[i].upper_wall = 0;
		ray->line[i].lower_wall = 0;
		ray->line[i].x_pix_wall = 0;
	}
}
