/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 15:14:28 by anowak            #+#    #+#             */
/*   Updated: 2015/01/25 08:33:52 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_strrchr(char const *s, int c)
{
	int				x;
	unsigned char	*r;

	x = 0;
	r = (unsigned char *)s;
	while (r[x])
		x++;
	while (x)
	{
		if (r[x] == c)
			return ((char *)&r[x]);
		x--;
	}
	if (r[x] == c)
		return ((char *)&r[x]);
	return (NULL);
}
