/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 16:48:53 by anowak            #+#    #+#             */
/*   Updated: 2014/11/14 17:43:29 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	x;

	if (!s || !f)
		return (NULL);
	str = ft_strnew(ft_strlen(s) + 1);
	x = 0;
	if (!str)
		return (NULL);
	while (s[x])
	{
		str[x] = f(x, s[x]);
		x++;
	}
	return (str);
}
