/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:30:58 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/13 14:00:41 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

//key_hook.c

int	exit_hook(t_data *data)
{
	ft_mlx_close_croix_rouge_de_ses_morts(data);
	return (0);
}

int	handle_no_event(t_data *data)
{
	if (data->mouse_pressed || data->left_pressed)
	{
		mlx_mouse_get_pos(data->mlx, data->win, &data->mouse_x, &data->mouse_y);
		data->diff_x = data->mouse_prec_x - data->mouse_x;
		data->mouse_prec_x = data->mouse_x;
		if (data->mouse_x < 50 || data->mouse_x > 750)
		{
			mlx_mouse_move(data->mlx, data->win, 400, 300);
			data->mouse_prec_x = 400;
		}
	}
	if (data->player->is_jumping == 0)
		update_movements(data);
	update_stamina(data);
	if (data->player->is_jumping)
		update_jump(data);
	data->player->ms = calcul_movespeed(data);
	update_player(data);
	create_big(data);
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == W_KEY || keycode == UP_KEY)
		data->move->try_move_y--;
	else if (keycode == S_KEY || keycode == DOWN_KEY)
		data->move->try_move_y++;
	else if (keycode == A_KEY || keycode == D_KEY)
		data->move->try_move_x += 1 - 2 * (keycode == A_KEY);
	else if (keycode == LEFT_KEY || keycode == RIGHT_KEY)
		data->move->rotate += 1 - 2 * (keycode == LEFT_KEY);
	else if (keycode == SHIFT_KEY)
		data->player->try_sprint = 1;
	else if (keycode == CTRL_KEY)
		data->player->zoom = ZOOM_FORCE;
	else if (keycode == SPACE_BAR && !data->player->is_jumping)
	{
		data->player->z_speed = INITIAL_Z_SPEED;
		data->player->z_accel = -data->player->z_speed
			* data->player->z_speed * (1.0 / (2.0 * JUMP_HEIGHT));
		data->player->is_jumping = 1;
		data->begin = clock();
		data->current = data->begin;
		data->begin_ms = data->begin / (CLOCKS_PER_SEC / 1000);
		data->current_ms = data->begin_ms;
	}
	return (keycode);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == ESCAPE_KEY)
		ft_mlx_close_game(data);
	else if (keycode == W_KEY || keycode == UP_KEY)
		data->move->try_move_y++;
	else if (keycode == S_KEY || keycode == DOWN_KEY)
		data->move->try_move_y--;
	else if (keycode == A_KEY || keycode == D_KEY)
		data->move->try_move_x -= 1 - 2 * (keycode == A_KEY);
	else if (keycode == LEFT_KEY)
		data->move->rotate++;
	else if (keycode == RIGHT_KEY)
		data->move->rotate--;
	else if (keycode == CTRL_KEY)
		data->player->zoom = 1;
	else if (keycode == SHIFT_KEY)
		data->player->try_sprint = 0;
	return (keycode);
}
