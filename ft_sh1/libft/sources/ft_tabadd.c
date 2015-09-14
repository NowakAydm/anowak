/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/11 19:03:35 by anowak            #+#    #+#             */
/*   Updated: 2015/06/11 20:09:29 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabadd(char ***tab, char *str)
{
	char	**new_tab = NULL;
	int		len;
	int		x = 0;

	len = ft_tablen(*tab);
	if (!(new_tab = (char**)ft_memalloc(sizeof(char*) * (len + 2))))
		return (NULL);
	while ((*tab)[x])
	{
		new_tab[x] = ft_strdup((*tab)[x]);
		x++;
	}
	new_tab[x] = ft_strdup(str);
	ft_tabfree(*tab);
	*tab = new_tab;
	return (new_tab);
}
