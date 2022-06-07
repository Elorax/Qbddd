/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:25:01 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/07 00:28:38 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_player	player;

	data.player = &player;
	if (is_arg_valid(ac, av) == FALSE)
		return (EXIT_FAILURE);
	init_data(&data);
	data.fd = open(av[1], O_RDONLY);
	if (data.fd < 0)
		return (printf("Error : File descriptor invalid\n"), 0);
	read_map_parameters(&data);
	count_map_size(&data);
	read_map(&data, av[1]);
	print_data(data);
	close(data.fd);
	if (check_map(data.map, &data))
		printf("Map safe, skip voting\n");
	else
		return (free_data(&data), printf("This map is sus\n"), 0);
	data.mlx = mlx_init();
	if (!data.mlx)
		return (free_data(&data), printf("mlx init failed\n"), 0);
	if (!init_images(&data, data.img))
		return (free_data(&data), printf("img not loaded\n"), 0);
	data.win = mlx_new_window(data.mlx, W_LENGTH, W_HEIGHT, "OMG OMG OMG OMG");
	if (!data.win)
		return (free_data(&data), printf("window creation failed\n"), 0);
	mlx_put_image_to_window(data.mlx, data.win, data.img[0].img, 0, 0);
	create_big(&data);
//	osef(&data.img[0], &data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_hook(data.win, 17, 0, exit_hook, &data);
	mlx_loop(data.mlx);
	free_data(&data);
	return (0);
}
