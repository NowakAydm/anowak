/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttostr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:42:14 by anowak            #+#    #+#             */
/*   Updated: 2015/07/14 20:56:11 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_lsttostr(t_list **alst)
{
	t_list	*cur;
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
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
