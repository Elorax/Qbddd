/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:06:15 by abiersoh          #+#    #+#             */
/*   Updated: 2022/05/30 18:36:23 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Cub3d.h"

int	read_color(char *line, t_data *data)
{
	int		res;
	int		i;
	char	**tmp;

	if (countchar(line, ',') != 2)
		exit((free_data(data), printf("COULEUR A CHIER\n"), ERROR_BAD_COLOR));
	tmp = formatting_split(line, ',', " ");
	if (!tmp)
		exit((free_data(data), printf("COULEUR A CHIER\n"), ERROR_BAD_COLOR));
	i = -1;
	res = 0;
	while (++i < 3)
	{
		if (tmp[i] && is_8bits_int(tmp[i]))
		{
			res <<= 8;
			res += ft_atoi(tmp[i]);
		}
		else
			break ;
	}
	if ((i == 3) && tmp[i] == NULL)
		return (ft_freesplit(tmp), res);
	exit((free_data(data), ft_freesplit(tmp),
			printf("COULEUR A CHIER\n"), ERROR_BAD_COLOR));
}

int	read_line(char *line, t_data *data)
{
	if (ft_strstr(line, "NO ") == line)
		data->path_north = ft_remove_newline_space(ft_strstr(line, "NO ") + 3);
	else if (ft_strstr(line, "SO ") == line)
		data->path_south = ft_remove_newline_space(ft_strstr(line, "SO ") + 3);
	else if (ft_strstr(line, "EA ") == line)
		data->path_east = ft_remove_newline_space(ft_strstr(line, "EA ") + 3);
	else if (ft_strstr(line, "WE ") == line)
		data->path_west = ft_remove_newline_space(ft_strstr(line, "WE ") + 3);
	else if (ft_strstr(line, "F ") == line)
		data->Fcolor = read_color(line + 2, data);
	else if (ft_strstr(line, "C ") == line)
		data->Ccolor = read_color(line + 2, data);
	else
		return (0);
	return (1);
}
