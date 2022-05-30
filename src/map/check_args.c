/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:05:47 by abiersoh          #+#    #+#             */
/*   Updated: 2022/05/30 17:05:48 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Cub3d.h"

int	is_arg_valid(int ac, char **av)
{
	if (ac != 2)
		return (printf("Error : argument count not valid\n"), 0);
	if (ft_strlen(ft_strstr(av[1], ".cub")) != ft_strlen(".cub"))
		return (printf("WRONG MAP NAME"), 0);
	return (1);
}
