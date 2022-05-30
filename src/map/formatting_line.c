/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:06:06 by abiersoh          #+#    #+#             */
/*   Updated: 2022/05/30 17:06:09 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Cub3d.h"

char	*ft_remove_newline_space(char *line)
{
	int	i;

	if (ft_strchr(line, '\n'))
		*ft_strchr(line, '\n') = 0;
	i = 0;
	while (line[i] == ' ')
		i++;
	return (ft_substr(line, i, ft_strlen(line) - i));
}

char	*ft_remove_newline(char *line)
{
	if (ft_strchr(line, '\n'))
		*ft_strchr(line, '\n') = 0;
	return (line);
}
