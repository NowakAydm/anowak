/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 15:59:21 by anowak            #+#    #+#             */
/*   Updated: 2014/11/27 03:16:40 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;

	if (alst)
	{
		while ((*alst)->next)
		{
			tmp = *alst;
			*alst = (*alst)->next;
			ft_lstdelone(&tmp, del);
		}
		ft_lstdelone(&*alst, del);
		free(*alst);
		*alst = NULL;
	}
}
