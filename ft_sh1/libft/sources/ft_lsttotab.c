/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttotab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 20:14:14 by anowak            #+#    #+#             */
/*   Updated: 2015/05/19 15:07:02 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_lsttotab(t_list **alst)
{
	t_list	*cur;
	char	**tab = NULL;
	int	x;
	int	len;
	
	if (*alst)
	{
	    len = ft_lstlen(alst);
	    tab = (char**)malloc(sizeof(char*) * len + 1);
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
