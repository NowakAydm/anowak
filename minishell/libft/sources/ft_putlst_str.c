/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlst_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 17:38:33 by anowak            #+#    #+#             */
/*   Updated: 2015/05/15 20:16:15 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlst_str(t_list **alst)
{
	t_list	*tmp;

	if (*alst)
	{
		tmp = *alst;
		while (tmp)
		{
			ft_putstr(tmp->content);
			if (tmp->next)
				ft_putstr(" - ");
			tmp = tmp->next;
		}
	}
}
