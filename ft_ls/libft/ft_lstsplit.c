/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 17:05:15 by anowak            #+#    #+#             */
/*   Updated: 2014/11/21 18:45:07 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstsplit(char const *s, char c, int keepc)
{
	t_list	*begin;
	char	*str;
	int		x;

	if (!s)
		return (NULL);
	str = (char *)s;
	begin = NULL;
	while (*str)
	{
		x = 0;
		if (!keepc)
			while (*str == c && *str)
				str++;
		if (!*str)
			break ;
		while (str[x] != c && str[x])
			x++;
		if (keepc == 1 && str[x])
			x++;
		ft_lstaddend(&begin, ft_lstnew(ft_strndup(str, x), (x + 1)));
		str = &str[x];
	}
	return (begin);
}
