/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttostr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:42:14 by anowak            #+#    #+#             */
/*   Updated: 2014/12/09 16:24:32 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_lsttostr(t_list **alst)
{
	t_list	*cur;
	char	*str;
	char	*tmp;

	cur = *alst;
	while (cur)
	{
		if (tmp)
			free(tmp);
		tmp = ft_strdup(str);
		str = ft_strnew(ft_strlen(tmp) + ft_strlen(cur->content));
		str = ft_strcat(tmp, cur->content);
	}
	return (str);
}
