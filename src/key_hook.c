/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:30:58 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/12 16:11:31 by abiersoh         ###   ########.fr       */
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
	else if (keycode == LEFT_KEY)
		data->move->rotate--;
	else if (keycode == RIGHT_KEY)
		data->move->rotate++;
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

//utils.c ou calculs.c

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

//movements_player.c

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

//rotation.c

void	rotate_right(t_data *data)
{
	double	tmp;

	tmp = data->player->lookingX;
	data->player->lookingX = data->player->lookingX * cos(ROTSPEED / 10)
		- data->player->lookingY * sin(ROTSPEED / 10);
	data->player->lookingY = tmp * sin(ROTSPEED / 10)
		+ data->player->lookingY * cos(ROTSPEED / 10);
	tmp = data->player->planeX;
	data->player->planeX = tmp * cos(ROTSPEED / 10)
		- data->player->planeY * sin(ROTSPEED / 10);
	data->player->planeY = tmp * sin(ROTSPEED / 10)
		+ data->player->planeY * cos(ROTSPEED / 10);
}

void	rotate_left(t_data *data)
{
	double	tmp;

	tmp = data->player->lookingX;
	data->player->lookingX = data->player->lookingX * cos(-ROTSPEED / 10)
		- data->player->lookingY * sin(-ROTSPEED / 10);
	data->player->lookingY = tmp * sin(-ROTSPEED / 10)
		+ data->player->lookingY * cos(-ROTSPEED / 10);
	tmp = data->player->planeX;
	data->player->planeX = tmp * cos(-ROTSPEED / 10)
		- data->player->planeY * sin(-ROTSPEED / 10);
	data->player->planeY = tmp * sin(-ROTSPEED / 10)
		+ data->player->planeY * cos(-ROTSPEED / 10);
}

void	update_player_rotation(t_data *data)
{
	if (data->move->rotate == 1)
		rotate_right(data);
	else if (data->move->rotate == -1)
		rotate_left(data);
}

//close_window.c

void	ft_mlx_close_game(t_data *data)
{	
	mlx_do_key_autorepeaton(data->mlx);
	if (data->win != NULL)
	{
		mlx_clear_window(data->mlx, data->win);
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	free_data(data);
	exit(EXIT_SUCCESS);
}

void	ft_mlx_close_croix_rouge_de_ses_morts(t_data *data)
{
	t_xvar	*ptr;

	if (data->win != NULL)
	{
		mlx_clear_window(data->mlx, data->win);
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
		ptr = (t_xvar *)(data->mlx);
		ptr->end_loop = 1;
	}
	free_data(data);
	exit(EXIT_SUCCESS);
}
