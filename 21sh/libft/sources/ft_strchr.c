/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 15:09:33 by anowak            #+#    #+#             */
/*   Updated: 2015/10/30 19:13:10 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char *r;

	if (s)
	{
		r = (unsigned char *)s;
		while (*r)
		{
			if (*r == c)
				return ((char *)r);
			r++;
		}
		if (c == 0)
			return ((char *)r);
		else
			return (NULL);
	}
	return (NULL);
}
