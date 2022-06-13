/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:11:35 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/13 13:48:19 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

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
