/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/06 19:46:22 by anowak            #+#    #+#             */
/*   Updated: 2015/01/06 19:53:20 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_free(t_btree *root)
{
	if (!root)
		return ;
	if (root->left)
		ft_btree_free(root->left);
	if (root->right)
		ft_btree_free(root->right);
	free(root->item);
	free(root);
}
