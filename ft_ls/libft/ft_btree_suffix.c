/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_suffix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/01 16:13:55 by anowak            #+#    #+#             */
/*   Updated: 2014/12/01 16:14:18 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_suffix(t_btree *root, void (*applyf)(void *))
{
	if (root)
	{
		if (root->left != 0)
			ft_btree_suffix(root->left, *applyf);
		if (root->right != 0)
			ft_btree_suffix(root->right, *applyf);
		applyf(root->item);
	}
}
