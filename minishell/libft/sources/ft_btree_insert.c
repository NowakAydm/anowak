/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/01 16:14:58 by anowak            #+#    #+#             */
/*   Updated: 2014/12/03 20:01:31 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_insert(t_btree **root, void *item, int (*cmpf)(void *, void *))
{
	t_btree	*new;
	t_btree	*tmp;

	new = ft_btree_new(item);
	if (!*root)
		*root = new;
	else
	{
		tmp = *root;
		while (tmp->left != new && tmp->right != new)
			if (cmpf(item, tmp->item) < 0)
			{
				if (!tmp->left)
					tmp->left = new;
				else
					tmp = tmp->left;
			}
			else
			{
				if (!tmp->right)
					tmp->right = new;
				else
					tmp = tmp->right;
			}
	}
}
