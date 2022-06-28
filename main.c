/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:25:01 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/12 14:56:05 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	init_movements(t_movements *move)
{
	move->move_x = 0;
	move->move_y = 0;
	move->rotate = 0;
	move->try_move_x = 0;
	move->try_move_y = 0;
}

void	reading(char *av,
			t_data *data, t_player *player, t_movements *move)
{
	data->player = player;
	data->move = move;
	init_data(data);
	init_movements(data->move);
	data->fd = open(av, O_RDONLY);
	if (data->fd < 0)
		exit((printf("Error\nFile descriptor invalid\n"), 0));
	read_map_parameters(data);
	count_map_size(data);
	read_map(data, av);
	//print_data(*data);
	close(data->fd);
	if (check_map(data->map, data))
		//printf("Map safe, skip voting\n");
		;
	else
		exit((free_data(data), printf("Error\nThis map is sus\n"), 0));
}

void	create_window(t_data *data, char *av)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit((free_data(data), printf("Error\nmlx init failed\n"), 0));
	if (!init_images(data, data->img))
		exit((free_data(data), printf("Error\nimg not loaded\n"), 0));
	if (!init_frames(data))
		exit((free_data(data), printf("Error\nmlx_new_image FAILED MISERABLY\n"), 0));
	data->win = mlx_new_window(data->mlx, W_LENGTH, W_HEIGHT, av);
	if (!data->win)
		exit((free_data(data), printf("Error\nwindow creation failed\n"), 0));
	create_big(data);
	mlx_loop_hook(data->mlx, handle_no_event, data);
	mlx_hook(data->win, 17, 0, exit_hook, data);
	mlx_hook(data->win, 02, (1L << 1), key_press, data);
	mlx_hook(data->win, 03, (1L << 0), key_release, data);
	mlx_hook(data->win, 04, (1L << 3), mouse_press, data);
	mlx_hook(data->win, 05, (1L << 2), mouse_release, data);

	mlx_do_key_autorepeatoff(data->mlx);
	mlx_loop(data->mlx);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_player	player;
	t_movements	move;

	if (is_arg_valid(ac, av) == FALSE)
		return (EXIT_FAILURE);
	data.mouse_initial_x = 0;
	data.mouse_initial_y = 0;
	data.mouse_pressed = 0;
	data.left_pressed = 0;
	data.mouse_x = 0;
	data.mouse_y = 0;
	data.img[0].path = NULL;
	data.img[1].path = NULL;
	data.img[2].path = NULL;
	data.img[3].path = NULL;
	data.img[4].path = NULL;
	reading(av[1], &data, &player, &move);
	create_window(&data, av[1]);
}
