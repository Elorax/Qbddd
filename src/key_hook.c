/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:30:58 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/08 19:42:54 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	exit_hook(t_data *data)
{
	ft_mlx_close_croix_rouge_de_ses_morts(data);
	return (0);
}

/*
void	manage_movement(t_data *data, int keycode)
{
	(void) data;
	(void) keycode;
	printf("keycode %d\n", keycode);
	if (keycode == UP_KEY || keycode == W_KEY)
	{
		if (data->map[(int)(data->player->posY)][(int)(data->player->posX + data->player->dirX * MOVESPEED/10)] != '1')
			data->player->posX += data->player->dirX * MOVESPEED / 10;
		if (data->map[(int)(data->player->posY + data->player->dirY * MOVESPEED/10)][(int)(data->player->posX)] != '1')
			data->player->posY += data->player->dirY * MOVESPEED / 10;
		create_big(data);
	}
	else if (keycode == DOWN_KEY || keycode == S_KEY)
	{
		data->player->posX -= data->player->dirX * MOVESPEED / 10;
		data->player->posY -= data->player->dirY * MOVESPEED / 10;
		create_big(data);
	}
	else if (keycode == A_KEY)
	{
		data->player->posX -= data->player->dirY * MOVESPEED / 10;
		data->player->posY += data->player->dirX * MOVESPEED / 10;
		create_big(data);
	}
	else if (keycode == D_KEY)
	{
		data->player->posX += data->player->dirY * MOVESPEED / 10;
		data->player->posY -= data->player->dirX * MOVESPEED / 10;
		create_big(data);
	}
	else if (keycode == LEFT_KEY)
	{
		double tmp = data->player->dirX;
		data->player->dirX = data->player->dirX * cos(ROTSPEED) - data->player->dirY * sin(ROTSPEED);
		data->player->dirY = tmp * sin(ROTSPEED) + data->player->dirY * cos(ROTSPEED);
		tmp = data->player->planeX;
		data->player->planeX = tmp * cos(ROTSPEED) - data->player->planeY * sin(ROTSPEED);
		data->player->planeY = tmp * sin(ROTSPEED) + data->player->planeY * cos(ROTSPEED);
		create_big(data);
	}
	else if (keycode == RIGHT_KEY)
	{
		double tmp = data->player->dirX;
		data->player->dirX = data->player->dirX * cos(-ROTSPEED) - data->player->dirY * sin(-ROTSPEED);
		data->player->dirY = tmp * sin(-ROTSPEED) + data->player->dirY * cos(-ROTSPEED);
		tmp = data->player->planeX;
		data->player->planeX = tmp * cos(-ROTSPEED) - data->player->planeY * sin(-ROTSPEED);
		data->player->planeY = tmp * sin(-ROTSPEED) + data->player->planeY * cos(-ROTSPEED);
		create_big(data);
	}
	return ;
}*/

int	handle_no_event(t_data *data)
{
//	printf("Je me lance omg\n");
	if (data->player->is_jumping)
	{
		data->current = clock();
		data->current_ms = data->current / (CLOCKS_PER_SEC / 1000);
		data->time_diff = (data->current_ms - data->begin_ms) / 1000.0;
		printf("time_diff : %f\n", data->time_diff);
	//	data->player->z_speed = data->player->z_accel * (data->current_ms - data->begin_ms) + INITIAL_Z_SPEED;
	//	data->player->z_speed /= 1000;
		data->player->height = (data->player->z_accel / 2) * data->time_diff * data->time_diff + data->player->z_speed * data->time_diff;
		printf("Height : %f\n", data->player->height);
		if (data->player->height < 0)
		{
			data->player->height = 0;
			data->player->is_jumping = 0;
		}
	}
	if (data->move->move_y == -1)
	{
		if (data->map[(int)(data->player->posY)][(int)(data->player->posX + data->player->dirX * MOVESPEED/100)] != '1')
			data->player->posX += data->player->dirX * MOVESPEED / 100;
		if (data->map[(int)(data->player->posY + data->player->dirY * MOVESPEED/100)][(int)(data->player->posX)] != '1')
			data->player->posY += data->player->dirY * MOVESPEED / 100;
	}
	else if (data->move->move_y == 1)
	{
		if (data->map[(int)(data->player->posY)][(int)(data->player->posX - data->player->dirX * MOVESPEED/100)] != '1')
			data->player->posX -= data->player->dirX * MOVESPEED / 100;
		if (data->map[(int)(data->player->posY - data->player->dirY * MOVESPEED/100)][(int)(data->player->posX)] != '1')
			data->player->posY -= data->player->dirY * MOVESPEED / 100;
	}
	if (data->move->move_x == 1)
	{
		printf("%d, %d\n", (int) data->player->posY, (int) (data->player->posX - data->player->dirY * MOVESPEED/100));
		if (data->map[(int)(data->player->posY)][(int)(data->player->posX - data->player->dirY * MOVESPEED/100)] != '1')
			data->player->posX -= data->player->dirY * MOVESPEED / 100;
		if (data->map[(int)(data->player->posY + data->player->dirX * MOVESPEED/100)][(int)(data->player->posX)] != '1')
			data->player->posY += data->player->dirX * MOVESPEED / 100;
	}
	else if (data->move->move_x == -1)
	{
		printf("%d, %d\n", (int) data->player->posY, (int) (data->player->posX + data->player->dirY * MOVESPEED/100));
		if (data->map[(int)(data->player->posY)][(int)(data->player->posX + data->player->dirY * MOVESPEED/100)] != '1')
			data->player->posX += data->player->dirY * MOVESPEED / 100;
		if (data->map[(int)(data->player->posY - data->player->dirX * MOVESPEED/100)][(int)(data->player->posX)] != '1')
			data->player->posY -= data->player->dirX * MOVESPEED / 100;
	}
	if (data->move->rotate == 1)
	{
		double tmp = data->player->dirX;
		data->player->dirX = data->player->dirX * cos(ROTSPEED/10) - data->player->dirY * sin(ROTSPEED/10);
		data->player->dirY = tmp * sin(ROTSPEED/10) + data->player->dirY * cos(ROTSPEED/10);
		tmp = data->player->planeX;
		data->player->planeX = tmp * cos(ROTSPEED/10) - data->player->planeY * sin(ROTSPEED/10);
		data->player->planeY = tmp * sin(ROTSPEED/10) + data->player->planeY * cos(ROTSPEED/10);
	}
	else if (data->move->rotate == -1)
	{
		double tmp = data->player->dirX;
		data->player->dirX = data->player->dirX * cos(-ROTSPEED/10) - data->player->dirY * sin(-ROTSPEED/10);
		data->player->dirY = tmp * sin(-ROTSPEED/10) + data->player->dirY * cos(-ROTSPEED/10);
		tmp = data->player->planeX;
		data->player->planeX = tmp * cos(-ROTSPEED/10) - data->player->planeY * sin(-ROTSPEED/10);
		data->player->planeY = tmp * sin(-ROTSPEED/10) + data->player->planeY * cos(-ROTSPEED/10);
	}
	create_big(data);
	return (0);

}

int	key_press(int keycode, t_data *data)
{
	printf("%d pressed\n", keycode);
	
	if (keycode == W_KEY || keycode == UP_KEY)
		data->move->move_y = -1;
	else if (keycode == S_KEY || keycode == DOWN_KEY)
		data->move->move_y = 1;
	if (keycode == A_KEY)
		data->move->move_x = -1;
	else if (keycode == D_KEY)
		data->move->move_x = 1;
	if (keycode == LEFT_KEY)
		data->move->rotate = -1;
	else if (keycode == RIGHT_KEY)
		data->move->rotate = 1;
	if (keycode == CTRL_KEY)
		data->player->zoom = ZOOM_FORCE;
	if (keycode == SPACE_BAR && !data->player->is_jumping)
	{
		data->player->z_speed = INITIAL_Z_SPEED;
		data->player->z_accel = -data->player->z_speed * data->player->z_speed * (1.0/(2.0 * JUMP_HEIGHT));
		data->player->is_jumping = 1;
		data->begin = clock();
		data->current = data->begin;
		data->begin_ms = data->begin / (CLOCKS_PER_SEC / 1000);
		data->current_ms = data->begin_ms;
	}
//	printf("%d %d %d\n", data->move->move_x, data->move->move_y, data->move->rotate);

	return (keycode);
}

int	key_release(int keycode, t_data *data)
{
//		printf("%d released\n", keycode);
	if (keycode == ESCAPE_KEY)
		ft_mlx_close_game(data);
	if (keycode == W_KEY || keycode == UP_KEY)
		data->move->move_y = 0;
	else if (keycode == S_KEY || keycode == DOWN_KEY)
		data->move->move_y = 0;
	if (keycode == A_KEY)
		data->move->move_x = 0;
	else if (keycode == D_KEY)
		data->move->move_x = 0;
	if (keycode == LEFT_KEY)
		data->move->rotate = 0;
	else if (keycode == RIGHT_KEY)
		data->move->rotate = 0;
	if (keycode == CTRL_KEY)
		data->player->zoom = 1;
	if (keycode == SPACE_BAR && data->player->is_jumping && data->player->height == 0)
	{
		data->player->is_jumping = 0;
	}
	return (keycode);
}

void	ft_mlx_close_game(t_data *data)
{
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

