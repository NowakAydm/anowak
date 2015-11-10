/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttotab_n.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/21 15:04:10 by anowak            #+#    #+#             */
/*   Updated: 2015/07/21 15:54:51 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_lsttotab_n(t_list **alst, int n)
{
	t_list	*cur;
	char	**tab;
	int		x;

	tab = NULL;
	if (*alst)
	{
		if (!(tab = (char**)malloc(sizeof(char*) * n + 1)))
			return (NULL);
		cur = *alst;
		x = -1;
		while (cur && n--)
		{
			x++;
			tab[x] = ft_strdup(cur->content);
			cur = cur->next;
		}
		while (++x && n-- > 0)
			tab[x] = NULL;
	}
	return (tab);
}
