/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:30:58 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/13 14:05:03 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

//update_player.c

void	update_stamina(t_data *data)
{
	if (data->player->sprint)
		data->player->stamina--;
	else
		data->player->stamina++;
	if (data->player->stamina <= 0)
	{
		data->player->can_sprint = 0;
		if (data->player->is_jumping == 0)
			data->player->sprint = 0;
		data->player->stamina = 0;
	}
	if (data->player->stamina >= 250)
		data->player->can_sprint = 1;
	if (data->player->stamina >= 500)
		data->player->stamina = 500;
}

void	update_movements(t_data *data)
{
	data->move->move_y = data->move->try_move_y;
	data->move->move_x = data->move->try_move_x;
	data->player->sprint = data->player->try_sprint;
	if (!data->move->move_y && !data->move->move_x)
		data->player->sprint = 0;
	if (data->player->can_sprint == 0)
		data->player->sprint = 0;
}

void	update_jump(t_data *data)
{
	data->current = clock();
	data->current_ms = data->current / (CLOCKS_PER_SEC / 1000);
	data->time_diff = (data->current_ms - data->begin_ms) / 1000.0;
	data->player->height = (data->player->z_accel / 2) * data->time_diff
		* data->time_diff + data->player->z_speed * data->time_diff;
	if (data->player->height < 0)
	{
		data->player->height = 0;
		data->player->is_jumping = 0;
		data->player->dirY = data->player->lookingY;
		data->player->dirX = data->player->lookingX;
	}
}

void	update_player_direction(t_data *data)
{
	if (data->player->is_jumping == 0)
	{
		data->player->dirX = data->player->lookingX;
		data->player->dirY = data->player->lookingY;
	}
}

void	update_player(t_data *data)
{
	update_player_y(data);
	update_player_x(data);
	update_player_rotation(data);
	update_player_direction(data);
}
