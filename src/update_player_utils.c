/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:30:58 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/13 13:59:13 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	update_player_y(t_data *data)
{
	if (data->move->move_y < 0)
	{
		if (data->map[(int)(data->player->posY)][(int)(data->player->posX
				+ data->player->dirX * data->player->ms)] != '1')
			data->player->posX += data->player->dirX * data->player->ms;
		if (data->map[(int)(data->player->posY + data->player->dirY
				* data->player->ms)][(int)(data->player->posX)] != '1')
			data->player->posY += data->player->dirY * data->player->ms;
	}
	else if (data->move->move_y > 0)
	{
		if (data->map[(int)(data->player->posY)][(int)(data->player->posX
				- data->player->dirX * data->player->ms)] != '1')
			data->player->posX -= data->player->dirX * data->player->ms;
		if (data->map[(int)(data->player->posY - data->player->dirY
				* data->player->ms)][(int)(data->player->posX)] != '1')
			data->player->posY -= data->player->dirY * data->player->ms;
	}
}

void	update_player_x(t_data *data)
{
	if (data->move->move_x > 0)
	{
		if (data->map[(int)(data->player->posY)][(int)(data->player->posX
				- data->player->dirY * data->player->ms)] != '1')
			data->player->posX -= data->player->dirY * data->player->ms;
		if (data->map[(int)(data->player->posY + data->player->dirX
				* data->player->ms)][(int)(data->player->posX)] != '1')
			data->player->posY += data->player->dirX * data->player->ms;
	}
	else if (data->move->move_x < 0)
	{
		if (data->map[(int)(data->player->posY)][(int)(data->player->posX
				+ data->player->dirY * data->player->ms)] != '1')
			data->player->posX += data->player->dirY * data->player->ms;
		if (data->map[(int)(data->player->posY - data->player->dirX
				* data->player->ms)][(int)(data->player->posX)] != '1')
			data->player->posY -= data->player->dirX * data->player->ms;
	}
}

void	rotate_right(t_data *data, int diff)
{
	double	tmp;

	tmp = data->player->lookingX;
	data->player->lookingX = data->player->lookingX * cos((ROTSPEED / 10) * diff)
		- data->player->lookingY * sin((ROTSPEED / 10) * diff);
	data->player->lookingY = tmp * sin((ROTSPEED / 10) * diff)
		+ data->player->lookingY * cos((ROTSPEED / 10) * diff);
	tmp = data->player->planeX;
	data->player->planeX = tmp * cos((ROTSPEED / 10) * diff)
		- data->player->planeY * sin((ROTSPEED / 10) * diff);
	data->player->planeY = tmp * sin((ROTSPEED / 10) * diff)
		+ data->player->planeY * cos((ROTSPEED / 10) * diff);
}

void	rotate_left(t_data *data, int diff)
{
	double	tmp;

	tmp = data->player->lookingX;
	data->player->lookingX = data->player->lookingX * cos(-(ROTSPEED / 10) * diff)
		- data->player->lookingY * sin(-(ROTSPEED / 10) * diff);
	data->player->lookingY = tmp * sin(-(ROTSPEED / 10) * diff)
		+ data->player->lookingY * cos(-(ROTSPEED / 10) * diff);
	tmp = data->player->planeX;
	data->player->planeX = tmp * cos(-(ROTSPEED / 10) * diff)
		- data->player->planeY * sin(-(ROTSPEED / 10) * diff);
	data->player->planeY = tmp * sin(-(ROTSPEED / 10) * diff)
		+ data->player->planeY * cos(-(ROTSPEED / 10) * diff);
}

void	update_player_rotation(t_data *data)
{
	if (!data->mouse_pressed)
	{
		if (data->move->rotate == 1)
			rotate_right(data, 3);
		else if (data->move->rotate == -1)
			rotate_left(data, 3);
	}
	else
	{
		if (data->diff_x > 0)
		{
			rotate_left(data, data->diff_x);
		}	
		else if (data->diff_x < 0)
			rotate_right(data, -data->diff_x);

	}
}
