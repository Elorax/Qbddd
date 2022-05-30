/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:06:31 by abiersoh          #+#    #+#             */
/*   Updated: 2022/05/30 18:35:56 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Cub3d.h"

char	*ft_strstr(const char *str, const char *tofind)
{
	size_t	i;
	size_t	j;

	if (!str || !tofind)
		return (NULL);
	if (!(*tofind))
		return ((char *) str);
	j = 0;
	while (str[j])
	{
		i = 0;
		while (str[i + j] && (str[i + j] == tofind[i]))
		{
			i++;
			if (!tofind[i])
				return ((char *)(str + j));
		}
		j++;
	}
	return (NULL);
}
