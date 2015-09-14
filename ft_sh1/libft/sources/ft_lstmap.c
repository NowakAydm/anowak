/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 16:44:30 by anowak            #+#    #+#             */
/*   Updated: 2015/05/04 19:35:17 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*new;
	t_list	*new_begin;

	new_begin = NULL;
	if (lst)
	{
		tmp = f(lst);
		new_begin = ft_lstnew(tmp->content, tmp->content_size);
		new = new_begin;
		lst = lst->next;
		while (lst)
		{
			tmp = f(lst);
			new->next = ft_lstnew(tmp->content, tmp->content_size);
			new = new->next;
			lst = lst->next;
		}
	}
	return (new_begin);
}
