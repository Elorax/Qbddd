/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:06:26 by abiersoh          #+#    #+#             */
/*   Updated: 2022/05/30 18:32:56 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Cub3d.h"

char	**formatting_split(char *line, char sep, char *trim)
{
	char	**tmp;
	char	*osef;
	int		i;

	tmp = ft_split(line, sep);
	if (!tmp)
		return (NULL);
	i = -1;
	while (tmp[++i])
	{
		osef = tmp[i];
		tmp[i] = ft_strtrim(tmp[i], trim);
		free(osef);
	}
	if (tmp[2] && ft_strchr(tmp[2], '\n'))
		ft_remove_newline(tmp[2]);
	return (tmp);
}

void	ft_freesplit(char **s)
{
	int	i;

	i = -1;
	if (!s)
		return ;
	while (s[++i])
	{
		free(s[i]);
		s[i] = NULL;
	}
	free(s);
}
