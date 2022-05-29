/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:38:05 by abiersoh          #+#    #+#             */
/*   Updated: 2021/11/27 12:28:37 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_strndup(char const *s, int begin, int end)
{
	char	*dest;
	int		i;
	int		j;

	i = begin;
	j = 0;
	dest = (char *) malloc(sizeof(char) * (end - begin + 2));
	if (!dest)
		return (NULL);
	while (i <= end)
	{
		dest[j] = s[i];
		j++;
		i++;
	}
	dest[j] = 0;
	return (dest);
}

t_list	*ft_lstnnew(void *s, int begin, int end)
{
	t_list	*l;

	l = (t_list *) malloc(sizeof(t_list));
	if (!l)
		return (NULL);
	l->content = ft_strndup((char *)s, begin, end);
	if (!(l->content))
	{
		free(l);
		return (NULL);
	}
	l->next = NULL;
	return (l);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*cursor;

	if (alst && *alst)
	{
		cursor = *alst;
		while (cursor->next)
		{
			cursor = cursor->next;
		}
		cursor->next = new;
	}
	else if (alst)
		*alst = new;
}

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*cursor;

	i = 0;
	cursor = lst;
	while (cursor)
	{
		cursor = cursor->next;
		i++;
	}
	return (i);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!del || !lst || !(*lst))
		return ;
	temp = *lst;
	while (*lst)
	{
		temp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
}
