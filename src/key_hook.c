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


int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESCAPE_KEY)
		ft_mlx_close_game(data);
	else if (keycode == W_KEY || keycode == A_KEY || keycode == S_KEY
		|| keycode == D_KEY || keycode == UP_KEY || keycode == DOWN_KEY
		|| keycode == RIGHT_KEY || keycode == LEFT_KEY
		|| keycode == Z_KEY || keycode == Q_KEY)
		manage_movement(data, keycode);
	return (keycode);
}

void	manage_movement(t_data *data, int keycode)
{
	(void) data;
	printf("keycode %d\n", keycode);
	return ;
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

