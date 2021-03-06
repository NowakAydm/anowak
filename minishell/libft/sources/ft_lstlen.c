/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 20:19:12 by anowak            #+#    #+#             */
/*   Updated: 2015/07/14 20:55:41 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstlen(t_list **alst)
{
	t_list	*cur;
	int		x;

	x = 0;
	cur = *alst;
	while (cur)
	{
		x++;
		cur = cur->next;
	}
	return (x);
}
