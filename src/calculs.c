/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:11:35 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/13 13:51:58 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

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

double	calcul_movespeed(t_data *data)
{
	double	ret;

	ret = (1 + 0.8 * data->player->sprint)
		* (1 + 0.3 * data->player->is_jumping)
		* (MOVESPEED / 100.0)
		* (1.0 - (0.293
				* (data->move->move_y && data->move->move_x)));
	if (ret > 0.8)
		ret = 0.8;
	return (ret);
}
