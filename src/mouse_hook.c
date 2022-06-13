/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:30:58 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/13 14:30:34 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	mouse_press(int keycode, t_data *data)
{
	int	x;
	int	y;
	printf("pressing %d\n", keycode);
	if (keycode == RIGHT_CLICK)
		mlx_mouse_get_pos(data->mlx, data->win, &x, &y);
	printf("%d, %d\n", x, y);
	return (0);
}

int	mouse_release(int keycode, t_data *data)
{
	printf("releasing %d\n", keycode);
	(void)data;
	if (keycode == RIGHT_CLICK)
		mlx_mouse_show(data->mlx, data->win);
	return (0);
}