/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:25:01 by abiersoh          #+#    #+#             */
/*   Updated: 2022/05/30 18:32:19 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;

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
	if (check_map(data.map))
		printf("Map safe, skip voting\n");
	else
		printf("This map is sus\n");
	free_data(&data);
	return (0);
}
