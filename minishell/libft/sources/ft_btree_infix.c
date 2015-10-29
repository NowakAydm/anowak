/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_infix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/01 16:11:40 by anowak            #+#    #+#             */
/*   Updated: 2014/12/02 19:39:38 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_infix(t_btree *root, void (*applyf)(void *))
{
	if (root)
	{
		if (root->left)
			ft_btree_infix(root->left, applyf);
		applyf(root->item);
		if (root->right)
			ft_btree_infix(root->right, applyf);
	}
}
