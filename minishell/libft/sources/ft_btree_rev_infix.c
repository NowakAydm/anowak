/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_rev_infix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/07 19:43:48 by anowak            #+#    #+#             */
/*   Updated: 2014/12/07 19:44:01 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_rev_infix(t_btree *root, void (*applyf)(void *))
{
	if (root)
	{
		if (root->right)
			ft_btree_rev_infix(root->right, applyf);
		applyf(root->item);
		if (root->left)
			ft_btree_rev_infix(root->left, applyf);
	}
}
