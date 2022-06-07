/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:30:58 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/01 17:01:34 by abiersoh         ###   ########.fr       */
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
	printf("Je me lance omg\n");
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
	if (data->move->move_x == -1)
	{
		if (data->map[(int)(data->player->posY)][(int)(data->player->posX - data->player->dirY * MOVESPEED/100)] != '1')
			data->player->posX -= data->player->dirY * MOVESPEED / 100;
		if (data->map[(int)(data->player->posY + data->player->dirX * MOVESPEED/100)][(int)(data->player->posX)] != '1')
			data->player->posY += data->player->dirX * MOVESPEED / 100;
	}
	else if (data->move->move_x == 1)
	{
		if (data->map[(int)(data->player->posY)][(int)(data->player->posX + data->player->dirY * MOVESPEED/100)] != '1')
			data->player->posX += data->player->dirY * MOVESPEED / 100;
		if (data->map[(int)(data->player->posY - data->player->dirX * MOVESPEED/100)][(int)(data->player->posX)] != '1')
			data->player->posY -= data->player->dirX * MOVESPEED / 100;
	}
	if (data->move->rotate == -1)
	{
		double tmp = data->player->dirX;
		data->player->dirX = data->player->dirX * cos(ROTSPEED/10) - data->player->dirY * sin(ROTSPEED/10);
		data->player->dirY = tmp * sin(ROTSPEED/10) + data->player->dirY * cos(ROTSPEED/10);
		tmp = data->player->planeX;
		data->player->planeX = tmp * cos(ROTSPEED/10) - data->player->planeY * sin(ROTSPEED/10);
		data->player->planeY = tmp * sin(ROTSPEED/10) + data->player->planeY * cos(ROTSPEED/10);
	}
	else if (data->move->rotate == 1)
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
	printf("%d %d %d\n", data->move->move_x, data->move->move_y, data->move->rotate);

	return (keycode);
}

int	key_release(int keycode, t_data *data)
{
		printf("%d released\n", keycode);
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

