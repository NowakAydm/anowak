/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 15:59:21 by anowak            #+#    #+#             */
/*   Updated: 2015/07/14 14:06:42 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;

	if (alst && *alst)
	{
		while ((*alst)->next)
		{
			tmp = *alst;
			*alst = (*alst)->next;
			ft_lstdelone(&tmp, del);
			free(tmp);
		}
		ft_lstdelone(&*alst, del);
		free(*alst);
		*alst = NULL;
	}
}
