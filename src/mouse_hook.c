/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:30:58 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/20 08:29:29 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	mouse_press(int keycode, int x, int y, t_data *data)
{
	printf("pressing %d\n", keycode);
	if (keycode == RIGHT_CLICK)
	{
		data->mouse_initial_x = x;
		data->mouse_initial_y = y;
		data->mouse_pressed = 1;
		printf("pressed at x, y : %d, %d\n", x, y);
		mlx_mouse_hide(data->mlx, data->win);
	}
	else if (keycode == LEFT_CLICK)
	{
		data->left_pressed++;
	}
	if (data->left_pressed && data->mouse_pressed)
		data->move->try_move_y--;
	return (0);
}

int	mouse_release(int keycode, int x, int y, t_data *data)
{
	if (keycode == RIGHT_CLICK)
	{
		printf("released at x, y : %d, %d\n", x, y);
		mlx_mouse_show(data->mlx, data->win);
		data->mouse_pressed = 0;
		if (data->left_pressed)
			data->move->try_move_y++;
	}
	else if (keycode == LEFT_CLICK)
	{
		data->left_pressed--;
		if (data->mouse_pressed)
			data->move->try_move_y++;
	}

	return (0);
}
