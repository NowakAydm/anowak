/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlst_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 17:38:33 by anowak            #+#    #+#             */
/*   Updated: 2014/11/15 17:50:48 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlst_str(t_list **alst)
{
	if (*alst)
	{
		while ((*alst)->next)
		{
			ft_putstr((*alst)->content);
			ft_putstr(" - ");
			*alst = (*alst)->next;
		}
		ft_putstr((*alst)->content);
	}
}
