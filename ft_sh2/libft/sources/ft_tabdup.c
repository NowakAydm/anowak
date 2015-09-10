/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 20:26:43 by anowak            #+#    #+#             */
/*   Updated: 2015/05/19 20:31:13 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabdup(char **tab)
{
	char	**new;
	int		x;

	new = NULL;
	if (tab)
	{
		if (!(new = ft_memalloc(sizeof(char*) * (ft_tablen(tab) + 1))))
			return (NULL);
		x = -1;
		while (tab[++x])
			new[x] = ft_strdup(tab[x]);
		new[x] = NULL;
	}
	return (new);
}
