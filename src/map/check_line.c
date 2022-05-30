/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:05:51 by abiersoh          #+#    #+#             */
/*   Updated: 2022/05/30 18:35:48 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Cub3d.h"

int	is_8bits_int(char *line)
{
	int	size;
	int	i;

	i = -1;
	size = ft_strlen(line);
	if (size > 3 || size == 0)
		return (FALSE);
	while (++i < size)
		if (!ft_isdigit(line[i]))
			return (FALSE);
	if (ft_atoi(line) > 255)
		return (FALSE);
	return (TRUE);
}

int	is_line_valid(char *line, t_data *data)
{
	if (!line)
		return (FALSE);
	if (ft_strstr(line, "NO ") == line
		&& ft_strlen(line) > 4 && !data->path_north)
		return (TRUE);
	else if (ft_strstr(line, "SO ") == line
		&& ft_strlen(line) > 4 && !data->path_south)
		return (TRUE);
	else if (ft_strstr(line, "EA ") == line
		&& ft_strlen(line) > 4 && !data->path_east)
		return (TRUE);
	else if (ft_strstr(line, "WE ") == line
		&& ft_strlen(line) > 4 && !data->path_west)
		return (TRUE);
	else if (ft_strstr(line, "F ") == line
		&& ft_strlen(line) > 7 && data->Fcolor == COLOR_UNSET)
		return (TRUE);
	else if (ft_strstr(line, "C ") == line
		&& ft_strlen(line) > 7 && data->Ccolor == COLOR_UNSET)
		return (TRUE);
	else if (line[0] == '\n')
		return (TRUE);
	else
		return (FALSE);
}

int	countchar(char *line, char c)
{
	int	ret;

	ret = 0;
	while (*line)
		ret += (*line++ == c);
	return (ret);
}

int	check_around_zero(char **map, int i, int j)
{
	if (!j || !i)
		return (FALSE);
	if (map[i][j + 1] == '\n')
		return (FALSE);
	if (!map[i + 1])
		return (FALSE);
	if (ft_strlen(map[i - 1]) < (size_t)(j + 2))
		return (FALSE);
	if (ft_strlen(map[i + 1]) < (size_t)(j + 2))
		return (FALSE);
	if (!ft_strchr("10NSEW", map[i - 1][j - 1])
		|| !ft_strchr("10NSEW", map[i - 1][j])
		|| !ft_strchr("10NSEW", map[i - 1][j + 1])
		|| !ft_strchr("10NSEW", map[i][j - 1])
		|| !ft_strchr("10NSEW", map[i][j + 1])
		|| !ft_strchr("10NSEW", map[i + 1][j - 1])
		|| !ft_strchr("10NSEW", map[i + 1][j])
		|| !ft_strchr("10NSEW", map[i + 1][j + 1]))
		return (FALSE);
	return (TRUE);
}
