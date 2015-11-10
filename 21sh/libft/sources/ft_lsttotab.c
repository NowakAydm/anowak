/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttotab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 20:14:14 by anowak            #+#    #+#             */
/*   Updated: 2015/07/14 20:58:01 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_lsttotab(t_list **alst)
{
	t_list	*cur;
	char	**tab;
	int		x;
	int		len;

	tab = NULL;
	if (*alst)
	{
		len = ft_lstlen(alst);
		if (!(tab = (char**)malloc(sizeof(char*) * len + 1)))
			return (NULL);
		cur = *alst;
		x = -1;
		while (cur)
		{
			x++;
			tab[x] = ft_strdup(cur->content);
			cur = cur->next;
		}
		while (++x <= len)
			tab[x] = 0;
	}
	return (tab);
}
