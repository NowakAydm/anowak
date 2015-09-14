/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 15:59:21 by anowak            #+#    #+#             */
/*   Updated: 2014/11/19 17:08:17 by anowak           ###   ########.fr       */
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
			del(tmp, tmp->content_size);
		}
		del(*alst, (*alst)->content_size);
		free(*alst);
		*alst = NULL;
	}
}
