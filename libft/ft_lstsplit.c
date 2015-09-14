/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 17:05:15 by anowak            #+#    #+#             */
/*   Updated: 2014/11/15 17:46:50 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstsplit(char const *s, char c)
{
	t_list	*lst_begin;
	char	*str;
	char	*tmp;
	int		x;

	if (!s)
		return (NULL);
	str = (char *)s;
	lst_begin = NULL;
	while (*str)
	{
		x = 0;
		while (*str == c && *str)
			str++;
		if (!*str)
			break ;
		while (str[x] != c && str[x])
			x++;
		tmp = ft_strndup(str, x);
		ft_lstaddend(&lst_begin, ft_lstnew(tmp, ft_strlen(tmp) * sizeof(char)));
		str = &str[x];
	}
	return (lst_begin);
}
