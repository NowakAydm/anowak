/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/12 18:45:29 by exam              #+#    #+#             */
/*   Updated: 2014/09/12 20:12:06 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdlib.h>

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*cur;
	t_list	*next;

	cur = *begin_list;
	next = cur->next;
	if (cmp(data_ref, cur->data) == 0)
	{
		free(cur);
		cur = next;
		*begin_list = cur;
	}
	while (next->next != NULL)
	{
		next = cur->next;
		if (cmp(data_ref, next->data) == 0)
		{
			cur->next = next->next;
			free(next);
		}
		else
			cur = next;
	}
}
